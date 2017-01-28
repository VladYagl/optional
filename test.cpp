#include "test.h"
#include <iostream>

using namespace std;

test::test() {
	data = make_optional<int>(10);
	cout << (data ? *data : -1) << endl;
}