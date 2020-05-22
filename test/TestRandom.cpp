#include "Random.h"

#include "catch2/catch.hpp"

#include <iostream>

TEST_CASE("Random numbers can be generated", "[Random]")
{
    const int n = 10;
    long long tab[n];
    for (int i = 0; i < n; i++)
        tab[i] = 0;

    for (long long i = 0; i < 1000000; i++) {
        long double l = 10 * Random::Generate()->uniform(0, 1);
        if ((l < 0) || (l >= 10)) {
            std::cout << "l=" << l << std::endl;
            continue;
        }
        tab[(int)(l)]++;
    }

    unsigned long long sum = 0;
    for (int i = 0; i < n; i++) {
        std::cout << i << " : " << tab[i] << std::endl;
        sum += tab[i];
    }
    std::cout << "sum= " << sum << std::endl;
}

TEST_CASE("Random numbers can be generated using a distribution", "[Random]")
{
    unsigned long nb1 = 0, nb0 = 0;
    for (long long i = 0; i < 10000000; i++) {
        if (Random::Generate()->bernoulli(0.66666666) == 0)
            ++nb0;
        else
            ++nb1;
    }
    std::cout << "Number of 0 = " << nb0 << std::endl;
    std::cout << "Number of 1 = " << nb1 << std::endl;
}