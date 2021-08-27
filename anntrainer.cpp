#include "anntrainer.h"
#include <random>
#include <ctime>

AnnTrainer::AnnTrainer(ANN &ann)
{
    this->ann = ann;
    this->unif = std::uniform_int_distribution<int>(0, 1);
    re.seed(std::time(NULL));
}

void AnnTrainer::train(unsigned int iterations)
{
    double a, b, c;

    for (unsigned int i = 0; i < iterations; ++i) {
        this->generate(a, b, c);

        this->ann.setInputValues(std::vector<double>{a, b});
        this->ann.feedForward();
        this->ann.backPropagate(std::vector<double>{c, 1.0});
    }

    this->print();
}

void AnnTrainer::generate(double &a, double &b, double &c)
{
    int ia, ib, ic;

    ia = unif(re);
    ib = unif(re);
    ic = ia ^ ib;

    a = ia;
    b = ib;
    c = ic;
}

void AnnTrainer::print()
{
    this->ann.setInputValues(std::vector<double>{0, 0});
    this->ann.feedForward();
    this->ann.print();

    this->ann.setInputValues(std::vector<double>{1, 0});
    this->ann.feedForward();
    this->ann.print();

    this->ann.setInputValues(std::vector<double>{0, 1});
    this->ann.feedForward();
    this->ann.print();

    this->ann.setInputValues(std::vector<double>{1, 1});
    this->ann.feedForward();
    this->ann.print();
}
