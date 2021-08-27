#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <memory>
#include "node.h"

class Layer
{
public:
    Layer(int nodesNum);

    void connectLayers(Layer *left, Layer *right);
    void feedForward();
    void backPropagate();
    void backPropagate(std::vector<double> &expectedOutputs);

    std::vector<std::shared_ptr<Node>> nodes;

protected:
    int nodesNum;
    Layer *rightLayer;

    static double derivativeOfSigmoid(double expectedOutput, double output);
};

#endif // LAYER_H
