#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;


class Edge
{
    int capacity;
    int vertex1, vertex2;
    Edge *redge;

    public:
    Edge(int capacity, int vertex1, int vertex2);
    void setCapacity(int capacity);
    void setVertex1(int vertex1);
    void setVertex2(int vertex2);
    void setRedge(Edge *redge);
    int getCapacity();
    int getVertex1();
    int getVertex2();
    Edge* getRedge();
    bool operator==(Edge &edge1, Edge &edge2);
    ~Edge();
}

Edge::Edge(int capacity, int vertex1, int vertex2)
{
    this.capacity = capacity;
    this.vertex1 = vertex1;
    this.vertex2 = vertex2;
    this.redge = NULL;
}

Edge::~Edge()
{
    if(this.redge != NULL)
    {
        delete this.redge;
    }
}

bool Edge::operator==(Edge &edge1, Edge &edge2)
{
    return edge1.getVertex1() == edge2.getVertex1() and edge1.getVertex2() == edge2.getVertex2();
}

void Edge::setCapacity(int capacity)
{
    this.capacity = capacity;
}

void Edge::setVertex1(int vertex1)
{
    this.vertex1 = vertex1;
}

void Edge::setVertex2(int vertex2)
{
    this.vertex2 = vertex2;
}

int Edge::getCapacity()
{
    return this.capacity;
}

int Edge::getVertex1()
{
    return this.vertex1;
}

int Edge::getVertex2()
{
    return this.vertex2;
}

Edge* Edge::getRedge()
{
    return this.redge;
}

class NetworkFlow
{
    //Adjacent lists
    // Each list contains the edges that go out from the vertex index.
    unordered_map<int, vector<Edge>> adj;
    unordered_map<Edge, int> flow;

    public:
    void addEdge(int vertex1, int vertex2, int capacity);
    vector<Edge> findPath(int sourceVertex, int sinkVertex, vector<Edge> path);
}

void NetworkFlow::addEdge(int capacity, int vertex1, int vertex2)
{
    Edge edge = Edge(capacity, vertex1, vertex2);
    Edge redge = Edge(0, vertex2, vertex1);
    edge.setRedge(redge);
    redge.setRedge(edge);

    this.adj[vertex1].push_back(edge);
    this.adj[vertex2].push_back(redge);
    this.flow[edge] = 0;
    this.flow[redge] = 0;
}

vector<Edge> NetworkFlow::findPath(int sourceVertex, int sinkVertex, vector<Edge> path)
{
    if(sourceVertex == sinkVertex)
    {
        return path;
    }

    for(vector<Edge>::iterator edge = this.adj[sourceVertex].begin(); edge != this.adj[sourceVertex].end(); edge++)
    {
        int residual = edge->getCapacity() - this.flow[*edge];
        if(residual > 0 and find(path.begin(), path.end(), *edge) == path.end())
        {
            path.push_back(edge);
            vector<Edge> result = this.findPath(edge.getVertex2(), sinkVertex, path);
            if(!result.empty())
            {
                return result;
            }
        }
    }
}

int main()
{
    return 0;
}
