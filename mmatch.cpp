#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge
{
    int capacity;
    bool reverse;
    int vertex1, vertex2;
    Edge *redge;
         
public:
    Edge(int capacity, int vertex1, int vertex2);
    void setCapacity(int capacity);
    void setVertex1(int vertex1);
    void setVertex2(int vertex2);
    void setRedge(Edge *redge);
    void setReverse(bool reverse);
    int getCapacity();
    int getVertex1();
    int getVertex2();
    Edge* getRedge();
    bool isReverse();
    bool operator==(Edge edge2);
};

Edge::Edge(int capacity, int vertex1, int vertex2)
{
    this->capacity = capacity;
    this->vertex1 = vertex1;
    this->vertex2 = vertex2;
    redge = NULL;
}

bool Edge::operator==(Edge edge2)
{
    return getVertex1() == edge2.getVertex1() && getVertex2() == edge2.getVertex2();
}

void Edge::setRedge(Edge *redge)
{
    this->redge = redge;
}

void Edge::setCapacity(int capacity)
{
    this->capacity = capacity;
}

void Edge::setReverse(bool reverse)
{
    this->reverse = reverse;
}

void Edge::setVertex1(int vertex1)
{
    this->vertex1 = vertex1;
}

void Edge::setVertex2(int vertex2)
{
    this->vertex2 = vertex2;
}

Edge* Edge::getRedge()
{
    return this->redge;
}

int Edge::getCapacity()
{
    return capacity;
}

int Edge::getVertex1()
{
    return vertex1;
}

int Edge::getVertex2()
{
    return vertex2;
}

bool Edge::isReverse()
{
    return reverse;
}

class NetworkFlow
{
    //Adjacent lists
    // Each list contains the edges that go out from the vertex index.
    vector< vector<Edge> > adj;
    // Matrix of flow
    int **flow;
    int sourceVertex, sinkVertex;
    int dimension;
    
public:
    NetworkFlow(int dimension);
    void addEdge(int vertex1, int vertex2, int capacity);
    vector<Edge> getEdges(int vertex);
    vector<Edge> findPath(int sourceVertex, int sinkVertex, vector<Edge> path);
    int findMaxFlow();
    int getSourceVertex();
    int getSinkVertex();
    void setSourceVertex(int sourceVertex);
    void setSinkVertex(int sinkVertex);
    ~NetworkFlow();

};

NetworkFlow::NetworkFlow(int dimension) : adj(dimension)
{
    flow = new int*[dimension];
    for(int index=0; index < dimension; index++)
    {
        flow[index] = new int[dimension];
        for(int inner_index=0; inner_index < dimension; inner_index++)
        {
            flow[index][inner_index] = 0;
        }
    }

    this->dimension = dimension;
}

NetworkFlow::~NetworkFlow()
{
    for(int index=0; index < dimension; index++)
    {
        delete[] flow[index];
	adj[index].erase(adj[index].begin());
    }

    delete[] flow;
    adj.erase(adj.begin());
}

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
    edge->setReverse(false);
    redge->setRedge(edge);
    redge->setReverse(true);
    adj[vertex1].push_back(*edge);
    adj[vertex2].push_back(*redge);

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
        int residual = edge->getCapacity() - flow[edge->getVertex1()][edge->getVertex2()];
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
            residuals.push_back(edge->getCapacity() - flow[edge->getVertex1()][edge->getVertex2()]);
        }
        
        int flowValue = *min_element(residuals.begin(), residuals.end());
        for(vector<Edge>::iterator edge = path.begin(); edge != path.end(); edge++)
        {
            flow[edge->getVertex1()][edge->getVertex2()] += flowValue;
            flow[edge->getVertex2()][edge->getVertex1()] -= flowValue;
        }
        path.clear();
        path = findPath(sourceVertex, sinkVertex, path);
    }
    
    int sum = 0;
    for(vector<Edge>::iterator edge = getEdges(sourceVertex).begin(); edge != getEdges(sourceVertex).end(); edge++)
    {
        if(!edge->isReverse())
        {
            sum += flow[edge->getVertex1()][edge->getVertex2()];
        }
    }
    
    return sum;
}

NetworkFlow* loadTestCase()
{
    NetworkFlow *assignments;
    
    int numberChildren, numberBeds;
    cin >> numberChildren >> numberBeds;
    assignments = new NetworkFlow(numberChildren + numberBeds + 2);
    int child, bed;
    cin >> child >> bed;
    while(child != 0 && bed != 0)
    {
        /*
         * Considering bed vertex are those represented for the interval
         * [numberChildren+1, numberChildren+numberBed]
         */
        
        assignments->addEdge(child - 1, numberChildren + bed - 1 , 1);
        cin >> child >> bed;
    }
    
    /*
     * Considering the "source" vertex is indexed by numberChildren+numberBed+1
     * and "sink" vertex is indexed by numberChildren+numberBed+2
     */
    assignments->setSourceVertex(numberChildren + numberBeds);
    assignments->setSinkVertex(numberChildren + numberBeds + 1);
    
    // Add all edges from the "source" vertex to those who symbolize children
    for(int indexChildren = 1; indexChildren <= numberChildren; indexChildren++)
    {
        assignments->addEdge(assignments->getSourceVertex(), indexChildren - 1, 1);
    }
    
    // Add all edges from all bed vertice to "sink" vertex
    for(int indexBed = 1; indexBed <= numberBeds; indexBed++)
    {
        assignments->addEdge(numberChildren + indexBed - 1, assignments->getSinkVertex(), 1);
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
        delete assignmentsChildrenBeds;
    }
    
    return 0;
}
