#ifndef CLIENT
#define CLIENT

#include <stdint.h>
struct foxyram_cli{
	char *host;
	uint16_t port;
	int fd;
};

struct foxyram_cli* init(char *host, uint16_t port);
void cli_connect(struct foxyram_cli *fram);


#endif
