/**
 * Set implementation.
 * 
 * @author sudheer-k-bhat
 **/
#ifndef SET_H
#define SET_H
#include <stdint.h>

#include "slist.h"

typedef struct _set_ Set;
struct _set_
{
    Node *head;
    Node *tail;
    uint32_t length;
};

typedef enum {
    SET_OK,
    SET_DUPLICATE_ELEMENT
}SET_STATUS;

typedef struct {
    int32_t data;
    SET_STATUS status;
}SetResult;

Set set_new();

uint8_t set_lookup(const Set *set, int32_t key);

int32_t set_length(const Set *set);

Set* set_addnode_head(Set *set, int32_t val, SetResult* result);

Set* set_addnode_tail(Set *set, int32_t val, SetResult* result);

Set* set_add_element_after(Set* set, int32_t after_this, int32_t val, SetResult* result);

Set* set_delnode_head(Set *set);

Set* set_delnode_tail(Set *set);

int32_t set_find_max_element(const Set *set);

int32_t set_find_min_element(const Set *set);

BOOL set_equals(const Set *set1, const Set *set2);

Set* set_reverse_elements(const Set* set, Set* new_set);

Set* set_union(const Set *set1, const Set *set2, Set* new_set);

Set* set_intersection(const Set *set1, const Set *set2, Set* new_set);

void set_to_string(const Set* set);

Set* set_del_element(Set* set, int32_t key);


#endif