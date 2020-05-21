/**
 * \file    BaseObject.cpp
 * \brief   Implementation of base class for static and dynamic elements in maps edition and simulation.
 * \date    June, 10th, 2011
 * \author  Yahiaoui H.
 */

#include "BaseObject.h"

#include <sstream>

const char EmptyName[] = "";

BaseObject::BaseObject(const char* name)
    : m_name(std::string())
    , m_kind(0)
{
    if (name)
        m_name = std::string(name);
}

BaseObject::BaseObject(const std::string& name)
    : m_name(std::string())
    , m_kind(0)
{
    m_name = name;
}

BaseObject::BaseObject(const BaseObject& other)
    : m_name(std::string())
{
    operator=(other);
}

BaseObject::~BaseObject() noexcept(false)
{
}

BaseObject& BaseObject::operator=(const BaseObject& other)
{
    if (this != &other) {
        m_name = other.m_name;
        m_kind = other.m_kind;
    }
    return *this;
}

bool BaseObject::operator==(const BaseObject& other) const
{
    return (m_kind == other.m_kind) && (m_name == other.m_name);
}

bool BaseObject::operator!=(const BaseObject& other) const
{
    return !operator==(other);
}

void BaseObject::setName(const char* name)
{
    if (name) {
        m_name = std::string(name);
    } else
        m_name = std::string();
}

void BaseObject::setName(const std::string& name)
{
    m_name = name;
}

const char* BaseObject::name() const
{
    return m_name.c_str();
}

int BaseObject::kind() const
{
    return m_kind;
}

void BaseObject::setKind(const int kind)
{
    m_kind = kind;
}

const char* BaseObject::serialize() const
{
    std::ostringstream outStream;
    outStream << "BaseObject["
              << "name=\"" << name() << "\", "
              << "kind=" << kind() << "]";
    return outStream.str().c_str();
}

std::ostream& operator<<(std::ostream& ost, const BaseObject& obj)
{
    return ost << (&obj)->serialize();
}

std::ostream& operator<<(std::ostream& ost, const BaseObject* obj)
{
    if (obj)
        ost << obj->serialize();
    return ost;
}
