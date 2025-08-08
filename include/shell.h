#ifndef SHELL
#define SHELL

#include "client.h"

#define MAX_INPUT 	1024
#define MAX_ARGS	10

struct foxyram_shell{
	struct foxyram_cli *client;
	char input[MAX_INPUT];
	char *arguments[MAX_ARGS];
};

struct foxyram_shell *shell_init(struct foxyram_cli *client);
void run(struct foxyram_shell *sh);
void read_command(struct foxyram_shell *sh);
void parse_command(struct foxyram_shell *sh);
void execute_command(struct foxyram_shell *sh);
void print_args(struct foxyram_shell *sh);

#endif
