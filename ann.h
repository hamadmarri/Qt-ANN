#ifndef ANN_H
#define ANN_H

#include <vector>
#include "layer.h"

class ANN
{
public:
    ANN();
    ~ANN();

    void setInputValues(std::vector<double> values);
    void feedForward();
    void backPropagate(std::vector<double> expectedOutputs);
    void print();

private:

    void initializeLayers();

    Layer **layers;
    Layer *outputLayer;
};

#endif // ANN_H
