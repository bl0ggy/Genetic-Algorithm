#include "Population.h"

Population::Population(size_t p_sentenceLength, size_t p_quantity)
  : m_lastBestSentence(Sentence(p_sentenceLength))    // Make a random Sentence, no other choice at the construction (an null pointer would be dangerous).
  , m_quantity(p_quantity)                            // The size of the population.
{
    for (size_t i = 0; i < p_quantity; i++) {
        m_sentences.push_back(Sentence(p_sentenceLength));    // Generate p_quantity Sentence.
    }
}

void Population::calculatefitness(std::string p_sentence)
{
    double lastBestFitness = 0.0f;                           // Set the worst value to the best fitness.
    m_fitnessSum = 0.0f;                                     // Initialize the suml of fitnesses to 0.
    for (size_t i = 0; i < m_sentences.size(); i++) {        // For all Sentence objects,
        m_sentences[i].calculateFitness(p_sentence);         //   calculate its fitness,
        m_fitnessSum += m_sentences[i].fitness();            //   and add it to the sum of fitnesses.
                                                             //
        if (m_sentences[i].fitness() > lastBestFitness) {    //   If the fitness is better than another one before,
            lastBestFitness = m_sentences[i].fitness();      //   set this Sentence object as the best.
            m_lastBestSentence = m_sentences[i];             //
        }
    }
}

void Population::select()
{
    size_t halfQuantity = m_quantity / 2;                                                      // We want half of the population.
    std::vector<Sentence> tmp_sentences;                                                       // Empty Sentence vector we will fill ..
    while (tmp_sentences.size() < halfQuantity) {                                              //   .. until we have not reached half of the quantity.
        double sum = 0.0;                                                                      //   Here we prepare a "roulette wheel" algorithm. We start with a fitness sum of 0.
                                                                                               //
                                                                                               //   (Note that this sum is different than m_fitnessSum. This one will increase after each loop,
                                                                                               //    permitting to select a Sentence randomly).
                                                                                               //
        double rand = std::uniform_real_distribution<double>(0.0, m_fitnessSum)(generator);    //   Generate a random number between 0.0 and the sum of fitnesses of all the population.
        for (int i = 0; i < m_sentences.size(); i++) {                                         //   Browse the population of Sentence objects.
            sum += m_sentences[i].fitness();                                                   //     Add the fitness of the current Sentence to the sum.
            if (sum >= rand) {                                                                 //     If the sum is equal or above our random number,
                tmp_sentences.push_back(m_sentences[i]);                                       //       we select that Sentence for the next generation,
                m_sentences.erase(m_sentences.begin() + i);                                    //       so we remove it from the actual population,
                m_fitnessSum -= tmp_sentences.back().fitness();                                //       and decrease the sum of fitnesses of all the population. (Better than recalculate the whole sum).
                sum = 0.0;                                                                     //       Reinitialize the sum to 0 for the next selection.
            }                                                                                  //
        }                                                                                      //
    }                                                                                          //
    m_sentences = tmp_sentences;                                                               // Finally, the new (half) generation is equal to the one we filled with selected Sentence objects.
}

void Population::makeLoveAndMutate(double p_chance)
{
    size_t halfQuantity = m_quantity / 2;                                           // Reminder of the value of half population.
    while (m_sentences.size() < m_quantity) {                                       // Until the actual population has not reached m_quantity Sentence objects,
        size_t i1 = (size_t)(dis(generator) * (double)halfQuantity);                //   select 2 Sentence objects from the last natural selection,
        size_t i2 = (size_t)(dis(generator) * (double)halfQuantity);                //
        std::vector<Sentence> outs = m_sentences[i1].crossOver(m_sentences[i2]);    //   mix their DNA, to make 2 children,
        m_sentences.push_back(outs[0]);                                             //   put them into the actual population,
        m_sentences.back().mutate(p_chance);                                        //   and mutate them (if their fate is to evolve).
        m_sentences.push_back(outs[1]);                                             //
        m_sentences.back().mutate(p_chance);                                        //
    }
}

Sentence Population::lastBestSentence()
{
    return m_lastBestSentence;
}
