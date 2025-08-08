#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "../include/client.h"

struct foxyram_cli* init(char *host, uint16_t port) {
	struct foxyram_cli *fram_cli;
	fram_cli = malloc(sizeof(struct foxyram_cli));

	if (fram_cli == NULL) {
		perror("Failed to allocate memory");
		return NULL;
	}

	fram_cli->host = host;
	fram_cli->port = port;
	fram_cli->fd = 0;
	return fram_cli;
}

void cli_connect(struct foxyram_cli *fram) {
	int fd;
	struct sockaddr_in server_addr;

	server_addr.sin_port = htons(7000);
	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
	fd = socket(AF_INET, SOCK_STREAM, 0);

	if (fd == -1) {
		perror("Failed socket creation");
		return;
	}

	if (connect(fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		perror("Failed to connect");
		close(fd);
		return;
	}
	printf("%d", fd);
	fram->fd = fd;
}

