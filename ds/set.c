#include "../include/ds/set.h"
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/ds/linkedlist.h"

struct hash_table *init_hashtable() {
    struct hash_table *ht = malloc(sizeof(struct hash_table));
    if (!ht) return NULL;

    for (int i = 0; i < MAX_SET; i++) {
        ht->sets[i] = malloc(sizeof(struct linkedlist));
        if (!ht->sets[i]) {
            for (int j = 0; j < i; j++) {
                free(ht->sets[j]);
            }
            free(ht);
            return NULL;
        }

        ht->sets[i]->first = NULL;
        ht->sets[i]->last = NULL;
        ht->sets[i]->size = 0;
    }

    return ht;
}

int fr_hash(char *key) {
	int i = 0;
	int total = 9;

	while (key[i] != '\000') {
		total += key[i];
		i++;
	}

	return total;
}

int insert_set(struct hash_table *ht, struct set *set) {
	int hash = fr_hash(set->key);
	int index = hash % MAX_SET;

	if (!find_value(ht->sets[index], set->key)) {
		insert_node(ht->sets[index], set);
		printf("Inserted LL Index %d, Value %s\n", index, set->val);
		return INSERTED;
	}
	
	return update_set(ht->sets[index], set);
}

int update_set(struct linkedlist *sets, struct set *set) {
	struct node *current_node = sets->first;

	while (current_node) {
		if (strcmp(
			set->key, current_node->value->val
		) == 0) {
			current_node->value->val = set->val;
			return UPDATED;
		}
		current_node = current_node->next;
	}
	return ERRUPDATE;
}

char *find_value(struct linkedlist *ll, char *key) {
	if (!ll | !ll->first) {
		return NULL;
	}
	struct node *current_node = ll->first;
	char *value = NULL;

	printf("Current node %s\n", current_node->value->val);
	while (current_node != NULL) {
		printf("%s | %s\n", key, current_node->value->key);
		if (strcmp(key, current_node->value->key) == 0) {
			value = current_node->value->val;
		}
		current_node = current_node->next;
	}

	return value;
}

char *sget(char *key) {

	return NULL;
}

char *strret(int code) {

	switch (code)
	{
	case ERRAEXIST:
		/* code */
		return "Error: Already Exist";
		break;
	case ERRALLOC:
		return "Error: Failed to allocating memory";
		break;
	case ERRUPDATE:
		return "Error: Failed while updating linkedlist";
		break;
	case INSERTED:
		return "Success: Success inserting key val to memory";
		break;
	case UPDATED:
		return "Success: Updating new value to existing key";
		break;
	case SUCCESS:
		return "Success: just success";
		break;
	default:
		return "Unknown Error Code";
		break;
	}

}

void print_sets(struct hash_table *t) {
	int i = 0;

	while (i < MAX_SET) {
		struct linkedlist *ll = t->sets[i];
		printf("Index %d\n", i);
		print_linkedlist(ll);
		i++;
	}
}