#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h> // :stat 


void 	del_tree(char **);
void 	del_file(char **);
void 	show_help();
void 	init_option(struct option_s *);

// getopt optstring.
static const char *OPTSTRING = "fidPRrvW";

// option type.
typedef struct option_s {
	bool fflag;
	bool rflag;
} option_t;

// main entry.
int 
main(int argc, char *argv[])
{
	int opt;
	option_t *option;

	// parse option.
	option = (option_t *)malloc(sizeof(option_t));
	init_option(option);

	while ((opt = getopt(argc, argv, OPTSTRING)) != -1) {
		switch (opt) {
			case 'f':
				option->fflag = true;
				break;
			case 'R':
			case 'r':
				option->rflag = true;
				break;
			default:
				show_help();
				break;
		}
	}

	argc -= optind;
	argv += optind;

	/**
	 * If no arguments left, show help and exit.
	 */
	if (argc <= 0) {
		if (option->fflag)
			return(0);
		show_help();
	}

	if (*argv) {
		// files name after options
		if (option->rflag) {
			del_tree(argv);
		} else {
			del_file(argv);
		}
	}

	return(0);
}

void
del_tree(char *argv[]) 
{

}

// del file
void 
del_file(char *argv[], option_t *option) 
{
	struct stat sb;
	char *fpath;

	while ((fpath = *argv++) != NULL) {
		// fail
		if (lstat(fpath, &sb)) {
			if (!option->fflag || errno != ENOENT)
		}
	}
}

// show help string and exit the process.
void 
show_help() 
{
	fprintf(stderr, "%s\n%s\n", "usage: del [-f | -i] [-dPRrvW] file ...",
	"       unlink file");
	exit(0);
}

void 
init_option(option_t *option) 
{
	option->fflag = false;
	option->rflag = false;
}
