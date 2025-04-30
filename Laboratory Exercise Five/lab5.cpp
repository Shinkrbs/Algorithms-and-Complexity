#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <queue>
#include <limits>
#include <functional>
#include <cstring>
#include <ctime>

using namespace std;

#define edge pair<int, int>

// Boruvka's algorithm implementation
class GRAPH_BORUVKAS
{
	int V; // No. of vertices
	vector<vector<int> >graph; // default dictionary to store graph
	// A utility function to find set of an element i
	// (uses path compression technique)
	int find(vector<int>& parent, int i)
	{
		if (parent[i] == i) {
			return i;
		}
		return find(parent, parent[i]);
	}
	// A function that does union of two sets of x and y
	// (uses union by rank)
	void unionSet(vector<int>& parent, vector<int>& rank,
				int x, int y)
	{
		int xroot = find(parent, x);
		int yroot = find(parent, y);
		// Attach smaller rank tree under root of high rank
		// tree (Union by Rank)
		if (rank[xroot] < rank[yroot]) {
			parent[xroot] = yroot;
		}
		else if (rank[xroot] > rank[yroot]) {
			parent[yroot] = xroot;
		}
		// If ranks are same, then make one as root and
		// increment its rank by one
		else {
			parent[yroot] = xroot;
			rank[xroot]++;
		}
	}
public:
	GRAPH_BORUVKAS(int vertices)
	{
		V = vertices;
		graph = vector<vector<int> >();
	}
	// function to add an edge to graph
	void addEdge(int u, int v, int w)
	{
		graph.push_back({ u, v, w });
	}
	void generate_random_edges(int max_weight)
    {
        srand(time(NULL));
        for (int i = 0; i < V; i++)
        {
            for (int j = i + 1; j < V; j++)
            {
                int weight = (rand() % (max_weight -1));  // Generate random weight
                addEdge(i, j, weight);
            }
        }
    }
	// The main function to construct MST using Kruskal's
	// algorithm
	void boruvkaMST()
	{
		vector<int> parent(V);
		// An array to store index of the cheapest edge of
		// subset. It store [u,v,w] for each component
		vector<int> rank(V);
		vector<vector<int> > cheapest(V,
									vector<int>(3, -1));
		// Initially there are V different trees.
		// Finally there will be one tree that will be MST
		int numTrees = V;
		int MSTweight = 0;
		// Create V subsets with single elements
		for (int node = 0; node < V; node++) {
			parent[node] = node;
			rank[node] = 0;
		}
		// Keep combining components (or sets) until all
		// components are not combined into single MST
		while (numTrees > 1) {
			// Traverse through all edges and update
			// cheapest of every component
			for (int i = 0; i < graph.size(); i++) {
				// Find components (or sets) of two corners
				// of current edge
				int u = graph[i][0], v = graph[i][1],
					w = graph[i][2];
				int set1 = find(parent, u),
					set2 = find(parent, v);
				// If two corners of current edge belong to
				// same set, ignore current edge. Else check
				// if current edge is closer to previous
				// cheapest edges of set1 and set2
				if (set1 != set2) {
					if (cheapest[set1][2] == -1
						|| cheapest[set1][2] > w) {
						cheapest[set1] = { u, v, w };
					}
					if (cheapest[set2][2] == -1
						|| cheapest[set2][2] > w) {
						cheapest[set2] = { u, v, w };
					}
				}
			}
			// Consider the above picked cheapest edges and
			// add them to MST
			for (int node = 0; node < V; node++) {
				// Check if cheapest for current set exists
				if (cheapest[node][2] != -1) {
					int u = cheapest[node][0],
						v = cheapest[node][1],
						w = cheapest[node][2];
					int set1 = find(parent, u),
						set2 = find(parent, v);
					if (set1 != set2) {
						MSTweight += w;
						unionSet(parent, rank, set1, set2);
						numTrees--;
					}
				}
			}
			for (int node = 0; node < V; node++) {
				// reset cheapest array
				cheapest[node][2] = -1;
			}
		}
	}
};

// Kruskal's algorithm implementation
class GRAPH_KRUSKALS {
    private:
        vector<pair<int, edge> > G;  // graph
        vector<pair<int, edge> > T;  // mst
        int *parent;
        int V;  // number of vertices/nodes in graph
    public:
        GRAPH_KRUSKALS(int V);
        void AddWeightedEdge(int u, int v, int w);
        void generate_random_edges(int max_weight);
        int find_set(int i);
        void union_set(int u, int v);
        void kruskal();
        void print();
};

GRAPH_KRUSKALS::GRAPH_KRUSKALS(int x)
{
    parent = new int[x];
    V = x;
    //i 0 1 2 3 4 5
    //parent[i] 0 1 2 3 4 5
    for (int i = 0; i < V; i++)
        parent[i] = i;
    G.clear();
    T.clear();
}

void GRAPH_KRUSKALS::AddWeightedEdge(int u, int v, int w)
{
    G.push_back(make_pair(w, edge(u, v)));
}

int GRAPH_KRUSKALS::find_set(int i)
{
    // If i is the parent of itself
    if (i == parent[i])
    return i;
    else
    // Else if i is not the parent of itself
    // Then i is not the representative of his set,
    // so we recursively call Find on its parent
    return find_set(parent[i]);
}

void GRAPH_KRUSKALS::union_set(int u, int v)
{
    parent[u] = parent[v];
}

void GRAPH_KRUSKALS::generate_random_edges(int max_weight)
{
    srand(time(NULL));
    for (int i = 0; i < V; i++)
    {
        for (int j = i + 1; j < V; j++)
        {
            int weight = (rand() % (max_weight -1));  // Generate random weight
            AddWeightedEdge(i, j, weight);
        }
    }
}

void GRAPH_KRUSKALS::kruskal()
{
    int i, uRep, vRep;
    sort(G.begin(), G.end());  // increasing weight
    for (i = 0; i < G.size(); i++)
    {
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);
        if (uRep != vRep)
        {
          T.push_back(G[i]);  // add to tree
          union_set(uRep, vRep);
        }
    }
}

void GRAPH_KRUSKALS::print()
{
    cout << "Edge :"
     << " Weight" << endl;
    for (int i = 0; i < T.size(); i++)
    {
        cout << T[i].second.first << " - " << T[i].second.second << " : "
           << T[i].first;
        cout << endl;
    }
}

// Prim's Algorithm implementation
class GRAPH_PRIMS {
    private:
        int V;  // number of vertices/nodes in graph
        vector<vector<int>> matrix;
    public:
        GRAPH_PRIMS(int V);
        void generate_random_adjacency_matrix(int max_weight);
        void prims();
        void print();
};

GRAPH_PRIMS::GRAPH_PRIMS(int x)
{
    V = x;
    vector <int> vec;
    for(int i=0; i<x; i++)
        vec.push_back(0);
    for(int i=0; i<x; i++)
    {
        matrix.push_back(vec);
    }
}

void GRAPH_PRIMS::generate_random_adjacency_matrix(int max_weight)
{
    srand(time(NULL));
    int **temp = new int*[V];
    for(int i=0; i<V; i++)
        temp[i] = new int[V];
    for(int i=0; i<V; i++)
    {
        for(int j=0; j<V; j++)
        {
            int weight = (rand() % (max_weight -1)) + max_weight;
            if(i!=j)
            {
                temp[i][j] = weight;
                temp[j][i] = weight;
            }
        }
    }
    for(int i=0; i<V; i++)
    {
        for(int j=0; j<V; j++)
        {
            matrix[i][j] = temp[i][j];
        }
    }
    
    // Clean up the temp array
    for(int i=0; i<V; i++) {
        delete[] temp[i];
    }
    delete[] temp;
}

void GRAPH_PRIMS::prims()
{
    // Define INF within the function
    const int INF = 9999999;
    
    int no_edge;  // number of edge
    // create a array to track selected vertex
    // selected will become true otherwise false
    int *selected = new int[V];
    
    // set selected false initially
    memset(selected, false, sizeof(int) * V);
    
    // set number of edge to 0
    no_edge = 0;
    
    // choose 0th vertex and make it true
    selected[0] = true;
    int x;  //  row number
    int y;  //  col number
    
    while (no_edge < V - 1)
    {
    //For every vertex in the set S, find the all adjacent vertices
    // , calculate the distance from the vertex selected at step 1.
    // if the vertex is already in the set S, discard it otherwise
    //choose another vertex nearest to selected vertex  at step 1.
        int min = INF;
        x = 0;
        y = 0;
        for (int i = 0; i < V; i++)
        {
            if (selected[i])
            {
                for (int j = 0; j < V; j++)
                {
                    if (!selected[j] && matrix[i][j])
                    {  // not in selected and there is an edge
                        if (min > matrix[i][j])
                        {
                            min = matrix[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        selected[y] = true;
        no_edge++;
    }
    
    // Clean up
    delete[] selected;
}

int main()
{
    // Use the sizes specified in the provided main function
    int n[] = {1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000};
    int max_weight = 10;
    
    // Seed for random number generation
    srand(time(NULL));
    
    // For time measurements
    clock_t start, end;
    
    // Open file for output
    ofstream file("MST_Time.txt");
    
    for(int i = 0; i < 10; i++)
    {
        double kruskalTime, primsTime, boruvkasTime;
        cout << "Testing with size: " << n[i] << endl;
        
        // Kruskal's MST timing
        start = clock();
        GRAPH_KRUSKALS graph_kruskals(n[i]);
        graph_kruskals.generate_random_edges(max_weight);
        graph_kruskals.kruskal();
        end = clock();
        kruskalTime = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "Kruskal's MST time: " << kruskalTime << " sec" << endl;
        
        // Prim's MST timing
        start = clock();
        GRAPH_PRIMS graph_prims(n[i]);
        graph_prims.generate_random_adjacency_matrix(max_weight);
        graph_prims.prims();
        end = clock();
        primsTime = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "Prim's MST time: " << primsTime << " sec" << endl;
        
        // Boruvka's MST timing
        start = clock();
        GRAPH_BORUVKAS graph_boruvkas(n[i]);
        graph_boruvkas.generate_random_edges(max_weight);
        graph_boruvkas.boruvkaMST();
        end = clock();
        boruvkasTime = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "Boruvka's MST time: " << boruvkasTime << " sec" << endl;
        
        // Write results to file
        if(file.is_open())
            file << n[i] << ", " << kruskalTime << ", " << primsTime << ", " << boruvkasTime << "\n";
    }
    
    file.close();
    cout << "Results have been written to file.txt" << endl;
    
    return 0;
}