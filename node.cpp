#include "node.h"
#include <random>
#include <ctime>
#include <cmath>
#include <QDebug>

Node::Node(int leftLayerNum)
{
    std::uniform_real_distribution<double> unif(0.0, 1.0);
    std::default_random_engine re;
    re.seed(std::time(NULL));

    /*
     * Initialise threshold nodes with a random
     * number between -1 and 1
     */
    this->threshold = -1 + (2 * unif(re));

    this->leftLayerNum = leftLayerNum;

    if (!this->leftLayerNum)
        return;

    /*
     * Initialise weight with a random
     * number between -1 and 1
     */
    this->leftEdges = std::shared_ptr<Edge[]> (new Edge[leftLayerNum]);

    for (int i = 0; i < this->leftLayerNum; ++i) {
        this->leftEdges[i].weight = -1 + (2 * unif(re));
        this->leftEdges[i].deltaWeight = 0.0;
    }
}

void Node::feedForward()
{
    double net = this->threshold;

    for (int i = 0; i < this->leftLayerNum; ++i)
        net += this->leftEdges[i].leftNode->output * this->leftEdges[i].weight;

    this->output = Node::sigmoid(net);
}

void Node::updateThreshold()
{
    // update delta threshold
    this->deltaThreshold = (LEARNING_RATE * this->error)
            + (MOMENTUM * this->deltaThreshold);

    // update threshold
    this->threshold += this->deltaThreshold;
}

void Node::updateWeight()
{
    double err = this->error;
    Edge *e;

    for (int i = 0; i < this->leftLayerNum; ++i) {
        e = &this->leftEdges[i];

        // update delta weight
        e->deltaWeight = (LEARNING_RATE * err * e->leftNode->output)
                + (MOMENTUM * e->deltaWeight);

        // update weight
        e->weight += e->deltaWeight;
    }
}

double Node::sigmoid(double net)
{
    return 1 / (1 + exp(-net));
}
