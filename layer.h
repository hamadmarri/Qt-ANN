#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include "node.h"

class Layer
{
public:
    Layer(int nodesNum);
    ~Layer();

    void connectLayers(Layer *left, Layer *right);
    void feedForward();
    void backPropagate();
    void backPropagate(std::vector<double> &expectedOutputs);

    Node **nodes;

protected:
    int nodesNum;
    Layer *rightLayer;

    static double derivativeOfSigmoid(double expectedOutput, double output);
};

#endif // LAYER_H
