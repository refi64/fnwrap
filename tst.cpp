#include "fnwrap.hpp"
#include <iostream>


int f() { return 0; }
void g(int x, char y) {}


void before(int n) { std::cout << "before: " << n << '\n'; }
void after(int n) { std::cout << "after: " << n << '\n'; }


FNWRAP(f, w_f, before(0), after(0))
FNWRAP(g, w_g, before(a0), after(a0))

int main() {
    std::cout << "result: " << w_f() << '\n';
    w_g(10, 11);
    w_g(11, 12);
    return 0;
}
