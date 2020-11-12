#include <assert.h>

#include "set.h"
#include "log.h"

void test_set_empty_set()
{
    Set s1 = set_new();
    Set *set = &s1;
    assert(set_length(set) == 0);
}

void test_set_add_at_head()
{
    Set sl = set_new();
    Set *set = &sl;
    SetResult result;
    assert(set_length(set) == 0);
    set = set_addnode_head(set, 10, &result);
    assert(set_length(set) == 1);
    set = set_addnode_head(set, 20, &result);
    set = set_addnode_head(set, 30, &result);
    assert(set_length(set) == 3);
    assert(set_lookup(set, 20) == 1);
}

void test_set_add_at_tail()
{
    Set sl = set_new();
    Set *set = &sl;
    SetResult result;
    assert(set_length(set) == 0);
    set = set_addnode_tail(set, 10, &result);
    assert(set_length(set) == 1);
    set = set_addnode_tail(set, 20, &result);
    set = set_addnode_tail(set, 30, &result);
    assert(set_length(set) == 3);
    assert(set_lookup(set, 10) == 1);
}

void test_set_del_head()
{
    Set sl = set_new();
    Set *set = &sl;
    SetResult result;
    set = set_addnode_head(set, 10, &result);
    set = set_addnode_head(set, 20, &result);
    set = set_addnode_head(set, 30, &result);
    assert(set_length(set) == 3);
    set_delnode_head(set);
    assert(set_length(set) == 2 && set_lookup(set, 30) == 0 && set_lookup(set, 20) == 1);
    set = set_addnode_head(set, 40, &result);
    set_delnode_head(set);
    assert(set_length(set) == 2);
}

void test_set_del_tail()
{
    Set sl = set_new();
    Set *set = &sl;
    SetResult result;
    set = set_addnode_head(set, 10, &result);
    set = set_addnode_head(set, 20, &result);
    set = set_addnode_head(set, 30, &result);
    assert(set_length(set) == 3);
    set_delnode_tail(set);
    assert(set_length(set) == 2 && set_lookup(set, 10) == 0 && set_lookup(set, 20) == 1);
    set = set_addnode_head(set, 40, &result);
    set_delnode_tail(set);
    assert(set_length(set) == 2);
}

void test_set_find_max_element()
{
    Set sl = set_new();
    Set *set = &sl;
    SetResult result;
    set = set_addnode_tail(set, 10, &result);
    set = set_addnode_tail(set, 50, &result);
    set = set_addnode_tail(set, 30, &result);
    set = set_addnode_tail(set, 20, &result);
    assert(set_find_max_element(set) == 50);
}

void test_set_find_min_element()
{
    Set sl = set_new();
    Set *set = &sl;
    SetResult result;
    set = set_addnode_tail(set, 50, &result);
    set = set_addnode_tail(set, 10, &result);
    set = set_addnode_tail(set, 30, &result);
    set = set_addnode_tail(set, 20, &result);
    set = set_addnode_tail(set, 5, &result);
    assert(set_find_min_element(set) == 5);
}

void test_set_add_element_after()
{
    Set sl = set_new();
    Set *set = &sl;
    SetResult result;
    set = set_addnode_tail(set, 10, &result);
    set = set_addnode_tail(set, 20, &result);
    set = set_addnode_tail(set, 30, &result);
    set = set_add_element_after(set, 20, 25, &result);
    assert(set_length(set) == 4 && set_lookup(set, 25) == 1);
}

void test_set_equals()
{
    Set sl1 = set_new();
    Set *set1 = &sl1;
    SetResult result;
    set1 = set_addnode_tail(set1, 10, &result);
    set1 = set_addnode_tail(set1, 20, &result);

    Set sl2 = set_new();
    Set *set2 = &sl2;
    set2 = set_addnode_tail(set2, 10, &result);
    set2 = set_addnode_tail(set2, 20, &result);

    assert(set_equals(set1, set2) == BOOL_TRUE);
}

void test_set_reverse(){
    Set sl = set_new();
    Set *set = &sl;
    SetResult result;
    set = set_addnode_tail(set, 10, &result);
    set = set_addnode_tail(set, 20, &result);
    set = set_addnode_tail(set, 30, &result);

    Set sl2 = set_new();
    Set *set2 = &sl2;
    Set* rev_set = set_reverse_elements(set, set2);
    assert(set_length(rev_set) == 3 && rev_set->head->data == 30 && rev_set->tail->data == 10);
}

void test_set_union()
{
    Set sl1 = set_new();
    Set *set1 = &sl1;
    SetResult result;
    set1 = set_addnode_tail(set1, 10, &result);
    set1 = set_addnode_tail(set1, 30, &result);

    Set sl2 = set_new();
    Set *set2 = &sl2;
    set2 = set_addnode_tail(set2, 10, &result);
    set2 = set_addnode_tail(set2, 40, &result);

    Set sl3 = set_new();
    Set *new_set = &sl3;
    Set* set3 = set_union(set1, set2, new_set);
    //TODO more asserts
    assert(set_length(set3) == 3);
}

void test_set_intersection()
{
    Set sl1 = set_new();
    Set *set1 = &sl1;
    SetResult result;
    set1 = set_addnode_tail(set1, 10, &result);
    set1 = set_addnode_tail(set1, 30, &result);

    Set sl2 = set_new();
    Set *set2 = &sl2;
    set2 = set_addnode_tail(set2, 10, &result);
    set2 = set_addnode_tail(set2, 40, &result);

    Set sl3 = set_new();
    Set *new_set = &sl3;
    Set* set3 = set_intersection(set1, set2, new_set);
    //TODO more asserts
    assert(set_length(set3) == 1);
}

void test_set_del_element1()
{
    Set sl = set_new();
    Set *set = &sl;
    SetResult result;
    set = set_addnode_tail(set, 10, &result);
    set = set_del_element(set, 10);
    assert(set_length(set) == 0 && set_lookup(set, 10) == BOOL_FALSE);
}

void test_set_del_element2()
{
    Set sl = set_new();
    Set *set = &sl;
    SetResult result;
    set = set_addnode_tail(set, 10, &result);
    set = set_addnode_tail(set, 20, &result);
    set = set_del_element(set, 20);
    assert(set_length(set) == 1 && set_lookup(set, 20) == BOOL_FALSE);
}

void test_set_del_element2_1()
{
    Set sl = set_new();
    Set *set = &sl;
    SetResult result;
    set = set_addnode_tail(set, 10, &result);
    set = set_addnode_tail(set, 20, &result);
    set = set_del_element(set, 10);
    assert(set_length(set) == 1 && set_lookup(set, 10) == BOOL_FALSE);
}

void test_set_del_element3()
{
    Set sl = set_new();
    Set *set = &sl;
    SetResult result;
    set = set_addnode_tail(set, 10, &result);
    set = set_addnode_tail(set, 20, &result);
    set = set_addnode_tail(set, 30, &result);
    set = set_del_element(set, 20);
    assert(set_length(set) == 2 && set_lookup(set, 20) == BOOL_FALSE);
}

void test_set_del_element(){
    test_set_del_element1();
    test_set_del_element2();
    test_set_del_element2_1();
    test_set_del_element3();
}

void test_set_add_at_head_duplicate()
{
    Set sl = set_new();
    Set *set = &sl;
    SetResult result;
    set = set_addnode_head(set, 10, &result);
    set = set_addnode_head(set, 20, &result);
    set = set_addnode_head(set, 20, &result);
    assert(result.status == SET_DUPLICATE_ELEMENT && set_length(set) == 2);
}

void test_set_add_at_tail_duplicate()
{
    Set sl = set_new();
    Set *set = &sl;
    SetResult result;
    set = set_addnode_tail(set, 10, &result);
    set = set_addnode_tail(set, 20, &result);
    set = set_addnode_tail(set, 20, &result);
    assert(result.status == SET_DUPLICATE_ELEMENT && set_length(set) == 2);
}

void test_set_add_element_after_duplicate()
{
    Set sl = set_new();
    Set *set = &sl;
    SetResult result;
    set = set_addnode_tail(set, 10, &result);
    set = set_addnode_tail(set, 20, &result);
    set = set_add_element_after(set, 20, 10, &result);
    assert(result.status == SET_DUPLICATE_ELEMENT && set_length(set) == 2);
}

void test_set(){
    test_set_empty_set();
    test_set_add_at_head();
    test_set_add_at_tail();
    test_set_del_head();
    test_set_del_tail();
    test_set_find_max_element();
    test_set_find_min_element();
    test_set_add_element_after();
    test_set_equals();
    test_set_reverse();
    test_set_union();
    test_set_intersection();
    test_set_del_element();

    test_set_add_at_head_duplicate();
    test_set_add_at_tail_duplicate();
    test_set_add_element_after_duplicate();
}