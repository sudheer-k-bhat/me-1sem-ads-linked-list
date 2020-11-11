#include <stdlib.h>
#include <assert.h>

#include "log.h"
#include "slist.h"

SList slist_new()
{
    SList slist = {NULL, NULL, 0};
    return slist;
}

int32_t slist_length(const SList *list)
{
    assert(list != NULL);
    return list->length;
}

//private function via `static`
static Node *_get_new_node(int32_t val)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = val;
    node->next = NULL;
    return node;
}

SList *slist_addnode_head(SList *list, int32_t val)
{
    assert(list != NULL);
    Node *node = _get_new_node(val);
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

SList *slist_addnode_tail(SList *list, int32_t val)
{
    assert(list != NULL);
    Node *node = _get_new_node(val);
    if (list->tail != NULL)
    {
        list->tail->next = node;
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
uint8_t slist_lookup(const SList *list, int32_t key)
{
    assert(list != NULL);
    Node *cur = list->head;
    for (cur = list->head; cur != NULL; cur = cur->next)
    {
        if (cur->data == key)
        {
            break;
        }
    }
    return cur != NULL;
}

SList *slist_delnode_head(SList *list)
{
    assert(list != NULL);
    if (list->head != NULL)
    {
        Node *temp = list->head;
        list->head = list->head->next;
        if (list->head == NULL)
        {
            list->tail = NULL;
        }
        list->length -= 1;
        free(temp);
    }
    return list;
}

SList *slist_delnode_tail(SList *list)
{
    assert(list != NULL);
    if (list->tail != NULL)
    {
        Node *last = list->tail;
        if (list->tail == list->head)
        {
            list->tail = list->head = NULL;
        }
        else
        {
            Node *cur = list->head;
            for (cur = list->head; cur->next != last; cur = cur->next)
                ;
            list->tail = cur;
            cur->next = NULL;
        }
        list->length -= 1;
        free(last);
    }
    return list;
}

int32_t slist_find_max_element(const SList *list)
{
    assert(list != NULL);
    int32_t max = INT32_MIN;
    if (list->head != NULL)
    {
        Node *cur;
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

int32_t slist_find_min_element(const SList *list)
{
    assert(list != NULL);
    int32_t min = INT32_MAX;
    if (list->head != NULL)
    {
        Node *cur;
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
SList *slist_add_element_after(SList *list, int32_t after_this, int32_t val)
{
    assert(list != NULL);
    if (list->head != NULL)
    {
        Node *cur;
        for (cur = list->head; cur != NULL; cur = cur->next)
        {
            if (cur->data == after_this)
            {
                Node *new = _get_new_node(val);
                Node *next = cur->next;
                new->next = next;
                cur->next = new;
                list->length += 1;
            }
        }
    }
    return list;
}

// SList* slist_del_element(SList* list, int32_t key){
//     assert(list != NULL);
//     if(list->head != NULL){
//         Node* cur;
//         for(cur = list->head; cur != NULL; cur = cur->next){
//             if(cur->data == key){

//             }
//         }
//     }
// }

BOOL slist_equals(const SList *list1, const SList *list2)
{
    assert(list1 != NULL && list2 != NULL);
    BOOL is_equal = BOOL_FALSE;
    if (list1->length == list2->length)
    {
        Node *cur1;
        Node *cur2;
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

SList *slist_reverse_elements(const SList *list, SList *new_list)
{
    assert(list != NULL);
    if (list->length > 0)
    {
        Node *cur;
        for (cur = list->head; cur != NULL; cur = cur->next)
        {
            new_list = slist_addnode_head(new_list, cur->data);
        }
    }
    return new_list;
}

//TODO improve efficiency
SList *slist_union(const SList *list1, const SList *list2, SList *new_list)
{
    assert(list1 != NULL && list2 != NULL);
    Node *cur;
    for (cur = list2->head; cur != NULL; cur = cur->next)
    {
        if (slist_lookup(list1, cur->data) == BOOL_FALSE)
        {
            new_list = slist_addnode_tail(new_list, cur->data);
        }
    }
    for (cur = list1->head; cur != NULL; cur = cur->next)
    {
        slist_addnode_tail(new_list, cur->data);
    }
    return new_list;
}

SList *slist_intersection(const SList *list1, const SList *list2, SList *new_list)
{
    assert(list1 != NULL && list2 != NULL);
    Node *cur;
    for (cur = list2->head; cur != NULL; cur = cur->next)
    {
        if (slist_lookup(list1, cur->data) == BOOL_TRUE)
        {
            new_list = slist_addnode_tail(new_list, cur->data);
        }
    }
    return new_list;
}

void slist_to_string(const SList *list)
{
    assert(list != NULL);
    Node *cur;
    log_debug("SList{length: %d, elements: [", list->length);
    for (cur = list->head; cur != NULL; cur = cur->next)
    {
        log_debug("%d", cur->data);
    }
    log_debug("]}");
}

//TODO avoid O(n^2)
SList *slist_del_element(SList *list, int32_t key)
{
    assert(list != NULL);
    Node *cur = list->head;
    for (cur = list->head; cur != NULL; cur = cur->next)
    {
        if (cur->data == key)
        {
            if (list->tail == list->head)
            {
                list->tail = list->head = NULL;
            }
            else if(cur == list->head){
                Node* next = cur->next;
                list->head = next;
                cur->next = NULL;
            }
            else
            {
                Node *prev = list->head;
                for (prev = list->head; prev->next != cur; prev = prev->next);
                prev->next = cur->next;
                cur->next = NULL;
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
