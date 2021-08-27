#ifndef ANNTRAINER_H
#define ANNTRAINER_H

#include<random>

#include "ann.h"

class AnnTrainer
{
public:
    AnnTrainer(ANN &ann);
    void train(unsigned int iterations);

private:
    void generate(double &a, double &b, double &c);
    void print();

    std::uniform_int_distribution<int> unif;
    std::default_random_engine re;
    ANN ann;
};

#endif // ANNTRAINER_H
