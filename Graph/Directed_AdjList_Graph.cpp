#include <iostream>
#include <vector>

using namespace std;
// Directed Graph using Adjacency List

typedef struct node 
{
    int data; // Data of Node
    vector<int> edge; // edge
}*NODE;

typedef struct graph 
{
    vector<NODE> nodes; // Nodes of Graph
}*GRAPH;

NODE createNode(GRAPH g, int data); // Create new node and directly insert it into the graph
GRAPH createGraph(GRAPH g); // Create graph
void addNode(GRAPH g, int data); // Add node to graph
void addEdge(GRAPH g, int n1, int n2); // Add edge between two nodes
void dispAdjList(GRAPH g); // Display adj list of graph

int main()
{
    GRAPH g = createGraph(g); 

    addNode(g, 0);
    addNode(g, 1);
    addNode(g, 2);

    addEdge(g, 1, 0);
    addEdge(g, 1, 2);
    addEdge(g, 2, 0);

    dispAdjList(g);
    return 0;
}

NODE createNode(GRAPH g, int data)
{
    NODE newNode = new struct node;
    newNode->data = data;
    newNode->edge.clear(); // Ensure edge vector is clear
    return newNode;
}

GRAPH createGraph(GRAPH g)
{
    g = new struct graph;
    g->nodes.clear(); // Initialize the nodes vector, ensure it's empty
    return g;
}

void addNode(GRAPH g, int data)
{
    NODE x = createNode(g, data);
    g->nodes.push_back(x);
}

void addEdge(GRAPH g, int n1, int n2)
{
    for(int i = 0; i < g->nodes.size(); i++)
    {
        if(g->nodes[i]->data == n1)
            g->nodes[i]->edge.push_back(n2);
    }
}

void dispAdjList(GRAPH g)
{
    for(int i = 0; i < g->nodes.size(); i++)
    {
        cout << g->nodes[i]->data << " : ";
        for(int j = 0; j < g->nodes[i]->edge.size(); j++)
            cout << g->nodes[i]->edge[j] << "->";
        cout << "/" << endl;
    }    
}