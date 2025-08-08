#ifndef LINKEDLIST
#define LINKEDLIST

struct set;

struct linkedlist{
	struct node *first;
	struct node *last;
	int size;
};

struct node{
	struct node *prev;
	struct set *value;
	struct node *next;
};

struct linkedlist *init_linkedlist();
struct node *new_node(struct node *prev, struct set *value, struct node *next);
void insert_node(struct linkedlist *ll, struct set *value);
char *find_val(char *key);
void print_linkedlist(struct linkedlist *ll);

#endif
