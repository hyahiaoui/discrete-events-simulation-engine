/**
 * \file    baseobject.cpp
 * \brief   Implementation of base class for static and dynamic elements in maps edition and simulation.
 * \date    June, 10th, 2011
 * \author  Yahiaoui H.
 */

#include "baseobject.h"

#include <sstream>

const char EmptyName[] = "";

cBaseObject::cBaseObject(const char* name)
    : m_name(std::string())
    , m_kind(0)
{
    if (name)
        m_name = std::string(name);
}

cBaseObject::cBaseObject(const std::string& name)
    : m_name(std::string())
    , m_kind(0)
{
    m_name = name;
}

cBaseObject::cBaseObject(const cBaseObject& other)
    : m_name(std::string())
{
    operator=(other);
}

cBaseObject::~cBaseObject() noexcept(false)
{
}

cBaseObject& cBaseObject::operator=(const cBaseObject& other)
{
    if (this != &other) {
        m_name = other.m_name;
        m_kind = other.m_kind;
    }
    return *this;
}

bool cBaseObject::operator==(const cBaseObject& other) const
{
    return (m_kind == other.m_kind) && (m_name == other.m_name);
}

bool cBaseObject::operator!=(const cBaseObject& other) const
{
    return !operator==(other);
}

void cBaseObject::setName(const char* name)
{
    if (name) {
        m_name = std::string(name);
    } else
        m_name = std::string();
}

void cBaseObject::setName(const std::string& name)
{
    m_name = name;
}

const char* cBaseObject::name() const
{
    return m_name.c_str();
}

int cBaseObject::kind() const
{
    return m_kind;
}

void cBaseObject::setKind(const int kind)
{
    m_kind = kind;
}

const char* cBaseObject::serialize() const
{
    std::ostringstream outStream;
    outStream << "cBaseObject["
              << "name=\"" << name() << "\", "
              << "kind=" << kind() << "]";
    return outStream.str().c_str();
}

std::ostream& operator<<(std::ostream& ost, const cBaseObject& obj)
{
    return ost << (&obj)->serialize();
}

std::ostream& operator<<(std::ostream& ost, const cBaseObject* obj)
{
    if (obj)
        ost << obj->serialize();
    return ost;
}
