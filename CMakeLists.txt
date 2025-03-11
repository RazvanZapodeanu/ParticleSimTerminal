cmake_minimum_required(VERSION 3.30)
project(Tema1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Tema1 main.cpp
        Vector2D.h
        Particle.h
        Environment.h
        Simulation.h
)
