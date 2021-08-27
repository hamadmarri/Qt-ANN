#ifndef NODE_H
#define NODE_H

#include <vector>
#include "defines.h"

class Node;

struct Edge {
    Node *leftNode;
    double weight;
    double deltaWeight;
};

class Node
{
public:
    Node(int leftLayerNum);

    void feedForward();
    void updateThreshold();
    void updateWeight();

    int leftLayerNum;
    double threshold;
    double output;
    double error;
    double deltaThreshold = 0;

    std::vector<Edge> leftEdges;
private:
    static double sigmoid(double net);
};

#endif // NODE_H
