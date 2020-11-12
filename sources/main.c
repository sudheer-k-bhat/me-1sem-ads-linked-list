/**
 * Console app to test the functionality of linked list & set.
 * 
 * @author sudheer-k-bhat
 * @see files `test_suite_<datastructure-type>.h` for test cases implemented.
 **/
#include "test_suite_slist.h"
#include "test_suite_set.h"
#include "test_suite_dlist.h"

int main()
{
    test_slist();
    test_set();
    test_dlist();
    return 0;
}