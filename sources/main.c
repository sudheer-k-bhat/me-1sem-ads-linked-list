#include <assert.h>

#include "slist.h"
#include "log.h"

void test_empty_list()
{
    SList slist = slist_new();
    SList *list = &slist;
    assert(slist_length(list) == 0);
}

void test_add_at_head()
{
    SList sl = slist_new();
    SList *list = &sl;
    assert(slist_length(list) == 0);
    list = slist_addnode_head(list, 10);
    assert(slist_length(list) == 1);
    list = slist_addnode_head(list, 20);
    list = slist_addnode_head(list, 30);
    assert(slist_length(list) == 3);
    assert(slist_lookup(list, 20) == 1);
}

void test_add_at_tail()
{
    SList sl = slist_new();
    SList *list = &sl;
    assert(slist_length(list) == 0);
    list = slist_addnode_tail(list, 10);
    assert(slist_length(list) == 1);
    list = slist_addnode_tail(list, 20);
    list = slist_addnode_tail(list, 30);
    assert(slist_length(list) == 3);
    assert(slist_lookup(list, 10) == 1);
}

void test_del_head()
{
    SList sl = slist_new();
    SList *list = &sl;
    list = slist_addnode_head(list, 10);
    list = slist_addnode_head(list, 20);
    list = slist_addnode_head(list, 30);
    assert(slist_length(list) == 3);
    slist_delnode_head(list);
    assert(slist_length(list) == 2 && slist_lookup(list, 30) == 0 && slist_lookup(list, 20) == 1);
    list = slist_addnode_head(list, 40);
    slist_delnode_head(list);
    assert(slist_length(list) == 2);
}

void test_del_tail()
{
    SList sl = slist_new();
    SList *list = &sl;
    list = slist_addnode_head(list, 10);
    list = slist_addnode_head(list, 20);
    list = slist_addnode_head(list, 30);
    assert(slist_length(list) == 3);
    slist_delnode_tail(list);
    assert(slist_length(list) == 2 && slist_lookup(list, 10) == 0 && slist_lookup(list, 20) == 1);
    list = slist_addnode_head(list, 40);
    slist_delnode_tail(list);
    assert(slist_length(list) == 2);
}

void test_find_max_element()
{
    SList sl = slist_new();
    SList *list = &sl;
    list = slist_addnode_tail(list, 10);
    list = slist_addnode_tail(list, 50);
    list = slist_addnode_tail(list, 30);
    list = slist_addnode_tail(list, 20);
    assert(slist_find_max_element(list) == 50);
}

void test_find_min_element()
{
    SList sl = slist_new();
    SList *list = &sl;
    list = slist_addnode_tail(list, 50);
    list = slist_addnode_tail(list, 10);
    list = slist_addnode_tail(list, 30);
    list = slist_addnode_tail(list, 20);
    list = slist_addnode_tail(list, 5);
    assert(slist_find_min_element(list) == 5);
}

void test_slist_add_element_after()
{
    SList sl = slist_new();
    SList *list = &sl;
    list = slist_addnode_tail(list, 10);
    list = slist_addnode_tail(list, 20);
    list = slist_addnode_tail(list, 30);
    list = slist_add_element_after(list, 20, 25);
    assert(slist_length(list) == 4 && slist_lookup(list, 25) == 1);
}

void test_slist_equals()
{
    SList sl1 = slist_new();
    SList *list1 = &sl1;
    list1 = slist_addnode_tail(list1, 10);
    list1 = slist_addnode_tail(list1, 20);

    SList sl2 = slist_new();
    SList *list2 = &sl2;
    list2 = slist_addnode_tail(list2, 10);
    list2 = slist_addnode_tail(list2, 20);

    assert(slist_equals(list1, list2) == BOOL_TRUE);
}

void test_slist_reverse(){
    SList sl = slist_new();
    SList *list = &sl;
    list = slist_addnode_tail(list, 10);
    list = slist_addnode_tail(list, 20);
    list = slist_addnode_tail(list, 30);
    list = slist_reverse_elements(list);
    assert(slist_length(list) == 3 && list->head->data == 30 && list->tail->data == 10);
}

void test_slist_union()
{
    SList sl1 = slist_new();
    SList *list1 = &sl1;
    list1 = slist_addnode_tail(list1, 10);
    list1 = slist_addnode_tail(list1, 30);

    SList sl2 = slist_new();
    SList *list2 = &sl2;
    list2 = slist_addnode_tail(list2, 10);
    list2 = slist_addnode_tail(list2, 40);

    SList* list3 = slist_union(list1, list2);
    assert(slist_length(list3) == 3);
    slist_to_string(list3);
}

int main()
{
    test_empty_list();
    test_add_at_head();
    test_add_at_tail();
    test_del_head();
    test_del_tail();
    test_find_max_element();
    test_find_min_element();
    test_slist_add_element_after();
    test_slist_equals();
    test_slist_reverse();
    test_slist_union();
    return 0;
}