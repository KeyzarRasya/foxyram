#ifndef CLIENT
#define CLIENT

#include <stdint.h>
struct ridaore_cli{
	char *host;
	uint16_t port;
	int fd;
};

struct ridaore_cli* init(char *host, uint16_t port);
void cli_connect(struct ridaore_cli *fram);


#endif
