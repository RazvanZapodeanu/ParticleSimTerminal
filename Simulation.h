#ifndef SIMULATION_H
#define SIMULATION_H
#include "Environment.h"
#include <fstream>
#include <iostream>
#include <string>

class Simulation {
private:
    Environment environment;
    double time;
    double timeStep;
public:


    Simulation(double width = 100.0, double height = 100.0, double timeStep = 0.1)
        : environment(width, height), time(0.0), timeStep(timeStep) {}


    Simulation(const Simulation& other)
        : environment(other.environment), time(other.time), timeStep(other.timeStep) {}


    Simulation& operator=(const Simulation& other) {
        if (this != &other) {
            environment = other.environment;
            time = other.time;
            timeStep = other.timeStep;
        }
        return *this;
    }


    ~Simulation() {}


    const Environment& getEnvironment() const { return environment; }
    double getTime() const { return time; }
    double getTimeStep() const { return timeStep; }


    void setTimeStep(double newTimeStep) { timeStep = newTimeStep; }


    void addParticle(const Particle& particle) {
        environment.addParticle(particle);
    }

    void createParticleFromUserInput() {
        std::string name;
        double mass, radius, posX, posY, velX, velY;

        std::cout << "Input particle name: ";
        std::cin >> name;

        std::cout << "Input particle mass: ";
        std::cin >> mass;

        std::cout << "Input particle radius: ";
        std::cin >> radius;

        std::cout << "Input position X: ";
        std::cin >> posX;

        std::cout << "Input position Y: ";
        std::cin >> posY;

        std::cout << "Input speed X: ";
        std::cin >> velX;

        std::cout << "Input speed Y: ";
        std::cin >> velY;

        addParticle(Particle(name, mass, radius, Vector2D(posX, posY), Vector2D(velX, velY)));
        std::cout << "Particle added with succes!\n";
    }

    void step() {
        environment.update(timeStep);
        time += timeStep;
    }

    void run(int steps) {
        for (int i = 0; i < steps; ++i) {
            step();
        }
    }

    void loadInputExamples(const std::string& filename = "tastatura.txt") {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string name;
            double mass, radius, posX, posY, velX, velY;

            while (file >> name >> mass >> radius >> posX >> posY >> velX >> velY) {
                addParticle(Particle(name, mass, radius, Vector2D(posX, posY), Vector2D(velX, velY)));
            }

            file.close();
            std::cout << "Particles loaded from file: " << filename << std::endl;
        } else {
            std::cout << "Couldn't open the file: " << filename << std::endl;
        }
    }


    friend std::ostream& operator<<(std::ostream& os, const Simulation& sim) {
        os << "Simulation: time=" << sim.time << ", timeStep=" << sim.timeStep << "\n";
        os << sim.environment;
        return os;
    }
};


#endif
