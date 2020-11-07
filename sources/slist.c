#include <stdlib.h>
#include <assert.h>

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
uint8_t slist_lookup(const SList *list, int32_t key){
    assert(list != NULL);
    Node* cur = list->head;
    for(cur = list->head; cur != NULL; cur = cur->next){
        if(cur->data == key){
            break;
        }
    }
    return cur != NULL;
}

SList* slist_delnode_head(SList *list){
    assert(list != NULL);
    if(list->head != NULL){
        Node* temp = list->head;
        list->head = list->head->next;
        if(list->head == NULL){
            list->tail = NULL;
        }
        list->length -= 1;
        free(temp);
    }
    return list;
}

SList* slist_delnode_tail(SList *list){
    assert(list != NULL);
    if(list->tail != NULL){
        Node* last = list->tail;
        if(list->tail == list->head){
            list->tail = list->head = NULL;
        }else{
            Node* cur = list->head;
            for(cur = list->head; cur->next != last; cur = cur->next);
            list->tail = cur;
            cur->next = NULL;
        }
        list->length -= 1;
        free(last);
    }
    return list;
}

int32_t slist_find_max_element(const SList *list){
    assert(list != NULL);
    int32_t max = INT32_MIN;
    if(list->head != NULL){
        Node* cur;
        for(cur = list->head; cur != NULL; cur = cur->next){
            if(cur->data > max){
                max = cur->data;
            }
        }
    }
    return max;
}

int32_t slist_find_min_element(const SList *list){
    assert(list != NULL);
    int32_t min = INT32_MAX;
    if(list->head != NULL){
        Node* cur;
        for(cur = list->head; cur != NULL; cur = cur->next){
            if(cur->data < min){
                min = cur->data;
            }
        }
    }
    return min;
}
