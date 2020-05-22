#include "BaseObject.h"

#include "catch2/catch.hpp"

#include <iostream>

TEST_CASE("BaseObject can be created and accessed", "[BaseObject]")
{
    BaseObject ob1, ob2("hi"), ob3("himynameiswalter");

    std::cout << "First object is '" << ob1.name() << "'." << std::endl;
    std::cout << "Second object is '" << ob2.name() << "'." << std::endl;
    std::cout << "Third object is '" << ob3.name() << "'." << std::endl;

    ob1 = ob2;
    std::cout << "First object is '" << ob1.name() << "'." << std::endl;
    std::cout << "First Object is " << (ob1 == ob3 ? "equal to" : "different from") << " Third Object." << std::endl;

    ob1.setName("");
    std::cout << "First object is '" << ob1.name() << "'." << std::endl;
    std::cout << "First Object is " << (ob1 == ob3 ? "equal to" : "different from") << " Third Object." << std::endl;

    ob1.setName(ob3.name());
    std::cout << "First object is '" << ob1.name() << "'." << std::endl;
    std::cout << "First Object is " << (ob1 == ob3 ? "equal to" : "different from") << " Third Object." << std::endl;
}