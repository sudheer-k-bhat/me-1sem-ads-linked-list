/**
 * Doubly linked list.
 * 
 * @author sudheer-k-bhat
 **/
#ifndef DLIST_H
#define DLIST_H

#include <stdint.h>

typedef struct _dnode_ DNode;
struct _dnode_
{
    int32_t data;
    DNode *next;
    DNode *previous;
};

typedef struct _dlist_ DList;
struct _dlist_
{
    DNode *head;
    DNode *tail;
    uint32_t length;
};

typedef enum {
    BOOL_FALSE = 0,
    BOOL_TRUE = 1
}BOOL;

DList dlist_new();

uint8_t dlist_lookup(const DList *list, int32_t key);

int32_t dlist_length(const DList *list);

DList* dlist_addnode_head(DList *list, int32_t val);

DList* dlist_addnode_tail(DList *list, int32_t val);

DList* dlist_delnode_head(DList *list);

DList* dlist_delnode_tail(DList *list);

int32_t dlist_find_max_element(const DList *list);

int32_t dlist_find_min_element(const DList *list);

DList* dlist_add_element_after(DList* list, int32_t after_this, int32_t val);

BOOL dlist_equals(const DList *list1, const DList *list2);

DList* dlist_reverse_elements(const DList* list, DList* new_list);

DList* dlist_union(const DList *list1, const DList *list2, DList* new_list);

DList* dlist_intersection(const DList *list1, const DList *list2, DList* new_list);

void dlist_to_string(const DList* list);

DList* dlist_del_element(DList* list, int32_t key);

#endif