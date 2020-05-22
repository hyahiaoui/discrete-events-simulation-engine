#define CATCH_CONFIG_RUNNER
#include "catch2/catch.hpp"

#include <ctime>

int main(int argc, char* argv[])
{
    // global setup...
    srand(time(NULL));

    int result = Catch::Session().run(argc, argv);

    // global clean-up...

    return result;
}