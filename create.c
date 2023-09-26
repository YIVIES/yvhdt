#include "yvhdt.h"

void create(char **args)
{
	FILE *destvhd_fp = NULL;

	destvhd_fp = fopen(args[3], "r+");
	if (destvhd_fp == NULL)
		goto destvhd_err;
	goto success;
success:
	fclose(destvhd_fp);
	return;
destvhd_err:
	perror(args[3]);
	return;
}
