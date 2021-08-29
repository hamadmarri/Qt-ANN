#ifndef ANNTRAINER_H
#define ANNTRAINER_H

#include <QObject>
#include <QtQuick>
#include <QThread>
#include <QTimer>
#include <random>
#include <vector>

#include "ann.h"

class AnnTrainer : public QThread
{
Q_OBJECT

    Q_PROPERTY(unsigned int iterations READ iterations WRITE setIterations);
    Q_PROPERTY(double error READ error NOTIFY errorChanged);

public:
    AnnTrainer();
    AnnTrainer(ANN &ann);

    Q_INVOKABLE void train();

    unsigned int iterations();
    void setIterations(unsigned int i);
    double error();

signals:
    void errorChanged();

private:

    void _train();
    void generate(double &a, double &b, double &c);
    void print();
    void timeout();

    std::uniform_int_distribution<int> unif;
    std::default_random_engine re;
    ANN ann;
    int _iterations;
    QTimer *timer;

    // QThread interface
protected:
    void run();

};

#endif // ANNTRAINER_H
