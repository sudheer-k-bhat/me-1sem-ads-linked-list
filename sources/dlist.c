#include <stdlib.h>
#include <assert.h>

#include "log.h"
#include "dlist.h"

DList dlist_new()
{
    DList slist = {NULL, NULL, 0};
    return slist;
}

int32_t dlist_length(const DList *list)
{
    assert(list != NULL);
    return list->length;
}

//private function via `static`
static DNode *_get_new_node(int32_t val)
{
    DNode *node = (DNode *)malloc(sizeof(DNode));
    node->data = val;
    node->next = NULL;
    node->previous = NULL;
    return node;
}

DList *dlist_addnode_head(DList *list, int32_t val)
{
    assert(list != NULL);
    DNode *node = _get_new_node(val);
    if(list->head != NULL){
        list->head->previous = node;
    }
    node->next = list->head;
    list->head = node;
    if (list->tail == NULL)
    {
        list->tail = node;
    }
    list->length += 1;
    assert((list->length == 1 && list->head == list->tail) ||
           (list->length > 1 && list->head != list->tail));
    return list;
}

DList *dlist_addnode_tail(DList *list, int32_t val)
{
    assert(list != NULL);
    DNode *node = _get_new_node(val);
    if (list->tail != NULL)
    {
        list->tail->next = node;
        node->previous = list->tail;
        list->tail = node;
    }
    else
    {
        list->head = list->tail = node;
    }
    list->length += 1;
    assert((list->length == 1 && list->head == list->tail) ||
           (list->length > 1 && list->head != list->tail));
    return list;
}

//Avoid multiple return statements when possible.
uint8_t dlist_lookup(const DList *list, int32_t key)
{
    assert(list != NULL);
    DNode *cur = list->head;
    for (cur = list->head; cur != NULL; cur = cur->next)
    {
        if (cur->data == key)
        {
            break;
        }
    }
    return cur != NULL;
}

DList *dlist_delnode_head(DList *list)
{
    assert(list != NULL);
    if (list->head != NULL)
    {
        DNode *temp = list->head;
        list->head = list->head->next;
        list->head->previous = NULL;
        if (list->head == NULL)
        {
            list->tail = NULL;
        }
        list->length -= 1;
        free(temp);
    }
    return list;
}

DList *dlist_delnode_tail(DList *list)
{
    assert(list != NULL);
    if (list->tail != NULL)
    {
        DNode *last = list->tail;
        if (list->tail == list->head)
        {
            list->tail = list->head = NULL;
        }
        else
        {
            DNode *cur = list->tail->previous;
            list->tail = cur;
            cur->next = NULL;
        }
        list->length -= 1;
        free(last);
    }
    return list;
}

int32_t dlist_find_max_element(const DList *list)
{
    assert(list != NULL);
    int32_t max = INT32_MIN;
    if (list->head != NULL)
    {
        DNode *cur;
        for (cur = list->head; cur != NULL; cur = cur->next)
        {
            if (cur->data > max)
            {
                max = cur->data;
            }
        }
    }
    return max;
}

int32_t dlist_find_min_element(const DList *list)
{
    assert(list != NULL);
    int32_t min = INT32_MAX;
    if (list->head != NULL)
    {
        DNode *cur;
        for (cur = list->head; cur != NULL; cur = cur->next)
        {
            if (cur->data < min)
            {
                min = cur->data;
            }
        }
    }
    return min;
}

//TODO handle tail
DList *dlist_add_element_after(DList *list, int32_t after_this, int32_t val)
{
    assert(list != NULL);
    if (list->head != NULL)
    {
        DNode *cur;
        for (cur = list->head; cur != NULL; cur = cur->next)
        {
            if (cur->data == after_this)
            {
                DNode *new = _get_new_node(val);
                DNode *next = cur->next;
                new->next = next;
                new->previous = cur;
                cur->next = new;
                list->length += 1;
            }
        }
    }
    return list;
}

BOOL dlist_equals(const DList *list1, const DList *list2)
{
    assert(list1 != NULL && list2 != NULL);
    BOOL is_equal = BOOL_FALSE;
    if (list1->length == list2->length)
    {
        DNode *cur1;
        DNode *cur2;
        is_equal = BOOL_TRUE;

        for (cur1 = list1->head, cur2 = list2->head; cur1 != NULL; cur1 = cur1->next, cur2 = cur2->next)
        {
            if (cur1->data != cur2->data)
            {
                is_equal = BOOL_FALSE;
                break;
            }
        }
    }
    return is_equal;
}

DList *dlist_reverse_elements(const DList *list, DList *new_list)
{
    assert(list != NULL);
    if (list->length > 0)
    {
        DNode *cur;
        for (cur = list->head; cur != NULL; cur = cur->next)
        {
            new_list = dlist_addnode_head(new_list, cur->data);
        }
    }
    return new_list;
}

//TODO improve efficiency
DList *dlist_union(const DList *list1, const DList *list2, DList *new_list)
{
    assert(list1 != NULL && list2 != NULL);
    DNode *cur;
    for (cur = list2->head; cur != NULL; cur = cur->next)
    {
        if (dlist_lookup(list1, cur->data) == BOOL_FALSE)
        {
            new_list = dlist_addnode_tail(new_list, cur->data);
        }
    }
    for (cur = list1->head; cur != NULL; cur = cur->next)
    {
        dlist_addnode_tail(new_list, cur->data);
    }
    return new_list;
}

DList *dlist_intersection(const DList *list1, const DList *list2, DList *new_list)
{
    assert(list1 != NULL && list2 != NULL);
    DNode *cur;
    for (cur = list2->head; cur != NULL; cur = cur->next)
    {
        if (dlist_lookup(list1, cur->data) == BOOL_TRUE)
        {
            new_list = dlist_addnode_tail(new_list, cur->data);
        }
    }
    return new_list;
}

void dlist_to_string(const DList *list)
{
    assert(list != NULL);
    DNode *cur;
    log_debug("DList{head:%p, tail:%p, length: %d, elements: [", list->head, list->tail, list->length);
    for (cur = list->head; cur != NULL; cur = cur->next)
    {
        log_debug("addr:%p, data:%d, prev:%p, next:%p", cur, cur->data, cur->previous, cur->next);
    }
    log_debug("]}");
}

DList *dlist_del_element(DList *list, int32_t key)
{
    assert(list != NULL);
    DNode *cur = list->head;
    for (cur = list->head; cur != NULL; cur = cur->next)
    {
        if (cur->data == key)
        {
            if (list->tail == list->head)
            {
                list->tail = list->head = NULL;
            }
            else if(cur == list->head){
                DNode* next = cur->next;
                list->head = next;
                next->previous = NULL;
                cur->next = NULL;
            }
            else
            {
                DNode *prev = cur->previous;
                prev->next = cur->next;
                if(cur->next != NULL){
                    cur->next->previous = prev;
                }
                cur->next = NULL;
                cur->previous = NULL;
                if(cur == list->tail){
                    list->tail = prev;
                }
            }
            list->length -= 1;
            free(cur);
            break;
        }
    }
    return list;
}
