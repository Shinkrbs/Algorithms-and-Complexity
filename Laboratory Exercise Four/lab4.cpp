#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;

class Graph 
{
    int numVertices;
    vector<vector<int>> adjLists;  
    vector<bool> visited;

    public:
        Graph(int vertices);
        void addEdge(int src, int dest, bool bidirectional = false);
        void bfs(int startVertex);
        void dfs_iterative(int startVertex);  
        void resetVisited();
};

Graph::Graph(int vertices) 
{
    numVertices = vertices;
    adjLists.resize(vertices);
    visited.resize(vertices);
}

void Graph::addEdge(int src, int dest, bool bidirectional) 
{
    if (src < numVertices && dest < numVertices) 
    {
        adjLists[src].push_back(dest);
        if (bidirectional) 
            adjLists[dest].push_back(src);
    }
}

void Graph::resetVisited()
{
    fill(visited.begin(), visited.end(), false);
}

void Graph::bfs(int startVertex) 
{
    resetVisited();
    
    queue<int> q;
    
    visited[startVertex] = true;
    q.push(startVertex);

    while (!q.empty()) 
    {
        int currVertex = q.front();
        q.pop();
        
        for (int adjVertex : adjLists[currVertex]) 
        {
            if (!visited[adjVertex]) 
            {
                visited[adjVertex] = true;
                q.push(adjVertex);
            }
        }
    }
}

// Iterative DFS implementation 
void Graph::dfs_iterative(int startVertex) 
{
    resetVisited();
    
    stack<int> s;
    s.push(startVertex);
    
    while (!s.empty()) 
    {
        int currVertex = s.top();
        s.pop();
        
        if (!visited[currVertex]) 
        {
            visited[currVertex] = true;
            
            for (auto it = adjLists[currVertex].rbegin(); it != adjLists[currVertex].rend(); ++it) 
            {
                if (!visited[*it]) 
                    s.push(*it);
            }
        }
    }
}

void rec_to_text(string file_name, vector<double> &result) 
{
    ofstream file(file_name);
    if (!file) 
    {
        cout << "Error: Unable to Open File." << endl;
        return;
    }
    file << fixed << setprecision(10);
    for (const auto &results : result)
        file << results << "\n";

    cout << "Results have been written to " << file_name << "\n";
    file.close();
}

int main() 
{
    vector<int> sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    vector<double> result_bfs, result_dfs;
    
    // Seed for consistent testing
    srand(42);
    
    for (int size : sizes) 
    {
        cout << "Testing with size: " << size << endl;
        
        // Create graph inside the loop to free memory after each test
        Graph g(size);
        
        // Add random edges
        int num_edges = size * 2;
        for (int i = 0; i < num_edges; ++i)
        {
            int u = rand() % size;
            int v = rand() % size;

            if (u != v)
                g.addEdge(u, v, false); // Directed edge
        }

        // BFS timing
        auto start = chrono::high_resolution_clock::now();
        g.bfs(0);
        auto end = chrono::high_resolution_clock::now();
        double bfs_time = chrono::duration<double, milli>(end - start).count();
        result_bfs.push_back(bfs_time);
        cout << "BFS time: " << bfs_time << " ms" << endl;
        
        // DFS timing
        start = chrono::high_resolution_clock::now();
        g.dfs_iterative(0);  // Using iterative DFS
        end = chrono::high_resolution_clock::now();
        double dfs_time = chrono::duration<double, milli>(end - start).count();
        result_dfs.push_back(dfs_time);
        cout << "DFS time: " << dfs_time << " ms" << endl;
    }

    rec_to_text("BFS_Traversal_Times.txt", result_bfs);
    rec_to_text("DFS_Traversal_Times.txt", result_dfs);

    return 0;
}