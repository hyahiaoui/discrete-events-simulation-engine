#include "randomvariable.h"
#include "random.h"

#include <cfloat>
#include <climits>
#include <cmath>

const std::vector<std::string> cRandomVariable::m_typesNames = {
    "Unusable", "Uniform", "IntUniform", "Bernoulli", "Binomial", "Poisson", "Exponential", "Normal", "LogNormal"
};

cRandomVariable::cRandomVariable(const VariableType varType, const double param1, const double param2)
    : m_category(cRandomVariable::Undefined)
    , m_type(cRandomVariable::Unusable)
    , m_param()
{
    switch (varType) {
    case Uniform:
        setUniform(param1, param2);
        break;
    case IntUniform:
        setIntUniform((int)param1, (int)param2);
        break;
    case Bernoulli:
        setBernoulli(param1);
        break;
    case Binomial:
        setBinomial((int)param1, param2);
        break;
    case Poisson:
        setPoisson(param1);
        break;
    case Exponential:
        setExponential(param1);
        break;
    case Normal:
        setNormal(param1, param2);
        break;
    case LogNormal:
        setLogNormal(param1, param2);
        break;
    default:
        break;
    }
}

void cRandomVariable::setUniform(const double bound1, const double bound2)
{
    m_type = Uniform;
    m_category = Continuous;
    m_param.uniformParam.lowerBound = bound1 < bound2 ? bound1 : bound2;
    m_param.uniformParam.upperBound = bound1 < bound2 ? bound2 : bound1;
}

void cRandomVariable::setIntUniform(const int bound1, const int bound2)
{
    m_type = IntUniform;
    m_category = Discrete;
    m_param.intUniformParam.lowerBound = bound1 < bound2 ? bound1 : bound2;
    m_param.intUniformParam.upperBound = bound1 < bound2 ? bound2 : bound1;
}

void cRandomVariable::setBernoulli(const double p)
{
    m_type = Bernoulli;
    m_category = Discrete;
    m_param.bernoulliParam = p;
}

void cRandomVariable::setBinomial(const unsigned n, const double p)
{
    m_type = Binomial;
    m_category = Discrete;
    m_param.binomialParam.nb = n;
    m_param.binomialParam.prob = p;
}

void cRandomVariable::setExponential(const double lambda)
{
    m_type = Exponential;
    m_category = Continuous;
    m_param.exponentialParam = lambda;
}

void cRandomVariable::setPoisson(const double lambda)
{
    m_type = Poisson;
    m_category = Discrete;
    m_param.poissonParam = lambda;
}

void cRandomVariable::setNormal(const double mean, const double standardDev)
{
    m_type = Normal;
    m_category = Continuous;
    m_param.normalParam.mean = mean;
    m_param.normalParam.stdDev = standardDev;
}

void cRandomVariable::setLogNormal(const double mean, const double standardDev)
{
    m_type = LogNormal;
    m_category = Continuous;
    m_param.lognormalParam.mean = mean;
    m_param.lognormalParam.stdDev = standardDev;
}

double cRandomVariable::generateSample() const
{
    switch (m_type) {
    case Uniform:
        return cRandom::Generate()->uniform(
            m_param.uniformParam.lowerBound,
            m_param.uniformParam.upperBound);
        break;
    case IntUniform:
        return cRandom::Generate()->intuniform(
            m_param.intUniformParam.lowerBound,
            m_param.intUniformParam.upperBound);
        break;
    case Bernoulli:
        return cRandom::Generate()->bernoulli(
            m_param.bernoulliParam);
        break;
    case Binomial:
        return cRandom::Generate()->binomial(
            m_param.binomialParam.nb,
            m_param.binomialParam.prob);
        break;
    case Poisson:
        return cRandom::Generate()->poisson(
            m_param.poissonParam);
        break;
    case Exponential:
        return cRandom::Generate()->exponential(
            m_param.exponentialParam);
        break;
    case Normal:
        return cRandom::Generate()->normal(
            m_param.normalParam.mean,
            m_param.normalParam.stdDev);
        break;
    case LogNormal:
        return cRandom::Generate()->lognormal(
            m_param.lognormalParam.mean,
            m_param.lognormalParam.stdDev);
        break;
    default:
        return 0;
        break;
    }
}

double cRandomVariable::mean() const
{
    switch (m_type) {
    case Uniform:
        return (m_param.uniformParam.lowerBound + m_param.uniformParam.upperBound) / 2;
        break;
    case IntUniform:
        return (m_param.intUniformParam.lowerBound + m_param.intUniformParam.upperBound) / 2;
        break;
    case Bernoulli:
        return m_param.bernoulliParam;
        break;
    case Binomial:
        return m_param.binomialParam.nb * m_param.binomialParam.prob;
        break;
    case Poisson:
        return m_param.poissonParam;
        break;
    case Exponential:
        return 1 / m_param.exponentialParam;
        break;
    case Normal:
        return m_param.normalParam.mean;
        break;
    case LogNormal:
        return m_param.lognormalParam.mean;
        break;
    default:
        return 0;
        break;
    }
}

double cRandomVariable::variance() const
{
    switch (m_type) {
    case Uniform:
        return (m_param.uniformParam.upperBound - m_param.uniformParam.lowerBound)
            * (m_param.uniformParam.upperBound - m_param.uniformParam.lowerBound)
            / 12;
        break;
    case IntUniform:
        return (m_param.intUniformParam.upperBound - m_param.intUniformParam.lowerBound)
            * (m_param.intUniformParam.upperBound - m_param.intUniformParam.lowerBound)
            / 12;
        break;
    case Bernoulli:
        return m_param.bernoulliParam * (1 - m_param.bernoulliParam);
        break;
    case Binomial:
        return m_param.binomialParam.nb * m_param.binomialParam.prob * (1 - m_param.binomialParam.prob);
        break;
    case Poisson:
        return m_param.poissonParam;
        break;
    case Exponential:
        return 1 / (m_param.exponentialParam * m_param.exponentialParam);
        break;
    case Normal:
        return (m_param.normalParam.stdDev * m_param.normalParam.stdDev);
        break;
    case LogNormal:
        return (m_param.lognormalParam.stdDev * m_param.lognormalParam.stdDev);
        break;
    default:
        return 0;
        break;
    }
}

double cRandomVariable::standardDeviation() const
{
    return sqrt(variance());
}

double cRandomVariable::minValue() const
{
    switch (m_type) {
    case Uniform:
        return m_param.uniformParam.lowerBound;
        break;
    case IntUniform:
        return m_param.intUniformParam.lowerBound;
        break;
    case Normal:
        return -DBL_MAX;
        break;
    case Bernoulli:
    case Binomial:
    case Poisson:
    case Exponential:
    case LogNormal:
    default:
        return 0;
        break;
    }
}

double cRandomVariable::maxValue() const
{
    switch (m_type) {
    case Uniform:
        return m_param.uniformParam.upperBound;
        break;
    case IntUniform:
        return m_param.intUniformParam.upperBound;
        break;
    case Bernoulli:
        return 1;
        break;
    case Binomial:
        return m_param.binomialParam.nb;
        break;
    case Poisson:
        return INT_MAX;
        break;
    case Exponential:
    case Normal:
    case LogNormal:
        return DBL_MAX;
        break;
    default:
        return 0;
        break;
    }
}
