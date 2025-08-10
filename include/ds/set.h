#ifndef SET_H
#define SET_H

#define MAX_SET 10

#define INSERTED	2
#define UPDATED		1
#define SUCCESS		0
#define ERRAEXIST	-1
#define ERRALLOC	-2
#define ERRUPDATE	-3

struct linkedlist;

struct hash_table{
	struct linkedlist *sets[MAX_SET];
};

struct set{
	char *key;
	char *val;
};

struct hash_table *init_hashtable();
int fr_hash(char *key);
int insert_set(struct hash_table *ht, struct set *set);
int update_set(struct linkedlist *sets, struct set *set);
char *find_value(struct linkedlist *ll, char *key);
char *sget(char *key);
char *strret(int code);
void print_sets(struct hash_table *t);

#endif
