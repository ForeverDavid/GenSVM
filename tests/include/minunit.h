/**
 * @file minunit.h
 * @brief Minimal unit testing framework for C
 * @author Zed Shaw
 *
 * @details
 * This unit testing framework comes from Zed Shaw's book Learn C The Hard 
 * Way, and are evolved from the "minunit" code snippets by Jera Design. I've 
 * added a mu_test_missing() macro to deal with missing unit tests.
 *
 * @sa dbg.h
 */

#undef NDEBUG
#ifndef _minunit_h
#define _minunit_h

#include "dbg.h"
#include <stdlib.h>

#define mu_suite_start() char *message = NULL

#define mu_assert(test, message) if (!(test)) { log_err(message); return message; }

#define mu_run_test(test) debug("\n-----%s", " " #test); \
	message = test(); tests_run++; if (message) return message;

#define RUN_TESTS(name) int main(int argc, char *argv[]) {\
	argc = 1; \
	debug("\n-----\nRUNNING: %s", argv[0]);\
	printf("----\nRUNNING: %s\n", argv[0]);\
	char *result = name();\
	if (result != 0) {\
		printf("\033[91mFAILED:\033[0m %s\n", result);\
	}\
	else {\
		printf("ALL TESTS \033[92mPASSED\033[0m\n");\
	}\
	printf("Tests run: %d\n", tests_run);\
	exit(result != 0);\
}

#define mu_test_missing() printf("\033[33;1mWARNING: Test missing\033[0m\n");\
	tests_run--;

int tests_run;

#endif
