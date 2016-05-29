#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h> // :stat 

struct option_s;

void 	del_tree(char **);
void 	del_file(char **, struct option_s *);
void 	show_help();
void 	init_option(struct option_s *);
void 	reset_optind();
int 	init_mv_option(char **, struct option_s *); 
void 	init_argc_argv(int *, char **argv[], const char *, bool);
void 	free_argv(int, char **);
// other source prototype
int do_mv(int, char **);

// getopt optstring.
static const char *OPTSTRING = "fidPRrvW";
static const char *DELETE_TARGET_DIR = "~/.Trash/";
static const char *MV_OPTIONS = "-finv ";
static const char *FAKE_PRG_NAME = "del ";
static const char *TRASH_PATH = NULL;

// option type.
typedef struct option_s {
	bool fflag;
	bool rflag;
	bool dflag;
	bool vflag;
} option_t;

const char *
get_trash_path()
{
	const char *homedir = NULL;
	char *rval = NULL;

	if ((homedir = getenv("HOME")) == NULL) {
		homedir = getpwuid(getuid())->pw_dir;
	}

	rval = (char *)malloc((strlen(homedir) + strlen(DELETE_TARGET_DIR)) * sizeof(char));
	strcat(rval, homedir);
	strcat(rval, "/.Trash");

	return rval;
}

// main entry.
int 
main(int argc, char *argv[])
{
	int opt;
	option_t *option;

	TRASH_PATH = get_trash_path();

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
			case 'd':
				option->dflag = true;
				break;
			case 'v':
				option->vflag = true;
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

	reset_optind();

	if (*argv) {
		// files name after options
		if (option->rflag) {
			del_tree(argv);
		} else {
			del_file(argv, option);
		}
	}

	free((char *)TRASH_PATH);

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
	char *fpath = NULL;
	int mv_argc = 0;
	bool has_mv_option = false;
	char **mv_argv = NULL;
	char *mv_option = NULL;

	while ((fpath = *argv++) != NULL) {
		if(init_mv_option(&mv_option, option)) {
			has_mv_option = false;
		} else {
			has_mv_option = true;
		}

		init_argc_argv(&mv_argc, &mv_argv, fpath, has_mv_option);

		if (has_mv_option) {
			strcpy(mv_argv[1], mv_option);
		}

		// printf("%s\n%s\n%s\n%s\n", mv_argv[0], mv_argv[1], mv_argv[2], mv_argv[3]);

		// fail
		if (lstat(fpath, &sb)) {
			if (!option->fflag || errno != ENOENT) {
				fprintf(stderr, "%s\n", fpath);
			}
			continue;
		} 

		// if is a dir and not allowed to delete dir.
		if (S_ISDIR(sb.st_mode) && !option->dflag) {
			fprintf(stderr, "%s: is a directory\n", fpath);
			continue;
		}

		do_mv(mv_argc, mv_argv);

		free_argv(mv_argc, mv_argv);
		free(mv_option);
		mv_argv = NULL;
		mv_argc = 0;
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
	option->dflag = false;
	option->vflag = false;
}

void 
reset_optind()
{
	optind = 1;
}

void 
init_argc_argv(int *argc, char **argv[], const char *source, bool has_mv_option) 
{
	int rargc = 4;
	int index = 0;
	char **rargv;

	if (!has_mv_option) {
		rargc = 3;
	}

	rargv = malloc(rargc * sizeof(char *));

	rargv[index++] = (char *)malloc(strlen(FAKE_PRG_NAME) * sizeof(char));
	strcpy(rargv[index-1], FAKE_PRG_NAME);

	if (has_mv_option) {
		rargv[index++] = (char *)malloc(strlen(MV_OPTIONS) * sizeof(char));
	}

	rargv[index++] = (char *)malloc(strlen(source) * sizeof(char));
	strcpy(rargv[index-1], source);

	rargv[index++] = (char *)malloc(strlen(TRASH_PATH) * sizeof(char));
	strcpy(rargv[index-1], TRASH_PATH);

	*argc = rargc;
	*argv = rargv;
}

int
init_mv_option(char **mv_option, option_t *option) 
{
	char *tmp = NULL;
	int index = 1;

	tmp = (char *)malloc(strlen(MV_OPTIONS) * sizeof(char));

	// tmp[index++] = '-';

	if (option->fflag) {
		// force, ignore the `i` and `n` option
		tmp[index++] = 'f';
	}
	if (option->vflag) {
		// verbose
		tmp[index++] = 'v';
	}

	*mv_option = tmp;

	if (index > 1) {
		tmp[0] = '-';
	} else {
		return -1;
	}

	return 0;
}


void 
free_argv(int argc, char **argv)
{
	for (int i = 0; i < argc; i++) {
		free(argv[i]);
	}
	free(argv);
}
