#ifndef __YVHDT_H
#define __YVHDT_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define COOKIE "conectix"
#define FEATURES 0x20000000
#define FILE_FORMAT_VERSION 0x00000100
#define DATA_OFFSET 0xffffffffffffffff
#define CREATOR_APPLICATION "yvhd"
#define CREATOR_VERSION 0x00000900
#define CREATOR_HOST_OS 0x6b326957

struct hard_disk_footer_fields {
	union { uint64_t value;
       		char bytes[8];	} cookie;
	union { uint32_t value;
       		char bytes[4];	} features;
	union { uint32_t value;
       		char bytes[4];	} file_format_version;
	union { uint64_t value;
       		char bytes[8];	} data_offset;
	union { uint32_t value;
       		char bytes[4];	} time_stamp;
	union { uint32_t value;
       		char bytes[4];	} creator_application;
	union { uint32_t value;
       		char bytes[4];	} creator_version;
	union { uint32_t value;
       		char bytes[4];	} creator_host_os;
	union { uint32_t value;
       		char bytes[8];	} original_size;
	union { uint32_t value;
       		char bytes[8];	} current_size;
	union { uint32_t value;
       		char bytes[4];	} disk_geometry;
	union { uint32_t value;
		char bytes[4];	} disk_type;
	union { uint32_t value;
       		char bytes[4];	} checksum;
	char unique_id[16];
	char saved_state;
	char reserved[427];
};


void output(char **);
void create(char **);

#endif // __YVHDT_H
