#include "ann.h"

#include <qdebug.h>
#include "defines.h"

ANN::ANN()
{
    this->initializeLayers();
}

void ANN::initializeLayers()
{
    this->layers = new Layer*[LAYERS_NUM];

    for (int i = 0; i < LAYERS_NUM; ++i)
        this->layers[i] = new Layer(LAYERS_NODES[i]);

    this->outputLayer = this->layers[LAYERS_NUM - 1];

    /* connect layers */
    this->layers[0]->connectLayers(nullptr, this->layers[1]);

    for (int i = 1; i < LAYERS_NUM - 1; ++i)
        this->layers[i]->connectLayers(this->layers[i - 1], this->layers[i + 1]);

    this->outputLayer->connectLayers(this->layers[LAYERS_NUM - 2], nullptr);
}

ANN::~ANN()
{
    for (int i = 0; i < LAYERS_NUM; ++i)
        delete this->layers[i];

    delete [] this->layers;
}

void ANN::setInputValues(std::vector<double> values)
{
    Layer *iL = this->layers[0];
    Node **nodes = iL->nodes;

    for (int i = 0; i < values.size(); i++)
        nodes[i]->output = values[i];
}

void ANN::feedForward()
{
    /* starting from hidden layers */
    for (int i = 1; i < LAYERS_NUM; ++i)
        this->layers[i]->feedForward();
}

void ANN::backPropagate(std::vector<double> expectedOutputs)
{
    this->outputLayer->backPropagate(expectedOutputs);

    // Calculate error for all neurons in the hidden layers
    // (back propagate the errors)
    for (int i = LAYERS_NUM - 2; i > 0 ; --i)
        this->layers[i]->backPropagate();
}

void ANN::print()
{
    for (int i = 0; i < LAYERS_NODES[0]; ++i)
        qDebug() << "'i(" << this->layers[0]->nodes[i]->output << ')';

    for (int i = 0; i < LAYERS_NODES[LAYERS_NUM - 1]; ++i) {
        qDebug() << "'o(" << this->layers[LAYERS_NUM - 1]->nodes[i]->output << ')';
        qDebug() << "'e(" << this->layers[LAYERS_NUM - 1]->nodes[i]->error << ')';
    }

    qDebug() << "----------------";
}

