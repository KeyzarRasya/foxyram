#ifndef SERVER
#define SERVER

#include <stdint.h>
#include "../include/ds/set.h"

#define MAX_ARGS	10

struct foxyram{
	char *ip_addr;
	uint16_t port;
	char *command;
	char *args[MAX_ARGS];
	struct hash_table *hash_table;
};

struct foxyram* init(char *ip_addr, uint16_t port);
void run(struct foxyram *fram);
char *fr_execute(struct foxyram *fram, char *command);
void parse_command(struct foxyram *fram);
void cleanup(struct foxyram *fram);

#endif
