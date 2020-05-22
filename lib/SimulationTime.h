/**
 * \file    SimulationTime.h
 * \brief   Declaration of fixed-point representation of simulation time
 * \date    June, 9th, 2011
 * \author  Yahiaoui H.
 */

#ifndef SIMULATIONTIME_H
#define SIMULATIONTIME_H

#include <iostream>

/**
 *  \brief  Abstraction of simulation time, used by simulation projects
 *
 *  This class represents the time used for simulation purposes. It uses a fixed point representation of time, to achieve
 *  speed and usability on several scales of time.
 */
class SimulationTime {
public:
    // --------- Constructors
    /**
      * \brief  Default constructor that builds a 0-time.
      */
    //SimulationTime();

    /**
      * \brief  Copy constructor.
      */
    SimulationTime(const SimulationTime& other);

    /**
      * \brief  Time Constructor from double value.
      */
    SimulationTime(const long double dbl_time = 0);

    // --------- Explicit Conversion methods
    /**
      * \brief  Converts time into integer value
      * \return Integer part of the time stored in the object
      */
    long int toInt() const;

    /**
      * \brief  Converts time into double value
      * \return conversion of time into double value.
      */
    long double toDbl() const;

    /**
      * \brief  Converts time from integer value
      * \param  int_time given time as integer value
      */
    void fromInt(const long int int_time);

    /**
      * \brief  Converts time from double value
      * \param  dbl_time given time as double value
      */
    void fromDbl(const long double dbl_time);

    /**
      * \brief  Writes the time into the given string
      * \param  writeStr    string where a string-version of the time is written
      */
    void toStr(char* writeStr) const;

    /**
      * \brief  Reads the time from the given string
      * \param  readStr    string from where a string-version of the time is read
      */
    void fromStr(const char* readStr);

    // --------- Information Getters
    /**
      * \brief  Returns the number of bits used to store time, as fixed point value.
      */
    static inline unsigned getBitsLength()
    {
        return _timeDataLength;
    }

    /**
      * \brief  Returns the number of bits used to store the fractionnal part of time.
      */
    static inline unsigned getPrecisionLength()
    {
        return _timeDataPrecision;
    }

    /**
      * \brief  Assignment operator
      */
    inline SimulationTime& operator=(const SimulationTime& other)
    {
        if (this != &other)
            _time = other._time;
        return *this;
    }

    /**
      * \brief  Equality test operator
      */
    inline bool operator==(const SimulationTime& other) const
    {
        return (_time == other._time);
    }

    /**
      * \brief  Difference test operator
      */
    inline bool operator!=(const SimulationTime& other) const
    {
        return !operator==(other);
    }

    /**
      * \brief  Less than test operator
      */
    inline bool operator<(const SimulationTime& other) const
    {
        return (_time < other._time);
    }

    /**
      * \brief  Less than or equal to test operator
      */
    inline bool operator<=(const SimulationTime& other) const
    {
        return (operator==(other) || operator<(other));
    }

    /**
      * \brief  Greater than test operator
      */
    inline bool operator>(const SimulationTime& other) const
    {
        return (_time > other._time);
    }

    /**
      * \brief  Greater than or equal to test operator
      */
    inline bool operator>=(const SimulationTime& other) const
    {
        return (operator==(other) || operator>(other));
    }

    /**
      * \brief  Addition assignment operator
      */
    SimulationTime& operator+=(const SimulationTime&);

    /**
      * \brief  Substraction assignment operator
      */
    SimulationTime& operator-=(const SimulationTime&);

    /**
      * \brief  Multiplication assignment operator
      */
    SimulationTime& operator*=(const long double&);

    /**
      * \brief  Division assignment operator
      */
    SimulationTime& operator/=(const long double&);

    /**
      * \brief  Addition operator
      */
    SimulationTime operator+(const SimulationTime&) const;

    /**
      * \brief  Substraction operator
      */
    SimulationTime operator-(const SimulationTime&) const;

    /**
      * \brief  Multiplication operator
      */
    SimulationTime operator*(const long double&) const;

    /**
      * \brief  Division operator
      */
    SimulationTime operator/(const long double&) const;

private:
    typedef signed long long int DataType;

    static unsigned _timeDataLength, _timeDataPrecision;

    DataType _time;
};

/**
  * \brief Output stream writer
  */
std::ostream& operator<<(std::ostream& ost, const SimulationTime& time);

#endif // SIMULATIONTIME_H
