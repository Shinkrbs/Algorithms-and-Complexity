#include <iostream>
#include <vector>

using namespace std;

typedef struct node
{
    int data;
    vector<int> edges;
    vector<int> weights;
}*NODE;

typedef struct graph
{
    vector<NODE> nodes;
}*GRAPH;

NODE createNode(int data);
GRAPH createGraph(GRAPH g);
void addNode(GRAPH g, int data);
void addEdge(GRAPH g, int n1, int n2, int w);
void dispAdjList(GRAPH g);


int main()
{
    GRAPH g = createGraph(g); 

    addNode(g, 0);
    addNode(g, 1);
    addNode(g, 2);

    addEdge(g, 1, 0, 4);
    addEdge(g, 1, 2, 3);
    addEdge(g, 2, 0, 1);

    dispAdjList(g);
    return 0;
}

NODE createNode(int data)
{
    NODE x = new struct node;
    x->data = data;
    x->edges.clear();
    return x;
}

GRAPH createGraph(GRAPH g)
{
    GRAPH x = new struct graph;
    x->nodes.clear();
    return x;
}

void addNode(GRAPH g, int data)
{
    NODE x = createNode(data);
    g->nodes.push_back(x);
}

void addEdge(GRAPH g, int n1, int n2, int w)
{
    if(g->nodes.size() == 0)
        return; 
    for(int i = 0; i < g->nodes.size(); i++)
    {
        if(g->nodes[i]->data == n1)
        {
            g->nodes[i]->edges.push_back(n2);
            g->nodes[i]->weights.push_back(w);
        }

        if(g->nodes[i]->data == n2)
        {
            g->nodes[i]->edges.push_back(n1);
            g->nodes[i]->weights.push_back(w);
        }
    }
}

void dispAdjList(GRAPH g)
{
    for(int i = 0; i < g->nodes.size(); i++)
    {
        cout << g->nodes[i]->data << " : ";
        for(int j = 0; j < g->nodes[i]->edges.size(); j++)
            cout << "{" << g->nodes[i]->edges[j] << ", " << g->nodes[i]->weights[j] << "} ->";
        cout << "/" << endl;
    }
}