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
    int getVertex1() const;
    int getVertex2() const;
    Edge* getRedge();
    bool operator==(Edge edge2);
};

struct EdgeHash
{
    size_t operator()(const Edge& edge) const
    {
        return hash<int>()(edge.getVertex1()) ^ (hash<int>()(edge.getVertex2()) << 1);
    }
};

struct EdgeEqual
{
    bool operator()(const Edge& edge1, const Edge& edge2) const
    {
        return edge1.getVertex1() == edge2.getVertex1() and edge1.getVertex2() == edge2.getVertex2();
    }
};

Edge::Edge(int capacity, int vertex1, int vertex2)
{
    this->capacity = capacity;
    this->vertex1 = vertex1;
    this->vertex2 = vertex2;
    this->redge = NULL;
}

bool Edge::operator==(Edge edge2)
{
    return getVertex1() == edge2.getVertex1() and getVertex2() == edge2.getVertex2();
}

void Edge::setCapacity(int capacity)
{
    this->capacity = capacity;
}

void Edge::setVertex1(int vertex1)
{
    this->vertex1 = vertex1;
}

void Edge::setVertex2(int vertex2)
{
    this->vertex2 = vertex2;
}
void Edge::setRedge(Edge *redge)
{
    this->redge = redge;
}

int Edge::getCapacity()
{
    return capacity;
}

int Edge::getVertex1() const
{
    return vertex1;
}

int Edge::getVertex2() const
{
    return vertex2;
}

Edge* Edge::getRedge()
{
    return redge;
}

class NetworkFlow
{
    //Adjacent lists
    // Each list contains the edges that go out from the vertex index.
    unordered_map<int, vector<Edge> > adj;
    unordered_map<Edge, int, EdgeHash, EdgeEqual> flow;
    int sourceVertex, sinkVertex;
    
public:
    void addEdge(int vertex1, int vertex2, int capacity);
    vector<Edge> getEdges(int vertex);
    vector<Edge> findPath(int sourceVertex, int sinkVertex, vector<Edge> path);
    int findMaxFlow();
    int getSourceVertex();
    int getSinkVertex();
    void setSourceVertex(int sourceVertex);
    void setSinkVertex(int sinkVertex);
};

int NetworkFlow::getSourceVertex()
{
    return sourceVertex;
}

int NetworkFlow::getSinkVertex()
{
    return sinkVertex;
}

void NetworkFlow::setSourceVertex(int sourceVertex)
{
    this->sourceVertex = sourceVertex;
}

void NetworkFlow::setSinkVertex(int sinkVertex)
{
    this->sinkVertex = sinkVertex;
}

void NetworkFlow::addEdge(int vertex1, int vertex2, int capacity)
{
    Edge *edge = new Edge(capacity, vertex1, vertex2);
    Edge *redge = new Edge(0, vertex2, vertex1);
    edge->setRedge(redge);
    redge->setRedge(edge);
    
    adj[vertex1].push_back(*edge);
    adj[vertex2].push_back(*redge);
    flow[*edge] = 0;
    flow[*redge] = 0;
}

vector<Edge> NetworkFlow::getEdges(int vertex)
{
    return adj[vertex];
}

vector<Edge> NetworkFlow::findPath(int sourceVertex, int sinkVertex, vector<Edge> path)
{
    if(sourceVertex == sinkVertex)
    {
        return path;
    }
    
    for(vector<Edge>::iterator edge = adj[sourceVertex].begin(); edge != adj[sourceVertex].end(); edge++)
    {
        int residual = edge->getCapacity() - flow[*edge];
        if(residual > 0 && find(path.begin(), path.end(), *edge) == path.end())
        {
            path.push_back(*edge);
            vector<Edge> result = findPath(edge->getVertex2(), sinkVertex, path);
            if(!result.empty())
            {
                return result;
            }
        }
    }
    path.clear();
    return path;
}

int NetworkFlow::findMaxFlow()
{
    vector<Edge> path;
    path = findPath(sourceVertex, sinkVertex, path);
    while(!path.empty())
    {
        vector<int> residuals;
        for(vector<Edge>::iterator edge = path.begin(); edge != path.end(); edge++)
        {
            residuals.push_back(edge->getCapacity() - flow[*edge]);
        }
        
        int flowValue = *min_element(residuals.begin(), residuals.end());
        for(vector<Edge>::iterator edge = path.begin(); edge != path.end(); edge++)
        {
            flow[*edge] += flowValue;
            flow[*(edge->getRedge())] -= flowValue;
        }
        path.clear();
        path = findPath(sourceVertex, sinkVertex, path);
    }
    
    int sum = 0;
    for(vector<Edge>::iterator edge = getEdges(sourceVertex).begin(); edge != getEdges(sourceVertex).end(); edge++)
    {
        sum += flow[*edge];
    }
    
    return sum;
}

NetworkFlow* loadTestCase()
{
    NetworkFlow *assignments = new NetworkFlow();
    
    int numberChildren, numberBeds;
    cin >> numberChildren >> numberBeds;
    int child, bed;
    cin >> child >> bed;
    while(child != 0 && bed != 0)
    {
        /*
         * Considering bed vertex are those represented for the interval
         * [numberChildren+1, numberChildren+numberBed]
         */
        assignments->addEdge(child, numberChildren + bed, 1);
        cin >> child >> bed;
    }
    
    /*
     * Considering the "source" vertex is indexed by numberChildren+numberBed+1
     * and "sink" vertex is indexed by numberChildren+numberBed+2
     */
    assignments->setSourceVertex(numberChildren + numberBeds + 1);
    assignments->setSinkVertex(numberChildren + numberBeds + 2);
    
    // Add all edges from the "source" vertex to those who symbolize children
    for(int indexChildren = 1; indexChildren <= numberChildren; indexChildren++)
    {
        assignments->addEdge(assignments->getSourceVertex(), indexChildren, 1);
    }
    
    // Add all edges from all bed vertice to "sink" vertex
    for(int indexBed = 1; indexBed <= numberBeds; indexBed++)
    {
        assignments->addEdge(numberChildren + indexBed, assignments->getSinkVertex(), 1);
    }
    
    return assignments;
}

int main()
{
    cin.sync_with_stdio(false);
    int amountTestCases;
    cin >> amountTestCases;
    
    for(int indexTestCase=0; indexTestCase < amountTestCases; indexTestCase++)
    {
        NetworkFlow *assignmentsChildrenBeds = loadTestCase();
        cout << assignmentsChildrenBeds->findMaxFlow() << endl;
    }
    
    return 0;
}
