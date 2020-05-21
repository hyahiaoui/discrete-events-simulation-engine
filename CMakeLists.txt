cmake_minimum_required(VERSION 3.17)

project(discrete-events-simulator)

include(build/conanbuildinfo.cmake)

conan_basic_setup()

set(SRCS
    src/BaseObject.cpp
    src/DESimulator.cpp
    src/GenericGraph.cpp
    src/main.cpp
    src/ModuleTimer.cpp
    src/MovingParticle.cpp
    src/Random.cpp
    src/RandomVariable.cpp
    src/SimulationEvent.cpp
    src/SimulationModule.cpp
    src/SimulationTime.cpp
    src/TestDESimulator.cpp
    src/UniqueIDGenerator.cpp
    )
    
set(HEADERS
    src/BaseObject.h
    src/common.h
    src/DESimulator.h
    src/GenericGraph.h
    src/ModuleTimer.h
    src/MovingParticle.h
    src/Random.h
    src/RandomVariable.h
    src/SimulationEvent.h
    src/SimulationModule.h
    src/SimulationTime.h
    src/TestDESimulator.h
    src/UniqueIDGenerator.h
    )

add_compile_options(-std=c++11)

add_executable(des ${SRCS} ${HEADERS})

target_link_libraries(des ${CONAN_LIBS})

link_libraries("-static")




