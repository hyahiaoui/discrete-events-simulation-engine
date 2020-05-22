#ifndef RANDOMVARIABLE_H
#define RANDOMVARIABLE_H

#include <string>
#include <vector>

class RandomVariable {
public:
    enum VariableCategory {
        Undefined,
        Discrete,
        Continuous
    };
    enum VariableType {
        Unusable = 0,
        Uniform,
        IntUniform,
        Bernoulli,
        Binomial,
        Poisson,
        Exponential,
        Normal,
        LogNormal
    };

    struct UniformParameters {
        double lowerBound;
        double upperBound;
    };

    struct IntUniformParameters {
        int lowerBound;
        int upperBound;
    };

    struct BinomialParameters {
        double prob;
        unsigned nb;
    };

    struct NormalParameters {
        double mean;
        double stdDev;
    };

    RandomVariable(const VariableType varType = Unusable, const double param1 = 0, const double param2 = 0);

    // Getters
    VariableType type() const
    {
        return m_type;
    }

    const std::string& typeString() const
    {
        return m_typesNames.at(m_type);
    }

    static const std::vector<std::string>& typesStrings()
    {
        return m_typesNames;
    }

    VariableCategory category() const
    {
        return m_category;
    }

    const UniformParameters& uniformParameters() const
    {
        return m_param.uniformParam;
    }

    const IntUniformParameters& intUniformParameters() const
    {
        return m_param.intUniformParam;
    }

    double bernoulliParameters() const
    {
        return m_param.bernoulliParam;
    }

    const BinomialParameters& binomialParameters() const
    {
        return m_param.binomialParam;
    }

    double exponentialParameters() const
    {
        return m_param.exponentialParam;
    }

    double poissonParameters() const
    {
        return m_param.poissonParam;
    }

    const NormalParameters& normalParameters() const
    {
        return m_param.normalParam;
    }

    const NormalParameters& lognormalParameters() const
    {
        return m_param.lognormalParam;
    }

    // Setters
    void setUnusable()
    {
        m_type = Unusable;
        m_category = Undefined;
    }

    void setUniform(const double bound1, const double bound2);
    void setIntUniform(const int bound1, const int bound2);
    void setBernoulli(const double p);
    void setBinomial(const unsigned n, const double p);
    void setExponential(const double lambda);
    void setPoisson(const double lambda);
    void setNormal(const double mean = 0, const double standardDev = 1);
    void setLogNormal(const double mean, const double standardDev);

    // Generator
    double generateSample() const;

    // Random Variable characteristics
    double mean() const;
    double variance() const;
    double standardDeviation() const;
    double minValue() const;
    double maxValue() const;

    // Produce vari

private:
    union VariableParams {
        UniformParameters uniformParam;
        IntUniformParameters intUniformParam;
        double bernoulliParam;
        BinomialParameters binomialParam;
        double exponentialParam;
        double poissonParam;
        NormalParameters normalParam;
        NormalParameters lognormalParam;
    };

    VariableCategory m_category;
    VariableType m_type;
    VariableParams m_param;

    static const std::vector<std::string> m_typesNames;
};

#endif // RANDOMVARIABLE_H
