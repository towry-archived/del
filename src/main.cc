#include <iostream>
#include <unistd.h>

// getopt optstring.
static const char *OPTSTRING = "fidPRrvW";

// show help string and exit the process.
void show_help() 
{
	printf("usage: del [-f | -i] [-dPRrvW] file ...\n"
	"       unlink file\n");
	exit(0);
}

// option type.
typedef struct {
	bool force;
	bool recursive;
} option_t;

// main entry.
int main(int argc, char *argv[])
{
	int opt;
	option_t *option;

	// parse option.
	option = (option_t *)malloc(sizeof(option_t));

	while ((opt = getopt(argc, argv, OPTSTRING)) != -1) {
		switch (opt) {
			case 'f':
				option->force = true;
				break;
			case 'r':
				option->recursive = true;
				break;
			default:
				show_help();
				break;
		}
	}

	// show help and exit.
	if (optind == 1) {
		show_help();
	}

	argc -= optind;
	argv += optind;

	// rename the files

	return(0);
}
