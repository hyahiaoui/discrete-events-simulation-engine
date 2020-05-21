#ifndef RANDOM_H
#define RANDOM_H

/**
  * \brief  A singleton class providing randomly generated number.
  *
  * Invocation of random numbers generations is done with:
  *     x = cRandom::Generate()->Distribution_Name( Distribution_Params );
  * where, Distribution_Name can be one of the following discrete distributions
  * -   bernoulli, to produce values of a Bernoulli distribution (1 with probability p, 0 with probability 1-p)
  * -   intuniform, to produce uniformly distributed integer values in an interval
  * -   binomial, to produce values of a binomial distribution with the given parameters
  * -   poisson, to produce values of a Poisson distribution with the given parameter
  * or, one the following continuous distributions
  * -   uniform, to produce uniformly distributed real values in an interval
  * -   exponential, to produce values of an Exponential distribution with the given parameter
  * -   normal, to produce values of a Normal (Gaussian) distribution with the given mean and standard deviation
  * -   lognormal, to produce values of a Log-Normal distribution with the given mean and standard deviation
  */
class cRandom {
public:
    /**
      * \brief  Static, public, method to use when requesting random values from a random variable distribution
      */
    static cRandom* Generate();

    /**
      * \brief  Destructor
      *
      * This destructor is implicitly called by
      */
    ~cRandom();

    // Discrete Distributions
    /**
      * \brief  Produces a random integer number in interval [a,b]
      */
    long intuniform(long a, long b);

    /**
      * \brief  Produces a random value of distribution Bernoulli(p). It produces 1 with probability p, 0 with probability 1-p.
      */
    unsigned bernoulli(long double p);

    /**
      * \brief  Produces a random value of distribution Binomial(n, p). It produces the sum of n independent Bernoulli(p) trials
      */
    unsigned binomial(unsigned n, long double p);

    /**
      * \brief  Produces a random value of Poisson distribution with parameter lambda
      */
    unsigned poisson(long double lambda);

    // Continuous Distributions
    /**
      * \brief  Produces a random real number in interval [a,b[
      */
    long double uniform(long double a, long double b);

    /**
      * \brief  Produces an random value of exponential distribution with parameter lambda
      */
    long double exponential(long double lambda);

    /**
      * \brief  Produces a random value of Normal distribution
      * \param  mean    Mean value of the generated Normal distribution
      * \param  stddev  Standard deviation of the generated Normal distribution (Square root of its variance)
      */
    long double normal(long double mean, long double stddev);

    /**
      * \brief  Produces a random value of Log-Normal distribution
      * \param  mean    Mean value of the generated Normal distribution
      * \param  stddev  Standard deviation of the generated Normal distribution (Square root of its variance)
      */
    long double lognormal(long double mean, long double stddev);

private:
    // Private constructors and assignement operator to ensure singleton property
    cRandom();
    cRandom(const cRandom& other) { }
    cRandom& operator=(const cRandom& other) { return *this; }

    /**
      * \brief computes and returns next random number
      */
    unsigned long getRand();

    // Private attributs
    static cRandom* generatorInstance;

    unsigned long base;
    unsigned seedsNb;
    unsigned long* seeds;
    unsigned long multiplier;
    unsigned long carry;

    unsigned index;
};

#endif // RANDOM_H
