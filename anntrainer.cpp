#include "anntrainer.h"
#include <random>
#include <ctime>

AnnTrainer::AnnTrainer()
{
    this->unif = std::uniform_int_distribution<int>(0, 1);
    re.seed(std::time(NULL));
}

AnnTrainer::AnnTrainer(ANN &ann) : AnnTrainer()
{
    this->ann = ann;
}

void AnnTrainer::train()
{
    this->timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &AnnTrainer::timeout);
    timer->start(1);

    this->start();
}

void AnnTrainer::run()
{
    this->_train();
}

void AnnTrainer::_train()
{
    double a, b, c;
    qDebug("start training");

    for (unsigned int i = 0; i < this->_iterations; ++i) {
        this->generate(a, b, c);

        this->ann.setInputValues(std::vector<double>{a, b});
        this->ann.feedForward();
        this->ann.backPropagate(std::vector<double>{c, 1.0});
    }

    this->timer->stop();
    this->print();
    emit errorChanged();
}

void AnnTrainer::timeout()
{
    emit errorChanged();
}

unsigned int AnnTrainer::iterations()
{
    return this->_iterations;
}

void AnnTrainer::setIterations(unsigned int i)
{
    this->_iterations = i;
}

double AnnTrainer::error()
{
    return this->ann.error;
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

