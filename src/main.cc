#include <iostream>
#include <unistd.h>

using namespace std;

static const char *OPTSTRING = "fidPRrvW";

void show_help() 
{
	printf("usage: rm [-f | -i] [-dPRrvW] file ...\n"
	"       unlink file\n");
	exit(0);
}

typedef struct {
	bool force;
	bool recursive;
} option_t;

inline void option_tostring(option_t *option) 
{
	
}

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

	option_tostring(option);

	return(0);
}
