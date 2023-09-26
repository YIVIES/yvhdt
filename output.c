#include "yvhdt.h"

void output(char **args)
{
	FILE *destvhd_fp = NULL;
	FILE *srcfile_fp = NULL;
	int srcfile_data;
	
	/* first check whether the files exists */
	destvhd_fp = fopen(args[2], "r+");
	if (destvhd_fp == NULL)
		goto destvhd_err;
	srcfile_fp = fopen(args[3], "r+");
	if (srcfile_fp == NULL)
		goto srcfile_err;

	/* write data to destvhd */
	fseek(destvhd_fp, 0, SEEK_SET);
	fseek(srcfile_fp, 0, SEEK_SET);
	while ((srcfile_data = fgetc(srcfile_fp)) != EOF) {
		fputc(srcfile_data, destvhd_fp);
	}
	goto success;
success:
	fclose(destvhd_fp);
	fclose(srcfile_fp);
	return;
destvhd_err:
	perror(args[2]);
	return;
srcfile_err:
	perror(args[3]);
	return;
}
