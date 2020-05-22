#include "UniqueIDGenerator.h"
#include "common.h"

#include "catch2/catch.hpp"

#include <iostream>

TEST_CASE("UniqueIDGenerator generates module and particle IDs", "[UniqueIDGenerator]")
{
    for (long i = 0; i < 1000; i++)
        std::cout << i << " : "
                  << " module= " << UniqueIDGenerator<ModuleId>::Generator()->newId()
                  << " client= " << UniqueIDGenerator<ParticleId>::Generator()->newId()
                  << std::endl;
}