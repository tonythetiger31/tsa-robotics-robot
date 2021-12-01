#include <vector>

class Node {
    public:
    Node(int nx, int ny);
    int x;
    int y;
    std::vector<Node*> ConnectedNodes;
    double EstimateDistanceToGoal(Node* GoalNode);
};

struct NodePathElement{
    public:
    NodePathElement(Node* Element, int DistanceToPastNode, int angle);
    Node* NodeElement;
    int Distance;
    int Angle;
};

struct NodePath{
    public:
    std::vector<NodePathElement*> Path;
    float PathCost;
    float AddNode(Node* NodeToAdd);
};