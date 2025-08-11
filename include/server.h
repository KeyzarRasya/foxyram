#ifndef SERVER
#define SERVER

#include <stdint.h>
#include "../include/ds/set.h"

#define MAX_ARGS	10

struct ridaore{
	char *ip_addr;
	uint16_t port;
	char *command;
	char *args[MAX_ARGS];
	struct hash_table *hash_table;
};

struct ridaore* init(char *ip_addr, uint16_t port);
void run(struct ridaore *fram);
char *fr_execute(struct ridaore *fram, char *command);
void parse_command(struct ridaore *fram);
void cleanup(struct ridaore *fram);

#endif
