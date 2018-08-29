#include <stdio.h>

#define test_assert(message, test) \
	if (test) { \
		printf("OK    %03i: %s\n", ++test_count, message); \
		test_pass++; \
	} else { \
		printf("FAIL  %03i: %s\n", ++test_count, message); \
	}

#define test_summary() \
	printf("tests passed: %i/%i\n", test_pass, test_count);

int test_count = 0;
int test_pass = 0;
