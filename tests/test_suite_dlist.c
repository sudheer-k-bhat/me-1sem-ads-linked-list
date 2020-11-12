#include <assert.h>

#include "dlist.h"

void test_dlist_empty_list()
{
    DList slist = dlist_new();
    DList *list = &slist;
    assert(dlist_length(list) == 0);
}

void test_dlist_add_at_head()
{
    DList sl = dlist_new();
    DList *list = &sl;
    assert(dlist_length(list) == 0);
    list = dlist_addnode_head(list, 10);
    assert(dlist_length(list) == 1);
    list = dlist_addnode_head(list, 20);
    list = dlist_addnode_head(list, 30);
    assert(dlist_length(list) == 3);
    assert(dlist_lookup(list, 20) == 1);
}

void test_dlist_add_at_tail()
{
    DList sl = dlist_new();
    DList *list = &sl;
    assert(dlist_length(list) == 0);
    list = dlist_addnode_tail(list, 10);
    assert(dlist_length(list) == 1);
    list = dlist_addnode_tail(list, 20);
    list = dlist_addnode_tail(list, 30);
    assert(dlist_length(list) == 3);
    assert(dlist_lookup(list, 10) == 1);
}

void test_dlist_del_head()
{
    DList sl = dlist_new();
    DList *list = &sl;
    list = dlist_addnode_head(list, 10);
    list = dlist_addnode_head(list, 20);
    list = dlist_addnode_head(list, 30);
    assert(dlist_length(list) == 3);
    dlist_delnode_head(list);
    assert(dlist_length(list) == 2 && dlist_lookup(list, 30) == 0 && dlist_lookup(list, 20) == 1);
    list = dlist_addnode_head(list, 40);
    dlist_delnode_head(list);
    assert(dlist_length(list) == 2);
}

void test_dlist_del_tail()
{
    DList sl = dlist_new();
    DList *list = &sl;
    list = dlist_addnode_head(list, 10);
    list = dlist_addnode_head(list, 20);
    list = dlist_addnode_head(list, 30);
    assert(dlist_length(list) == 3);
    dlist_delnode_tail(list);
    assert(dlist_length(list) == 2 && dlist_lookup(list, 10) == 0 && dlist_lookup(list, 20) == 1);
    list = dlist_addnode_head(list, 40);
    dlist_delnode_tail(list);
    assert(dlist_length(list) == 2);
}

void test_dlist_find_max_element()
{
    DList sl = dlist_new();
    DList *list = &sl;
    list = dlist_addnode_tail(list, 10);
    list = dlist_addnode_tail(list, 50);
    list = dlist_addnode_tail(list, 30);
    list = dlist_addnode_tail(list, 20);
    assert(dlist_find_max_element(list) == 50);
}

void test_dlist_find_min_element()
{
    DList sl = dlist_new();
    DList *list = &sl;
    list = dlist_addnode_tail(list, 50);
    list = dlist_addnode_tail(list, 10);
    list = dlist_addnode_tail(list, 30);
    list = dlist_addnode_tail(list, 20);
    list = dlist_addnode_tail(list, 5);
    assert(dlist_find_min_element(list) == 5);
}

void test_dlist_add_element_after()
{
    DList sl = dlist_new();
    DList *list = &sl;
    list = dlist_addnode_tail(list, 10);
    list = dlist_addnode_tail(list, 20);
    list = dlist_addnode_tail(list, 30);
    list = dlist_add_element_after(list, 20, 25);
    assert(dlist_length(list) == 4 && dlist_lookup(list, 25) == 1);
}

void test_dlist_equals()
{
    DList sl1 = dlist_new();
    DList *list1 = &sl1;
    list1 = dlist_addnode_tail(list1, 10);
    list1 = dlist_addnode_tail(list1, 20);

    DList sl2 = dlist_new();
    DList *list2 = &sl2;
    list2 = dlist_addnode_tail(list2, 10);
    list2 = dlist_addnode_tail(list2, 20);

    assert(dlist_equals(list1, list2) == BOOL_TRUE);
}

void test_dlist_reverse(){
    DList sl = dlist_new();
    DList *list = &sl;
    list = dlist_addnode_tail(list, 10);
    list = dlist_addnode_tail(list, 20);
    list = dlist_addnode_tail(list, 30);

    DList sl2 = dlist_new();
    DList *list2 = &sl2;
    DList* rev_list = dlist_reverse_elements(list, list2);
    assert(dlist_length(rev_list) == 3 && rev_list->head->data == 30 && rev_list->tail->data == 10);
}

void test_dlist_union()
{
    DList sl1 = dlist_new();
    DList *list1 = &sl1;
    list1 = dlist_addnode_tail(list1, 10);
    list1 = dlist_addnode_tail(list1, 30);

    DList sl2 = dlist_new();
    DList *list2 = &sl2;
    list2 = dlist_addnode_tail(list2, 10);
    list2 = dlist_addnode_tail(list2, 40);

    DList sl3 = dlist_new();
    DList *new_list = &sl3;
    DList* list3 = dlist_union(list1, list2, new_list);
    //TODO more asserts
    assert(dlist_length(list3) == 3);
}

void test_dlist_intersection()
{
    DList sl1 = dlist_new();
    DList *list1 = &sl1;
    list1 = dlist_addnode_tail(list1, 10);
    list1 = dlist_addnode_tail(list1, 30);

    DList sl2 = dlist_new();
    DList *list2 = &sl2;
    list2 = dlist_addnode_tail(list2, 10);
    list2 = dlist_addnode_tail(list2, 40);

    DList sl3 = dlist_new();
    DList *new_list = &sl3;
    DList* list3 = dlist_intersection(list1, list2, new_list);
    //TODO more asserts
    assert(dlist_length(list3) == 1);
}

void test_dlist_del_element1()
{
    DList sl = dlist_new();
    DList *list = &sl;
    list = dlist_addnode_tail(list, 10);
    list = dlist_del_element(list, 10);
    assert(dlist_length(list) == 0 && dlist_lookup(list, 10) == BOOL_FALSE);
}

void test_dlist_del_element2()
{
    DList sl = dlist_new();
    DList *list = &sl;
    list = dlist_addnode_tail(list, 10);
    list = dlist_addnode_tail(list, 20);
    list = dlist_del_element(list, 20);
    assert(dlist_length(list) == 1 && dlist_lookup(list, 20) == BOOL_FALSE);
}

void test_dlist_del_element2_1()
{
    DList sl = dlist_new();
    DList *list = &sl;
    list = dlist_addnode_tail(list, 10);
    list = dlist_addnode_tail(list, 20);
    list = dlist_del_element(list, 10);
    assert(dlist_length(list) == 1 && dlist_lookup(list, 10) == BOOL_FALSE);
}

void test_dlist_del_element3()
{
    DList sl = dlist_new();
    DList *list = &sl;
    list = dlist_addnode_tail(list, 10);
    list = dlist_addnode_tail(list, 20);
    list = dlist_addnode_tail(list, 30);
    list = dlist_del_element(list, 20);
    assert(dlist_length(list) == 2 && dlist_lookup(list, 20) == BOOL_FALSE);
}

void test_dlist_del_element(){
    test_dlist_del_element1();
    test_dlist_del_element2();
    test_dlist_del_element2_1();
    test_dlist_del_element3();
}

void test_dlist(){
    test_dlist_empty_list();
    test_dlist_add_at_head();
    test_dlist_add_at_tail();
    test_dlist_del_head();
    test_dlist_del_tail();
    test_dlist_find_max_element();
    test_dlist_find_min_element();
    test_dlist_add_element_after();
    test_dlist_equals();
    test_dlist_reverse();
    test_dlist_union();
    test_dlist_intersection();
    test_dlist_del_element();
}