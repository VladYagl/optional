#include <iostream>
#include <string>

#include "optional.h"
#include "test.h"


using namespace std;

int main() {
	test test_obj;
	cout << endl;

	optional<string> a("some string");
	optional<string> b;
	optional<string> c(nullopt);
	optional<string> d(a);
	string s = "some string";
	optional<string> e(s);
	optional<string> f(move(e));
	optional<string> g = d;
	optional<string> i;
	i.emplace("some string");
	optional<string> j("some not string");
	j.emplace("some string");
	optional<string> k(implace, "somest string");
	optional<string> l = make_optional<string>(s);

	cout << a.value_or("some not string") << ' ' << (a ? "string" : "not string") << endl;
	cout << b.value_or("some not string") << ' ' << (b ? "string" : "not string") << endl;
	cout << c.value_or("some not string") << ' ' << (c ? "string" : "not string") << endl;
	cout << d.value_or("some not string") << ' ' << (d ? "string" : "not string") << endl;
	cout << e.value_or("some not string") << ' ' << (e ? "string" : "not string") << endl;
	cout << f.value_or("some not string") << ' ' << (f ? "string" : "not string") << endl;
	cout << g.value_or("some not string") << ' ' << (g ? "string" : "not string") << endl;
	cout << i.value_or("some not string") << ' ' << (i ? "string" : "not string") << endl;
	cout << j.value_or("some not string") << ' ' << (j ? "string" : "not string") << endl;
	cout << k.value_or("some not string") << ' ' << (k ? "string" : "not string") << endl;
	cout << l.value_or("some not string") << ' ' << (l ? "string" : "not string") << endl;
	cout << "----------------------------------" << endl << endl;
	swap(a, b);
	swap(c, d);
	swap(j, k);

	cout << a.value_or("some not string") << ' ' << (a ? "string" : "not string") << endl;
	cout << b.value_or("some not string") << ' ' << (b ? "string" : "not string") << endl;
	cout << c.value_or("some not string") << ' ' << (c ? "string" : "not string") << endl;
	cout << d.value_or("some not string") << ' ' << (d ? "string" : "not string") << endl;
	cout << e.value_or("some not string") << ' ' << (e ? "string" : "not string") << endl;
	cout << f.value_or("some not string") << ' ' << (f ? "string" : "not string") << endl;
	cout << g.value_or("some not string") << ' ' << (g ? "string" : "not string") << endl;
	cout << i.value_or("some not string") << ' ' << (i ? "string" : "not string") << endl;
	cout << j.value_or("some not string") << ' ' << (j ? "string" : "not string") << endl;
	cout << k.value_or("some not string") << ' ' << (k ? "string" : "not string") << endl;
	cout << l.value_or("some not string") << ' ' << (l ? "string" : "not string") << endl;
	cout << "----------------------------------" << endl << endl;

	cout << (a < b) << endl;
	cout << (c == b) << endl;

	return 0;
}