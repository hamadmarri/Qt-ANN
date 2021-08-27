#ifndef ANN_H
#define ANN_H

#include <vector>
#include <memory>
#include "layer.h"

class ANN
{
public:
    ANN();

    void setInputValues(std::vector<double> values);
    void feedForward();
    void backPropagate(std::vector<double> expectedOutputs);
    void print();

private:

    void initializeLayers();

    std::vector<std::shared_ptr<Layer>> layers;
    Layer *outputLayer;
};

#endif // ANN_H
