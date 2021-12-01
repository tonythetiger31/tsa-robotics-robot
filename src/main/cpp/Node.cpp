#include "Node.h"
#include <cmath>

Node::Node(int nx, int ny){
    x = nx;
    y = ny;
}

double Node::EstimateDistanceToGoal(Node* GoalNode){
    return std::sqrt(std::pow(GoalNode->x - x, 2)+std::pow(GoalNode->y - y, 2));
}

NodePathElement::NodePathElement(Node* Element, int DistanceToPastNode, int angle){
    NodeElement = Element;
    Distance = DistanceToPastNode;
    Angle = angle;
}

float NodePath::AddNode(Node* NodeToAdd){
    int Dis;
    int NewAngle;
    if (Path.size() != 0){
        Dis = static_cast<int>(std::sqrt(std::pow(NodeToAdd->x - Path.back()->NodeElement->x, 2)+std::pow(NodeToAdd->y - Path.back()->NodeElement->y, 2)));
        NewAngle = (std::acos((NodeToAdd->x - Path.back()->NodeElement->x)/Dis)/3.14159)*180;
        if (NodeToAdd->y - Path.back()->NodeElement->y < 0)
            NewAngle = 360 - NewAngle;
    }
    else{
        Dis = 0;
        NewAngle = 0;
    }

    NodePathElement* NewNodeElement = new NodePathElement(NodeToAdd, Dis, NewAngle);
    
    Path.emplace_back(NewNodeElement);
    PathCost += Dis;
}