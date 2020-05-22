#include "SimulationTime.h"

#include "catch2/catch.hpp"

#include <sstream>

TEST_CASE("SimulationTime can be converted to and from strings", "[SimulationTime]")
{
    int MYMAX = 60;

    std::stringstream timeAsStr;
    SimulationTime st, oldst;

    std::cout.precision(24);
    for (int i = 0; i < 10; i++) {
        timeAsStr.str("");
        timeAsStr << (rand() % 2 == 0 ? "+" : "-")
                  << rand() % MYMAX << "h"
                  << rand() % MYMAX << "d"
                  << rand() % MYMAX << "m"
                  << rand() % MYMAX << "";

        std::cout << "=============================" << std::endl;
        std::cout << "Before conversion time = " << timeAsStr.str().c_str() << std::endl;
        try {
            oldst = st;
            st.fromStr(timeAsStr.str().c_str());
        } catch (char* strexcept) {
            std::cerr << "Launched exception '" << strexcept << "'. Stopping." << std::endl;
            return;
        }

        std::cout << "After conversion time = " << st << std::endl;
        std::cout << "'" << st << "' + '" << oldst << "' = '" << st + oldst << "'." << std::endl;
    }

    SimulationTime testtime;
    testtime.fromStr("6h6m6s");
    std::cout << "============================" << std::endl;
    std::cout << "time is " << testtime << std::endl
              << ", 1.5*time = " << testtime * 1.5 << std::endl
              << ", 2*time = " << testtime * 2 << std::endl
              << ", 0.1*time = " << testtime * 0.1 << std::endl
              << ", 10.5*time = " << testtime * 10.5 << std::endl
              << ", 1000*time = " << testtime * 1000 << std::endl;
}