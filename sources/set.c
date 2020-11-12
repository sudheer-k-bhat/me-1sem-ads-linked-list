#include <stdlib.h>
#include <assert.h>

#include "log.h"
#include "set.h"

Set set_new()
{
    Set sset = {NULL, NULL, 0};
    return sset;
}

int32_t set_length(const Set *set)
{
    assert(set != NULL);
    return set->length;
}

//private function via `static`
static Node *_get_new_node(int32_t val)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = val;
    node->next = NULL;
    return node;
}

Set *set_addnode_head(Set *set, int32_t val, SetResult *result)
{
    assert(set != NULL);
    if (set_lookup(set, val) == BOOL_TRUE)
    {
        result->status = SET_DUPLICATE_ELEMENT;
    }
    else
    {
        Node *node = _get_new_node(val);
        node->next = set->head;
        set->head = node;
        if (set->tail == NULL)
        {
            set->tail = node;
        }
        set->length += 1;
        assert((set->length == 1 && set->head == set->tail) ||
               (set->length > 1 && set->head != set->tail));
        result->status = SET_OK;
    }
    return set;
}

Set *set_addnode_tail(Set *set, int32_t val, SetResult *result)
{
    assert(set != NULL);
    if (set_lookup(set, val) == BOOL_TRUE)
    {
        result->status = SET_DUPLICATE_ELEMENT;
    }
    else
    {
        Node *node = _get_new_node(val);
        if (set->tail != NULL)
        {
            set->tail->next = node;
            set->tail = node;
        }
        else
        {
            set->head = set->tail = node;
        }
        set->length += 1;
        assert((set->length == 1 && set->head == set->tail) ||
               (set->length > 1 && set->head != set->tail));
    }
    return set;
}

//Avoid multiple return statements when possible.
uint8_t set_lookup(const Set *set, int32_t key)
{
    assert(set != NULL);
    Node *cur = set->head;
    for (cur = set->head; cur != NULL; cur = cur->next)
    {
        if (cur->data == key)
        {
            break;
        }
    }
    return cur != NULL;
}

Set *set_delnode_head(Set *set)
{
    assert(set != NULL);
    if (set->head != NULL)
    {
        Node *temp = set->head;
        set->head = set->head->next;
        if (set->head == NULL)
        {
            set->tail = NULL;
        }
        set->length -= 1;
        free(temp);
    }
    return set;
}

Set *set_delnode_tail(Set *set)
{
    assert(set != NULL);
    if (set->tail != NULL)
    {
        Node *last = set->tail;
        if (set->tail == set->head)
        {
            set->tail = set->head = NULL;
        }
        else
        {
            Node *cur = set->head;
            for (cur = set->head; cur->next != last; cur = cur->next)
                ;
            set->tail = cur;
            cur->next = NULL;
        }
        set->length -= 1;
        free(last);
    }
    return set;
}

int32_t set_find_max_element(const Set *set)
{
    assert(set != NULL);
    int32_t max = INT32_MIN;
    if (set->head != NULL)
    {
        Node *cur;
        for (cur = set->head; cur != NULL; cur = cur->next)
        {
            if (cur->data > max)
            {
                max = cur->data;
            }
        }
    }
    return max;
}

int32_t set_find_min_element(const Set *set)
{
    assert(set != NULL);
    int32_t min = INT32_MAX;
    if (set->head != NULL)
    {
        Node *cur;
        for (cur = set->head; cur != NULL; cur = cur->next)
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
Set *set_add_element_after(Set *set, int32_t after_this, int32_t val, SetResult* result)
{
    assert(set != NULL);
    if (set_lookup(set, val) == BOOL_TRUE)
    {
        result->status = SET_DUPLICATE_ELEMENT;
    }
    else
    {
        if (set->head != NULL)
        {
            Node *cur;
            for (cur = set->head; cur != NULL; cur = cur->next)
            {
                if (cur->data == after_this)
                {
                    Node *new = _get_new_node(val);
                    Node *next = cur->next;
                    new->next = next;
                    cur->next = new;
                    set->length += 1;
                }
            }
        }
    }
    return set;
}

BOOL set_equals(const Set *set1, const Set *set2)
{
    assert(set1 != NULL && set2 != NULL);
    BOOL is_equal = BOOL_FALSE;
    if (set1->length == set2->length)
    {
        Node *cur1;
        Node *cur2;
        is_equal = BOOL_TRUE;

        for (cur1 = set1->head, cur2 = set2->head; cur1 != NULL; cur1 = cur1->next, cur2 = cur2->next)
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

Set *set_reverse_elements(const Set *set, Set *new_set)
{
    assert(set != NULL);
    if (set->length > 0)
    {
        Node *cur;
        SetResult result;
        for (cur = set->head; cur != NULL; cur = cur->next)
        {
            new_set = set_addnode_head(new_set, cur->data, &result);
        }
    }
    return new_set;
}

//TODO improve efficiency
Set *set_union(const Set *set1, const Set *set2, Set *new_set)
{
    assert(set1 != NULL && set2 != NULL);
    Node *cur;
    SetResult result;
    for (cur = set2->head; cur != NULL; cur = cur->next)
    {
        if (set_lookup(set1, cur->data) == BOOL_FALSE)
        {
            new_set = set_addnode_tail(new_set, cur->data, &result);
        }
    }
    for (cur = set1->head; cur != NULL; cur = cur->next)
    {
        set_addnode_tail(new_set, cur->data, &result);
    }
    return new_set;
}

Set *set_intersection(const Set *set1, const Set *set2, Set *new_set)
{
    assert(set1 != NULL && set2 != NULL);
    Node *cur;
    SetResult result;
    for (cur = set2->head; cur != NULL; cur = cur->next)
    {
        if (set_lookup(set1, cur->data) == BOOL_TRUE)
        {
            new_set = set_addnode_tail(new_set, cur->data, &result);
        }
    }
    return new_set;
}

void set_to_string(const Set *set)
{
    assert(set != NULL);
    Node *cur;
    log_debug("Set{length: %d, elements: [", set->length);
    for (cur = set->head; cur != NULL; cur = cur->next)
    {
        log_debug("%d", cur->data);
    }
    log_debug("]}");
}

//TODO avoid O(n^2)
Set *set_del_element(Set *set, int32_t key)
{
    assert(set != NULL);
    Node *cur = set->head;
    for (cur = set->head; cur != NULL; cur = cur->next)
    {
        if (cur->data == key)
        {
            if (set->tail == set->head)
            {
                set->tail = set->head = NULL;
            }
            else if (cur == set->head)
            {
                Node *next = cur->next;
                set->head = next;
                cur->next = NULL;
            }
            else
            {
                Node *prev = set->head;
                for (prev = set->head; prev->next != cur; prev = prev->next)
                    ;
                prev->next = cur->next;
                cur->next = NULL;
                if (cur == set->tail)
                {
                    set->tail = prev;
                }
            }
            set->length -= 1;
            free(cur);
            break;
        }
    }
    return set;
}
