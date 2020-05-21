/**
 * \file    BaseObject.h
 * \brief   Declaration of base class for static and dynamic elements in maps edition and simulation.
 * \date    June, 10th, 2011
 * \author  Yahiaoui H.
 * \version 1.0
 */

#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <iostream>
#include <string>

/**
  * \brief  Base class for all entities with a name and a kind
  */
class BaseObject {
public:
    /**
      * \brief Default constructor
      */
    BaseObject(const char* name);
    BaseObject(const std::string& name = std::string());

    /**
      * \brief Copy Constructor
      */
    BaseObject(const BaseObject& other);

    /**
      * \brief Destructor
      */
    virtual ~BaseObject() noexcept(false);

    /**
      * \brief  Assignment operator
      */
    virtual BaseObject& operator=(const BaseObject& other);

    /**
      * \brief  Equality test operator
      */
    virtual bool operator==(const BaseObject& other) const;

    /**
      * \brief  Inequality test operator
      */
    virtual bool operator!=(const BaseObject& other) const;

    /**
      * \brief  Returns a const pointer to the internally stored name.
      */
    virtual const char* name() const;

    /**
      * \brief  Sets a new name for the object.
      */
    virtual void setName(const char* name);

    /**
      * \brief  Sets a new name for the object.
      */
    virtual void setName(const std::string& name);

    /**
      * \brief  Returns the kind associated with the object
      */
    virtual int kind() const;

    /**
      * \brief  Sets the kind associated with the object
      */
    virtual void setKind(const int kind);

    /**
      * \brief  Serialization operator. This method should be overloaded by the subclasses of BaseObject.
      * \return
      */
    virtual const char* serialize() const;

private:
    std::string m_name;
    int m_kind;
};

/**
  * \brief  Really simple writing function.
  */
std::ostream& operator<<(std::ostream& ost, const BaseObject& obj);
std::ostream& operator<<(std::ostream& ost, const BaseObject* obj);

#endif // BASEOBJECT_H
