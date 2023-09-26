#include "yvhdt.h"

void create(char **args)
{
	int 		i;
	int 		checksum;
	int 		total_sectors;
	int 		cylinders;
	int 		heads;
	int 		sectors_per_track;
	int 		cylinder_times_heads;
	char 		cookie[8] = "conectix";
	char 		create_app_name[4] = "yvhd";
	FILE 		*destvhd_fp = NULL;
	uint64_t 	creat_bytes;
	time_t 		t;
	struct hard_disk_footer_fields hdff;

	/* 
	 * set create size (MB)
	 */
	creat_bytes 	= atoi(args[2]);
	creat_bytes 	*= (1024 * 1024);
	total_sectors 	= creat_bytes / 512;

	/* 
	 * remove exist file.
	 */
	remove(args[3]);

	/* 
	 * create vhd file.
	 */
	destvhd_fp = fopen(args[3], "w+");
	if (destvhd_fp == NULL)
		goto destvhd_err;

	/* 
	 * write 0x00 to dest vhdfile.
	 */
	fseek(destvhd_fp, 0, SEEK_SET);
	for (i = 0; i < creat_bytes; i++) {
		fputc(0x00, destvhd_fp);
	}

	/* 
	 * set hard disk footer fields.
	 */
	for (i = 0; i < 8; i++)
		hdff.cookie.bytes[i] = cookie[i];
	hdff.features.value 		= 0x02000000;
	hdff.file_format_version.value 	= 0x00000100;
	hdff.data_offset.value 		= 0xffffffffffffffff;

	/* 
	 * clac time from 2000.01.01 12:00:00 (UTC) to now.
	 * 959860800 is 1970.01.01 00:00:00 (UTC)
	 * to 2000.01.01 12:00:00 (UTC) seconds.
	 */
	t = time(NULL) - 959860800;
	for (i = 3; i >= 0; i--)
		hdff.time_stamp.bytes[i] = (t >> ((3 - i) * 8)) & 0xff;
	for (i = 0; i < 4; i++)
		hdff.creator_application.bytes[i] = create_app_name[i];

	hdff.creator_version.value = 0x00000010;
	hdff.creator_host_os.value = 0x007c0000;

	for (i = 7; i >= 0; i--)
		hdff.original_size.bytes[i] = (creat_bytes >> ((7 - i) * 8)) & 0xff;
	hdff.current_size.value = hdff.original_size.value;

	/*
	 * CHS calculation.
	 */
	if (total_sectors > 65535 * 16 * 255)
		total_sectors = 65535 * 16 * 255;
	if (total_sectors >= 65535 * 16 * 63) {
		sectors_per_track = 255;
		heads = 16;
		cylinder_times_heads = total_sectors / sectors_per_track;
	} else {
		sectors_per_track = 17;
		cylinder_times_heads = total_sectors / sectors_per_track;

		heads = (cylinder_times_heads + 1023) / 1024;

		if (heads < 4)
			heads = 4;
		if (cylinder_times_heads >= (heads * 1024) || heads > 16) {
			sectors_per_track = 31;
			heads = 16;
			cylinder_times_heads = total_sectors / sectors_per_track;
		}
		if (cylinder_times_heads >= (heads * 1024)) {
			sectors_per_track = 63;
			heads = 16;
			cylinder_times_heads = total_sectors / sectors_per_track;
		}
	}
	cylinders = cylinder_times_heads / heads;
	hdff.disk_geometry.bytes[0] = (cylinders & 0xff00) >> 8;
	hdff.disk_geometry.bytes[1] = cylinders & 0x00ff;
	hdff.disk_geometry.bytes[2] = heads & 0xff;
	hdff.disk_geometry.bytes[3] = sectors_per_track & 0xff;

	/*
	 * set disk type.
	 */
	hdff.disk_type.value = 0x02000000;

	/*
	 * checksum calculation.
	 */
	checksum = 0;
	hdff.checksum.value = 0;
	for (i = 0; i < 512; i++)
		checksum += ((char *)&hdff)[i];
	for (i = 3; i >= 0; i--)
		hdff.checksum.bytes[i] = ((~checksum) >> (3 - i) * 8) & 0xff;

	/*
	 * set universally unique id.
	 */
	for (i = 0; i < 16; i++)
		hdff.unique_id[i] = 0x1;

	/* 
	 * write footer to vhd.
	 */
	fseek(destvhd_fp, creat_bytes, SEEK_SET);
	for (i = creat_bytes; i < creat_bytes + 512; i++) {
		fputc(((char *)&hdff)[i - creat_bytes], destvhd_fp);
	}
	goto success;
success:
	fclose(destvhd_fp);
	return;
destvhd_err:
	perror(args[3]);
	return;
}
