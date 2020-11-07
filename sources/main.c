#include <assert.h>

#include "slist.h"

void test_empty_list(){
    SList slist = slist_new();
    SList *list = &slist;
    assert(slist_length(list) == 0);
}

void test_add_at_head(){
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

void test_add_at_tail(){
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

void test_del_head(){
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

void test_del_tail(){
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

void test_find_max_element(){
    SList sl = slist_new();
    SList *list = &sl;
    list = slist_addnode_tail(list, 10);
    list = slist_addnode_tail(list, 50);
    list = slist_addnode_tail(list, 30);
    list = slist_addnode_tail(list, 20);
    assert(slist_find_max_element(list) == 50);
}

void test_find_min_element(){
    SList sl = slist_new();
    SList *list = &sl;
    list = slist_addnode_tail(list, 50);
    list = slist_addnode_tail(list, 10);
    list = slist_addnode_tail(list, 30);
    list = slist_addnode_tail(list, 20);
    list = slist_addnode_tail(list, 5);
    assert(slist_find_min_element(list) == 5);
}

int main(){
    test_empty_list();
    test_add_at_head();
    test_add_at_tail();
    test_del_head();
    test_del_tail();
    test_find_max_element();
    test_find_min_element();
    return 0;
}