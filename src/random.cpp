#include "Random.h"

#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <ctime>

Random* Random::generatorInstance = 0;

Random* Random::Generate()
{
    if (!generatorInstance)
        generatorInstance = new Random();
    return generatorInstance;
}

Random::Random()
{
    base = ~(unsigned long)0 - 1; // oxff..fe
    seedsNb = (unsigned long)2096;
    multiplier = (unsigned long)1047570;
    carry = (unsigned long)123;

    carry = (carry & (base + 1)) % multiplier;
    seeds = new unsigned long[seedsNb];
    srand(time(NULL));
    for (unsigned i = 0; i < seedsNb; ++i) {
        seeds[i] = (unsigned long)rand() & base;
        if (seeds[i] == (base + 1))
            seeds[i] = 1;
    }

    index = 0; // index of first carry
}

Random::~Random()
{
    delete[] seeds;
}

unsigned long Random::getRand()
{
    // t    = a * x_n-r +c_n-1
    // x_n  = (b-1) - t
    // c_n  = t/b
    unsigned long long t = multiplier * (unsigned long long)seeds[index] + carry;
    carry = t / (unsigned long long)base;
    seeds[index] = (base - 1) - (t & (base | 1));
    unsigned long result = seeds[index];
    index = (index + 1) & (seedsNb - 1);
    return (result);
}

long double Random::uniform(long double a, long double b)
{
    long double uniform_0_1 = (long double)getRand() / (long double)(~(unsigned long)0);
    if (uniform_0_1 == 1)
        uniform_0_1 = (long double)getRand() / (long double)(~(unsigned long)0);
    return uniform_0_1 * (b - a) + a;
}

long Random::intuniform(long a, long b)
{
    return (getRand() % (b - a + 1) + a);
}

long double Random::exponential(long double lambda)
{
    return -log(uniform(0, 1)) / lambda;
}

unsigned Random::poisson(long double lambda)
{
    long double l = exp(-lambda), p = uniform(0, 1);
    unsigned k = 0;
    while (p > l) {
        ++k;
        p *= uniform(0, 1);
    }
    return (k);
}

unsigned Random::bernoulli(long double p)
{
    return (uniform(0, 1) < p ? 1 : 0);
}

unsigned Random::binomial(unsigned n, long double p)
{
    unsigned v = 0;
    for (unsigned i = 0; i < n; ++i)
        v += bernoulli(p);
    return v;
}

long double Random::normal(long double mean, long double stddev)
{
    long double z = cos(2 * M_PI * uniform(0, 1)) * sqrt(-2 * log(uniform(0, 1)));
    return mean + stddev * z;
}

long double Random::lognormal(long double mean, long double stddev)
{
    long double mean_log = log(mean) - log(1 + (stddev * stddev) / (mean * mean)) / 2;
    long double stddev_log = sqrt(log(1 + (stddev * stddev) / (mean * mean)));
    long double r1 = sqrt(-2 * log(uniform(0, 1))) * sin(2 * M_PI * uniform(0, 1));
    return exp(mean_log + stddev_log * r1);
}
