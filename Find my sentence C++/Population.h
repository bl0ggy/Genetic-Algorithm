#pragma once

#include <random>
#include <vector>

#include "Sentence.h"

// Variable created in "main.cpp" permitting to generate a random number from a uniform distribution.
extern std::random_device rd;
extern std::mt19937 generator;
extern std::uniform_real_distribution<double> dis;

class Population
{
public:
    Population(size_t p_sentenceLength, size_t p_quantity);    // Constructor, needs the length of the sentence we want to find, and the size of the population.
    void calculatefitness(std::string p_sentence);             // Calculate the fitness of all sentences.
    void select();                                             // Select half of the population depending on the fitness.
    void makeLoveAndMutate(double p_chance);                   // Crossover sentences and mutate the children.
    Sentence lastBestSentence();                               // Getter permitting to print it in the main() function.

private:
    std::vector<Sentence> m_sentences;    // List of all sentences.
    size_t m_quantity;                    // The quantity of the population (needed because of the select() function which will remove half of it).
    Sentence m_lastBestSentence;          // Range [0;1].
    double m_fitnessSum;                  // Sum of the fitness of all sentence.
};