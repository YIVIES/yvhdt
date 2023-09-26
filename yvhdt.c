#include "yvhdt.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		goto param_err;
	}

	if ((!strncmp(argv[1], "create", strlen("create"))) && (argc == 3)) {
		create(argv);
		goto success;
	} else if ((!strncmp(argv[1], "output", strlen("output"))) && (argc == 4)) {
		output(argv);
		goto success;
	} else goto param_err;

success:
	return 0;
param_err:
	printf("Usage: %s [output | create] [[dest.vhd srcfile] | name.vhd]\n", argv[0]);
	return -1;
}

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

void create(char **args)
{
	return;
}
