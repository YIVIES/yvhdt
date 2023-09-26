#ifndef __YVHDT_H
#define __YVHDT_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

struct hard_disk_footer_fields {
	char cookie[8];
	uint32_t features;
	char file_format_version[4];
	char data_offset[8];
	char time_stamp[4];
	char creator_application[4];
	char creator_version[4];
	char creator_host_os[4];
	char original_size[8];
	char current_size[8];
	char disk_geometry[4];
	char disk_type[4];
	char checksum[4];
	char unique_id[16];
	char saved_state;
	char reserved[427];
};

void output(char **);
void create(char **);

#endif // __YVHDT_H
