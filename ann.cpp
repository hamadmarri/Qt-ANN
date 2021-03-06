#include "ann.h"

#include <qdebug.h>
#include "defines.h"

ANN::ANN()
{
    this->initializeLayers();
}

void ANN::initializeLayers()
{
    for (int i = 0; i < LAYERS_NUM; ++i)
        this->layers.push_back(std::make_shared<Layer>(LAYERS_NODES[i]));

    this->outputLayer = this->layers[LAYERS_NUM - 1].get();

    /* connect layers */
    this->layers[0]->connectLayers(nullptr, this->layers[1].get());

    for (int i = 1; i < LAYERS_NUM - 1; ++i)
        this->layers[i]->connectLayers(this->layers[i - 1].get(), this->layers[i + 1].get());

    this->outputLayer->connectLayers(this->layers[LAYERS_NUM - 2].get(), nullptr);
}

void ANN::setInputValues(std::vector<double> values)
{
    Layer *iL = this->layers[0].get();

    for (int i = 0; i < values.size(); i++)
        iL->nodes[i]->output = values[i];
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

    /* update error */
    this->error = abs(this->outputLayer->nodes[0]->output - expectedOutputs[0]);
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

