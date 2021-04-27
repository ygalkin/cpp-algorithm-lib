#define CATCH_CONFIG_RUNNER
#include "external/catch.hpp"

#include "smart-ptr/test.h"
#include "sort/test.h"
#include "container/test.h"

int main() {
    Catch::Session().run();

    smart_ptr::test().run();
    container::test().run();
    sort::test().run();
}