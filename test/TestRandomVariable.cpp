#include "RandomVariable.h"

#include "catch2/catch.hpp"

#include <iostream>

TEST_CASE("Random numbers can be generated, with distribution", "[Random][RandomVariable]")
{
    int nbSamples = 100;

    RandomVariable X;
    double mean, sample;

    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;

    X.setBernoulli(0.3);
    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;

    X.setUniform(0, 1);
    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;

    X.setIntUniform(0, 10);
    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;

    X.setBinomial(10, 0.3);
    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;

    X.setNormal(0, 1);
    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;

    X.setPoisson(5);
    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;

    X.setExponential(5);
    std::cout << "Generating " << nbSamples << " of random variable X, of type '" << X.typeString() << "'" << std::endl;
    mean = 0;
    for (int i = 0; i < nbSamples; ++i) {
        sample = X.generateSample();
        mean += sample;
        std::cout << sample << " ";
    }
    std::cout << std::endl
              << "(Mean = " << mean / nbSamples << " )" << std::endl;
}