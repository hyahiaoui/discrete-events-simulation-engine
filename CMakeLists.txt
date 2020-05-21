cmake_minimum_required(VERSION 3.17)

project(discrete-events-simulator)

include(build/conanbuildinfo.cmake)

conan_basic_setup()

set(SRCS
    src/baseobject.cpp
    src/desimulator.cpp
    src/genericgraph.cpp
    src/main.cpp
    src/moduletimer.cpp
    src/movingparticle.cpp
    src/random.cpp
    src/randomvariable.cpp
    src/simulationevent.cpp
    src/simulationmodule.cpp
    src/simulationtime.cpp
    src/test_desimulator.cpp
    src/uniqueidgenerator.cpp
    )
    
set(HEADERS
    src/baseobject.h
    src/common.h
    src/desimulator.h
    src/genericgraph.h
    src/moduletimer.h
    src/movingparticle.h
    src/random.h
    src/randomvariable.h
    src/simulationevent.h
    src/simulationmodule.h
    src/simulationtime.h
    src/test_desimulator.h
    src/uniqueidgenerator.h
    )

add_compile_options(-std=c++11)

add_executable(des ${SRCS} ${HEADERS})

target_link_libraries(des ${CONAN_LIBS})

link_libraries("-static")




