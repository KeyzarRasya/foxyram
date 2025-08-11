#ifndef SHELL
#define SHELL

#include "client.h"

#define MAX_INPUT 	1024
#define MAX_ARGS	10

struct ridaore_shell{
	struct ridaore_cli *client;
	char input[MAX_INPUT];
	char *arguments[MAX_ARGS];
};

struct ridaore_shell *shell_init(struct ridaore_cli *client);
void run(struct ridaore_shell *sh);
void read_command(struct ridaore_shell *sh);
void parse_command(struct ridaore_shell *sh);
void execute_command(struct ridaore_shell *sh);
void print_args(struct ridaore_shell *sh);

#endif
