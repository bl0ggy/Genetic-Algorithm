
#include "Sentence.h"

Sentence::Sentence(size_t p_length)
  : m_fitness(0.0f)    // We don't know the Sentence to find at the beginning.
{
    for (size_t i = 0; i < p_length; i++) {
        char rand = (char)(dis(generator) * 95) + 32;    // Create the DNA randomly with p_length characters.
        m_sentence.push_back(rand);
    }
}

Sentence::Sentence(std::string p_str)    // Constructor used only by this class itself after a crossover.
    : m_fitness(0.0f)
{
    m_sentence = p_str;    // "p_str" is the DNA calculated by the crossover.
}

void Sentence::calculateFitness(std::string p_str)
{
    size_t fit = 0;                               // The fitness is the number of equal characters between the 2 Sentence objects, including the position of that.
    size_t length = p_str.length();               //
    for (size_t i = 0; i < length; i++) {         // Browse all characters
        if (p_str.at(i) == m_sentence.at(i)) {    //   If the character 'i' of each Sentence is the same,
            fit++;                                //   increase the fitness.
        }
    }
    m_fitness = std::exp(double(fit) - double(length));    // "Normalize" the fitness number between e^(-length) and e^(0) (between 0 and 1 when length is infinite).
                                                           // This permits to give more luck to the best Sentence objects during a natural selection.
}

std::vector<Sentence> Sentence::crossOver(Sentence p_A)
{
    std::string out1 = "";                                // Initialize 2 empty strings.
    std::string out2 = "";                                //
    for (size_t i = 0; i < m_sentence.length(); i++) {    // Browse all characters.
        int rand = (int)(dis(generator) * 2.0);           //   Generate a random number between 0 and (less than) 2. casting it to int will truncate it to 0 or 1.
        if (rand) {                                       //   If the random number is a 1,
            out1.push_back(p_A.sentence().at(i));         //     Put the i-th character of p_A in the first child,
            out2.push_back(m_sentence.at(i));             //     and the i-th character of the actual Sentence in the second child.
        } else {                                          //   If the random number if a 0,
            out1.push_back(m_sentence.at(i));             //     Put the i-th character of the actual Sentence in the first child,
            out2.push_back(p_A.sentence().at(i));         //     and the i-th character of p_A in the second child.
        }
    }
    return std::vector<Sentence>{Sentence(out1), Sentence(out2)};
}

void Sentence::mutate(double p_chance)
{
    for (size_t i = 0; i < m_sentence.length(); i++) {            // Browse all characters
        double rand = dis(generator);                             // Generate a random number between 0 and (less than) 1.
        bool toMutate = rand < p_chance ? true : false;           // If that number if below the chance,                        Why below ? If you want the maximum chance, p_chance equal to 1,
        if (toMutate) {                                           //                                                            "rand" cannot be above (or equal to) 1.
                                                                  //                                                            Similarly with the minimum chance, p_chance equal to 0,
                                                                  //                                                            "rand" cannot be below 0.
            char character = (char)(dis(generator) * 95) + 32;    //   Generate a random character,
            m_sentence[i] = character;                            //   and replace the old one by the one generated.
        }
    }
}

std::string Sentence::sentence()
{
    return m_sentence;
}

double Sentence::fitness()
{
    return m_fitness;
}