#include <stdint.h>

#include "slist.h"

typedef struct _node_ Node;
struct _node_
{
    int32_t data;
    Node *next;
};

typedef struct _slist_ SList;
struct _slist_
{
    Node *head;
    Node *tail;
    uint32_t length;
};

SList slist_new();

//No modifications are neeed, so using `const`
//not using `stdbool` bcoz not supported across compilers & platforms.
uint8_t slist_lookup(const SList *list, int32_t key);

int32_t slist_length(const SList *list);

SList* slist_addnode_head(SList *list, int32_t val);

SList* slist_addnode_tail(SList *list, int32_t val);

SList* slist_delnode_head(SList *list);

SList* slist_delnode_tail(SList *list);

int32_t slist_find_max_element(const SList *list);

int32_t slist_find_min_element(const SList *list);

//TODO

SList* slist_add_element_after(SList* list, int32_t after_this, int32_t val);

SList* slist_del_element(SList* list, int32_t key);

SList* slist_reverse_elements(SList* list);

uint8_t slist_equals(const SList *list1, const SList *list2);

SList* slist_union(SList *list1, SList *list2);

SList* slist_intersection(SList *list1, SList *list2);


