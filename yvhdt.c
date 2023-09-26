#include "yvhdt.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		goto param_err;
	}

	if ((!strncmp(argv[1], "create", strlen("create"))) && (argc == 4)) {
		create(argv);
		goto success;
	} else if ((!strncmp(argv[1], "output", strlen("output"))) && (argc == 4)) {
		output(argv);
		goto success;
	} else goto param_err;

success:
	return 0;
param_err:
	printf("Usage: %s [output | create] [[dest.vhd srcfile] | [vhdsize name.vhd]]\n", argv[0]);
	return -1;
}
