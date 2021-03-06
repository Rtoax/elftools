#include <malloc.h>
#include <string.h>

#include <utils/log.h>
#include <utils/list.h>
#include <utils/task.h>

#include "test_api.h"

struct test*
create_test(char *category, char *name, test_prio prio, int (*cb)(void),
	int expect_ret)
{
	struct test *test = malloc(sizeof(struct test));
	test->category = strdup(category);
	test->name = strdup(name);
	test->prio = prio;
	test->test_cb = cb;
	test->expect_ret = expect_ret;

	list_add(&test->node, &test_list[prio - TEST_PRIO_START]);

	return test;
}

void release_tests(void)
{
	int i;
	struct test *test, *tmp;

	// for each priority
	for (i = 0; i < TEST_PRIO_NUM; i++) {
		// for each test entry
		list_for_each_entry_safe(test, tmp, &test_list[i], node) {
			list_del(&test->node);
			free(test->category);
			free(test->name);
			free(test);
		}
	}
}

