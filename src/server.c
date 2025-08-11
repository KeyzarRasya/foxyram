#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../include/ds/set.h"
#include "../include/ds/linkedlist.h"
#include "../include/server.h"

struct ridaore* init(char *ip_addr, uint16_t port) {
	struct ridaore *fram;
	fram = malloc(sizeof(struct ridaore));

	if (fram == NULL) {
		perror("Failed to initiate ridaore");
		return NULL;
	}
	
	fram->hash_table = init_hashtable();
	fram->ip_addr = strdup(ip_addr);
	fram->port = port;

	return fram;
}

void run(struct ridaore *fram){ 
	system("clear");
	int fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);

	printf("+------------------+\n");
	printf("|                  |\n");
	printf("|      FoxyRam     |\n");
	printf("|                  |\n");
	printf("+------------------+\n");


	fd = socket(AF_INET, SOCK_STREAM, 0);

	if (fd == -1) {
		perror("Failed to create socket");
		close(fd);
		return;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(fram->port);
	inet_pton(AF_INET, fram->ip_addr, &server_addr.sin_addr);

	int opt = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		perror("Failed to set sock options");
		close(fd);
		return;
	}

	if (bind(fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1 ) {
		perror("Failed to bind");
		close(fd);
		return;
	}

	printf("[ FoxyRam Server ]: Creating connection to %s:%d via TCP Connection\n", fram->ip_addr, fram->port);

	if (listen(fd, 5) == -1) {
		perror("Failed to listen connection");
		close(fd);
		return;
	}

	printf("[ FoxyRam Server ]: Server running on port %s:%d\n", fram->ip_addr, fram->port);

	while (1) {
		int c = accept(fd, (struct sockaddr*)&client_addr, &client_len);

		if (c == -1) {
			perror("Error Accepting Connection");
			continue;
		}

		char buff[1024];

		while (1) {
			int n = recv(c, buff, sizeof(buff) - 1, 0);
			if (n <= 0) {
				break;
			}

			buff[n] = '\0';	
			char *res = fr_execute(fram, buff);

			send(c, res, strlen(res), 0);
			
		}

		close(c);
	}
	close(fd);
}

void parse_command(struct ridaore *fram) {
	int i = 0;
	char *token = strtok(fram->command, " ");
	
	while (token != NULL) {
		fram->args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}

	fram->args[i] = NULL;
}

char *fr_execute(struct ridaore *fram, char *command) {
	int i = 0;
	fram->command = command;
	parse_command(fram);

	if (strcmp(fram->args[0], "set") == 0) {
		struct set *set =
			malloc(sizeof(struct set));
		set->key = strdup(fram->args[1]);
		set->val = strdup(fram->args[2]);
		int insert = 
			insert_set(fram->hash_table, set);
		return strret(insert);
	} else if (strcmp(fram->args[0], "get") == 0) {
		int hash = fr_hash(fram->args[1]);
		int index = hash % 10;

		struct linkedlist *ll = fram->hash_table->sets[index];
		char *value = find_value(ll, fram->args[1]);
		if (!value) {
			return strdup("No Values were found");
		} else {
			return strdup(value);
		}
	}

	return strdup("Unknown Command");
}

void cleanup(struct ridaore *fram) {
	int i = 0;
	while (i < MAX_SET) {
		free(fram->hash_table->sets[i]);
		free(fram->args[i]);
		i++;
	}
	free(fram->command);
	free(fram->ip_addr);
	free(fram);
}
