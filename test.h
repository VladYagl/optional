#ifndef TEST_H
#define TEST_H

#include "optional.h"

struct test {
	optional<int> data;

	test();
};

#endif