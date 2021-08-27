#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <memory>
#include "node.h"

class Layer
{
public:
    Layer(int nodesNum);

    void connectLayers(std::shared_ptr<Layer> left, std::shared_ptr<Layer> right);
    void feedForward();
    void backPropagate();
    void backPropagate(std::vector<double> &expectedOutputs);

    std::shared_ptr<std::shared_ptr<Node>[]> nodes;

protected:
    int nodesNum;
    std::shared_ptr<Layer> rightLayer;

    static double derivativeOfSigmoid(double expectedOutput, double output);
};

#endif // LAYER_H
