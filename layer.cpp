#include "layer.h"

Layer::Layer(int nodesNum)
{
    /* +1 is for bias neuron */
    this->nodesNum = nodesNum + 1;
    this->nodes = new Node*[this->nodesNum];
}

Layer::~Layer()
{
    for (int i = 0; i < this->nodesNum; ++i)
        delete this->nodes[i];

    delete [] this->nodes;
}

void Layer::connectLayers(Layer *left, Layer *right)
{
    Node *lN;
    Edge *lE;

    /* initialize nodes */
    for (int i = 0; i < this->nodesNum; ++i) {
        if (!left) {
            this->nodes[i] = new Node(0);
            continue;
        }

        this->nodes[i] = new Node(left->nodesNum);
        for (int j = 0; j < left->nodesNum; ++j) {
            lN = left->nodes[j];
            lE = &this->nodes[i]->leftEdges[j];

            lE->leftNode = lN;
        }
    }

    /* make the bias neuron's output = 1 */
    this->nodes[this->nodesNum - 1]->output = 1.0;

    this->rightLayer = right;
}

void Layer::feedForward()
{
    /* -1 so bias neuron doesn't need to calculate its output */
    for (int i = 0; i < this->nodesNum - 1; ++i)
        this->nodes[i]->feedForward();
}

void Layer::backPropagate()
{
    Node *n, *rN;
    Edge *rE;
    Layer *rL = this->rightLayer;
    double sum = 0;

    /* Calculate all output error, update threshold, and update weights */
    for (int i = 0; i < this->nodesNum; ++i) {
        n = this->nodes[i];
        sum = 0;

        for (int j = 0; j < rL->nodesNum; ++j) {
            rN = rL->nodes[j];
            rE = &rN->leftEdges[i];

            sum += rE->weight * rN->error;
        }

        /* update error */
        n->error = sum * n->output * (1 - n->output);

        /* update delta threshold */
        n->updateThreshold();

        /* update input edges weights */
        n->updateWeight();
    }
}

void Layer::backPropagate(std::vector<double> &expectedOutputs)
{
    Node *n;

    /* Calculate all output error, update threshold,
     * and update weights
     */
    for (int i = 0; i < this->nodesNum; ++i) {
        n = this->nodes[i];

        // update error
        n->error = Layer::derivativeOfSigmoid(expectedOutputs[i], n->output);

        // update delta threshold
        n->updateThreshold();

        // update input edges weights
        n->updateWeight();
    }
}

double Layer::derivativeOfSigmoid(double expectedOutput, double output)
{
    return (expectedOutput - output) * output * (1 - output);
}
