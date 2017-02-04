
#include <iomanip>
#include <iostream>

#include "Population.h"

// 3 variables permitting to generate random number with a uniform distribution
std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<double> dis(0.0, 1.0);

int main()
{
    std::string sentenceToFind = "Hello World!";    // The sentence we want to find.
    double chance = 0.01;                           // The chance to mutate (from 0.0 to 1.0).
    size_t populationSize = 500;                    // The population size (must be at least 4, and a multiple of 2).

    Population pop(sentenceToFind.length(), populationSize);    // Create the population.
    size_t generation = 0;
    for (size_t i = 0; i < 1000; i++) {
        pop.calculatefitness(sentenceToFind);                                      // Calculate the fitness of all sentences.
        std::cout << "Generation " << std::setw(5) << generation << "\n"           // Print the generation and the best sentence of that generation.
                  << "    Best fitness : " << pop.lastBestSentence().fitness()     //
                  << "\n"                                                          //
                  << "                   " << pop.lastBestSentence().sentence()    //
                  << std::endl;                                                    //
        pop.select();                                                              // Select half of the population depending on the fitness.
        pop.makeLoveAndMutate(chance);                                             // Let them make love (crossover) and let their child mutate.
                                                                                   //
        if (pop.lastBestSentence().sentence() == sentenceToFind) {                 // If we found our sentence, stop the loop.
            break;
        }

        generation++;
    }
}
