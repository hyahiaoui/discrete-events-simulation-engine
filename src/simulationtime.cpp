/**
 * \file    SimulationTime.cpp
 * \brief   Implementation of fixed-point representation of simulation time
 * \date    June, 9th, 2011
 * \author  Yahiaoui H.
 */

#include "SimulationTime.h"

#include <cmath>
#include <cstring>
#include <sstream>

unsigned SimulationTime::_timeDataLength = sizeof(SimulationTime::_time) << 3; // nbBits = nbOctets * 8 bits (we'll use 64 bits)
unsigned SimulationTime::_timeDataPrecision = SimulationTime::_timeDataLength / 8 * 3; // precision = (nbBits / 8) * 3 (we'll use 24 of 64)
/*
SimulationTime::SimulationTime():
    _time(0)
{
}
*/
SimulationTime::SimulationTime(const SimulationTime& other)
    : _time(0)
{
    operator=(other);
}

SimulationTime::SimulationTime(const long double dbl_time)
    : _time(0)
{
    fromDbl(dbl_time);
}

void SimulationTime::toStr(char* writeStr) const
{
    if (writeStr) {
        long int intP = toInt();
        bool sign = false;
        if (intP < 0) {
            sign = true;
            intP = -intP;
        }
        int days = intP / (24 * 3600);
        intP %= (24 * 3600);
        int hours = intP / 3600;
        intP %= 3600;
        int minutes = intP / 60;
        long double secondes = (intP % 60) + fabs(toDbl() - toInt());

        std::ostringstream strm;
        if (sign)
            strm << "-";
        if (days)
            strm << days << "d";
        if (hours)
            strm << hours << "h";
        if (minutes)
            strm << minutes << "m";
        if (secondes > 0) {
            strm.precision(8);
            strm << std::fixed << secondes << "s";
        }
        strcpy(writeStr, strm.str().c_str());
    }
}

void SimulationTime::fromStr(const char* readStr)
{
    if (!readStr)
        return;

    bool sign = false,
         days = false,
         hours = false,
         minutes = false,
         seconds = false;
    long double tmpTime = 0, tmpNbr = 0, divisor = 0;
    unsigned currentCharIndex = 0;

    // Ignore all white spaces at string start, and react if we find a sign
    bool stop = false;
    while (currentCharIndex < strlen(readStr)) {
        switch (readStr[currentCharIndex]) {
        case '-': // Sign is switched
            sign = !sign;
            break;
        case '+': // Sign does not change
            break;
        case ' ':
        case '\t': // Ignore blank caracters
            break;
        default: // Anything else will be parsed by the next loop
            stop = true;
            break;
        }
        if (stop)
            break;
        else
            currentCharIndex++;
    }

    while (currentCharIndex < strlen(readStr)) {
        switch (readStr[currentCharIndex]) {
        case ' ':
        case '\t': // Ignore blank caracters
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            tmpNbr = tmpNbr * 10 + (readStr[currentCharIndex] - '0');
            if (divisor)
                divisor *= 10;
            break;
        case '.':
            if (divisor)
                throw("Encountred several decimal delimiters while parsing time string.");
            divisor = 1;
            break;
        case 'd':
            if (days)
                throw("Encountred several day delimiters while parsing time string.");
            if (divisor > 0)
                tmpNbr /= divisor;
            divisor = 0;
            tmpTime += tmpNbr * 3600 * 24;
            tmpNbr = 0;
            days = true;
            break;
        case 'h':
            if (hours)
                throw("Encountred several hours delimiters while parsing time string.");
            if (divisor > 0)
                tmpNbr /= divisor;
            divisor = 0;
            tmpTime += tmpNbr * 3600;
            tmpNbr = 0;
            hours = true;
            break;
        case 'm':
            if (minutes)
                throw("Encountred several minutes delimiters while parsing time string.");
            if (divisor > 0)
                tmpNbr /= divisor;
            divisor = 0;
            tmpTime += tmpNbr * 60;
            tmpNbr = 0;
            minutes = true;
            break;
        case 's':
            if (seconds)
                throw("Encountred several seconds delimiters while parsing time string.");
            if (divisor > 0)
                tmpNbr /= divisor;
            divisor = 0;
            tmpTime += tmpNbr;
            tmpNbr = 0;
            seconds = true;
            break;
        default:
            throw("Encountred unknown caracter while parsing time string.");
            break;
        }
        currentCharIndex++;
    }

    if (tmpNbr > 0 && !seconds) // if no XXXs is to be found, but there is a XXX (with no 's')
    {
        if (divisor > 0)
            tmpNbr /= divisor;
        tmpTime += tmpNbr;
    }

    if (sign)
        tmpTime = -tmpTime;
    fromDbl(tmpTime);
}

long int SimulationTime::toInt() const
{
    return (long int)(toDbl());
}

void SimulationTime::fromInt(const long int int_time)
{
    fromDbl((long double)int_time);
}

long double SimulationTime::toDbl() const
{
    long double tmp = (long double)_time;
    return (tmp / (long double)(2 << _timeDataPrecision));
}

void SimulationTime::fromDbl(const long double dbl_time)
{
    long double tmp = dbl_time * (2 << _timeDataPrecision);
    _time = (DataType)tmp;
}

SimulationTime& SimulationTime::operator+=(const SimulationTime& op)
{
    _time += op._time;
    return *this;
}

SimulationTime& SimulationTime::operator-=(const SimulationTime& op)
{
    _time -= op._time;
    return *this;
}

SimulationTime& SimulationTime::operator*=(const long double& op)
{
    fromDbl(toDbl() * op);
    return *this;
}

SimulationTime& SimulationTime::operator/=(const long double& op)
{
    fromDbl(toDbl() / op);
    return *this;
}

SimulationTime SimulationTime::operator+(const SimulationTime& op) const
{
    SimulationTime cpy(*this);
    cpy.operator+=(op);
    return cpy;
}

SimulationTime SimulationTime::operator-(const SimulationTime& op) const
{
    SimulationTime cpy(*this);
    cpy.operator-=(op);
    return cpy;
}

SimulationTime SimulationTime::operator*(const long double& op) const
{
    SimulationTime cpy(*this);
    cpy.operator*=(op);
    return cpy;
}

SimulationTime SimulationTime::operator/(const long double& op) const
{
    SimulationTime cpy(*this);
    cpy.operator/=(op);
    return cpy;
}

std::ostream& operator<<(std::ostream& ost, const SimulationTime& time)
{
    //std::cout << "FGHJK" << std::endl;
    char tmp[100];
    time.toStr(&tmp[0]);
    ost << tmp;

    return ost;
}
