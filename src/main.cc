#include <iostream>
#include <unistd.h>

void 	rm_tree(char **);
void 	rm_file(char **);
void 	show_help();

// getopt optstring.
static const char *OPTSTRING = "fidPRrvW";

// option type.
typedef struct {
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

	// show help and exit.
	if (optind == 1) {
		show_help();
	}

	argc -= optind;
	argv += optind;

	if (*argv) {
		// files name after options
		if (option->rflag) {
			rm_tree(argv);
		} else {
			rm_file(argv);
		}
	}

	return(0);
}

void
rm_tree(char **argv) 
{

}

// rm file
void 
rm_file(char **argv) 
{
	
}

// show help string and exit the process.
void 
show_help() 
{
	fprintf(stderr, "%s\n%s\n", "usage: del [-f | -i] [-dPRrvW] file ...\n",
	"       unlink file\n");
	exit(0);
}
