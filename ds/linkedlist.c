#include "../include/ds/linkedlist.h"
#include "../include//ds/set.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct linkedlist *init_linkedlist() {
	struct linkedlist *new_ll;
	new_ll = malloc(sizeof(struct linkedlist));

	if (new_ll == NULL) {return NULL;}
	new_ll->first = NULL;
	new_ll->last = NULL;
	new_ll->size = 0;
	return new_ll;
}

struct node *new_node(
	struct node *prev,
	struct set *val,
	struct node *next
) {
	struct node *n = malloc(sizeof(struct node));
	if (!n) {return NULL;}
	n->prev = prev;
	n->next = next;
	n->value = val;

	return n;
}

void insert_node(struct linkedlist *ll, struct set *value) {
	struct node *n = new_node(NULL, value, NULL);

	if (ll->first == NULL) {
		ll->first = n;
		ll->last = n;
		ll->size++;
		return;
	}

	ll->last->next = n;
	n->prev = ll->last;
	ll->last = n;
	ll->size++;
	return;
}

void print_linkedlist(struct linkedlist *ll) {
	struct node *current_node = ll->first;

	while (current_node != NULL) {
		printf("%s : %s\n", current_node->value->key, current_node->value->val);
		current_node = current_node->next;
	}
}
