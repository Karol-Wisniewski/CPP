cmake_minimum_required(VERSION 3.24)
project(01_living_world-Karol-Wisniewski)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT "include/boost")

find_package(Boost 1.77.0)
find_package(Boost REQUIRED COMPONENTS serialization)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")


add_executable(01_living_world-Karol-Wisniewski
        src/LivingWorld.cpp
        src/World.cpp headers/World.h
        src/Animal.cpp headers/Animal.h
        src/Plant.cpp headers/Plant.h
        src/Organism.cpp headers/Organism.h
        src/Position.cpp headers/Position.h
        src/Wolf.cpp headers/Wolf.h
        src/Sheep.cpp headers/Sheep.h
        src/Dandelion.cpp headers/Dandelion.h
        src/Toadstool.cpp headers/Toadstool.h
        src/Grass.cpp headers/Grass.h
        src/World.cpp)

target_link_libraries(01_living_world-Karol-Wisniewski Boost::serialization)
