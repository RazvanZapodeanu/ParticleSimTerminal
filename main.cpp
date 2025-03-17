
#include "Simulation.h"
#include <iostream>
#include <fstream>




int main() {



    Simulation sim(200.0, 200.0, 1.0);


    int option;
    bool running = true;

    while (running) {
        std::cout << "\n=== PARTICLE SIMULATION MENU ===\n";
        std::cout << "1. Add a particle manually\n";
        std::cout << "2. Load particles from input.txt file\n";
        std::cout << "3. Run the simulation for a number of steps\n";
        std::cout << "4. Display the current state of the simulation\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> option;

        switch (option) {
            case 1:
                sim.createParticleFromUserInput();
                break;
            case 2:
                sim.loadInputExamples();
                break;
            case 3: {
                int steps;
                std::cout << "Enter the number of steps: ";
                std::cin >> steps;
                sim.run(steps);
                std::cout << "Simulation ran for " << steps << " steps.\n";
                break;
            }
            case 4:
                std::cout << "\nCurrent state of the simulation:\n" << sim << std::endl;
                break;
            case 5:
                running = false;
                break;
            default:
                std::cout << "Invalid option. Try again.\n";
        }
    }

    std::cout << "Simulation ended. Goodbye!\n";
    return 0;
}