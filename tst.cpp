#include "fnwrap.hpp"

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"


int f() { return 0; }
int g(int x) { return x; }
void h(int x, int y) {}


int global=-1;

void before(int n) { global = n; }
void after(int n) { global += n; }


FNWRAP(f, basic_f,,)
FNWRAP(g, basic_g,,)
FNWRAP(h, basic_h,,)

FNWRAP(f, before_f, before(2),)
FNWRAP(g, before_g, before(a0),)
FNWRAP(h, before_h, before(a1),)

FNWRAP(f, before_after_f, before(2), after(10))
FNWRAP(g, before_after_g, before(a0), after(a0))
FNWRAP(h, before_after_h, before(a1), after(a0))


TEST_CASE("The basics work", "[basics]") {
    CHECK(basic_f() == 0);
    CHECK(basic_g(1) == 1);
    basic_h(1, 2);
}


TEST_CASE("before gets called", "[before]") {
    before_f();
    CHECK(global == 2);

    before_g(10);
    CHECK(global == 10);

    before_h(12, 36);
    CHECK(global == 36);
}


TEST_CASE("after gets called", "[after]") {
    before_after_f();
    CHECK(global == 12);

    before_after_g(10);
    CHECK(global == 20);

    before_after_h(12, 36);
    CHECK(global == 48);
}
