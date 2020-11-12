#!/bin/sh
rm -rf bin/out
gcc -I headers/ lib/log.c sources/slist.c tests/test_suite_slist.c sources/set.c tests/test_suite_set.c sources/dlist.c tests/test_suite_dlist.c sources/main.c -o bin/out
bin/out