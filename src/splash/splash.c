#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static const char * const PICFILE = "../rogue.pic";

char* PROGNAME;  // == argv[0], set by main()

void usage(FILE* stream)
{
	fprintf(stream, "Usage: %s [-h|--help] [PICFILE]\n", PROGNAME);
}

_Noreturn void fatal(const char *fmt, ...)
{
	char msg[200];

	va_list argp;
	va_start(argp, fmt);
	vsnprintf(msg, sizeof(msg), fmt, argp);
	va_end(argp);

	fprintf(stderr, "%s: %s\n", PROGNAME, msg);
	usage(stderr);
	exit(1);
}


int main(int argc, char* argv[])
{
	char* arg;
	const char* path = NULL;

	PROGNAME = argv[0];

	while (--argc) {
		arg = *(++argv);
		if (!strcmp("-h", arg) || !strcmp("--help", arg)) {
			printf("Display a 320x200 PIC image in BSAVE format using SDL\n");
			printf("With CGA colors, palette 1i (Black / Cyan / Magenta / White)\n");
			printf("Default image path: %s\n", PICFILE);
			usage(stdout);
			return 0;
		}
		if (!strcmp("--", arg)) {
			argc--;
			break;
		}
		if (arg[0] == '-')
			fatal("invalid option: %s", arg);
		if (path)
			fatal("too many arguments: %s", arg);
		path = arg;
	}
	if (!path) {
		if (argc) {
			path = *(++argv);
			argc--;
		}
		else
			path = PICFILE;
	}
	if (argc)
		fatal("too many arguments: %s", *(++argv));

	assert(!argc);

	printf("PIC path: %s\n", path);

	return 0;
}