#pragma once

#include <random>
#include <string>

// Variables created in "main.cpp" permitting to generate a random number with a uniform distribution.
// (extern because it is unnecessary to create them more than once).
extern std::random_device rd;
extern std::mt19937 generator;
extern std::uniform_real_distribution<double> dis;

class Sentence
{
public:
    Sentence(size_t p_length);                        // Constructor, make a random sentence with p_length characters.
    void calculateFitness(std::string p_str);         // Calculate the fitness of the actual Sentence.
    std::vector<Sentence> crossOver(Sentence p_A);    // Crossover the actual Sentence with another one.
    void mutate(double p_chance);                     // Mutate the actual Sentence.
    std::string sentence();                           // Returns the actual Sentence.
    double fitness();                                 // Returns the fitness of the actual Sentence.

private:
    Sentence(std::string p_str);    // Constructor, use by Sentence class after a crossover.

    std::string m_sentence;    // The sentence of the actual object.
    double m_fitness;          // The fitness in range [0;1].
};
