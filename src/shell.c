#include "../include/shell.h"
#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

struct foxyram_shell *shell_init(struct foxyram_cli *client) {
	struct foxyram_shell *shell;
	shell = malloc(sizeof(struct foxyram_shell));

	if (shell == NULL) {
		perror("Failed to allocate shell memory");
		return NULL;
	}


	shell->client = client;

	return shell;
}

void run(struct foxyram_shell *sh) {
	while (1) {
		read_command(sh);
		execute_command(sh);
	}
}

void read_command(struct foxyram_shell *sh) {
	printf("FoxyRam> ");

	fflush(stdout);
	fgets(sh->input, MAX_INPUT, stdin);
	sh->input[strcspn(sh->input, "\n")] = 0;

	if (strcmp(sh->input, "exit") == 0) {
		exit(1);
	}
}	

void parse_command(struct foxyram_shell *sh) {
	int i = 0;

	char *token = strtok(sh->input, " ");

	while (token != NULL) {
		sh->arguments[i] = token;
		token = strtok(NULL, " ");
		i++;
	}

	sh->arguments[i] = NULL;
}

void execute_command(struct foxyram_shell *sh) {
	char res[1024];
	if (send(sh->client->fd, sh->input, strlen(sh->input), 0) > 0) {
		int n = recv(sh->client->fd, res, sizeof(res), 0);
		if (n < 0) {
			printf("No message were received");
			return;
		}

		res[n] = '\0';
		printf("%s\n", res);

	}
}

void print_args(struct foxyram_shell *sh) {
	int i = 0;

	while (sh->arguments[i] != NULL) {
		printf("%s\n", sh->arguments[i]);
		i++;
	}
}
