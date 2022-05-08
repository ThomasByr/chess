#include "macros.h"

#include "lib.h"

#include "app.h"

unsigned long _no_asserts = 0;

const bool WHITE_IS_FILLED = true;
State state = State::PROGRAM_STARTING;


void dummy_test() {
    assert_eq(1, 1);
    assert_neq(1, 2);
    assert_lt(1, 2);
    assert_gt(2, 1);
    assert_leq(1, 1);
    assert_geq(2, 2);
}

int main() {
    test_case(dummy_test);

    return 0;
}
