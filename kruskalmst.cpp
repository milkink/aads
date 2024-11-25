#include <iostream>
#include <vector> 
using namespace std;

struct Edge
{
    int u,v,weight;
};

// Function to find the root of the set that 'node' belongs to 

int findSet(int node, vector<int>& parent)
{
    if (parent[node] == node)
    {
        return node;
    }
    return parent[node] = findSet(parent[node], parent);
}

// Function to unite two sets containing 'u' and 'v'

void unionSets(int u, int v, vector<int>& parent, vector<int>& rank)
{
    u = findSet(u, parent); 
    v = findSet(v, parent);

    if (u != v)
    {
    // Union by rank optimization 
        if (rank[u] < rank[v])
        {
            swap(u, v);
        }
        parent[v] = u;
        if (rank[u] == rank[v])
        {
            rank[u]++;
        }
    }
}
// Custom bubble sort to sort edges by weight 

void bubbleSort(vector<Edge>& edges) {
    int n = edges.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
 
                // Swap edges[j] and edges[j+1] 
                Edge temp = edges[j];
                edges[j] = edges[j + 1]; 
                edges[j + 1] = temp;
            }
        }
    }
}

// Kruskal's algorithm to find MST

int kruskal(int n, vector<Edge>& edges) {
    // Custom sorting using bubble sort 
    bubbleSort(edges);

    // Initialize the parent and rank arrays for union-find 
    vector<int> parent(n), rank(n, 0);
    for (int i = 0; i < n; i++) { 
        parent[i] = i;
    }

    int mst_weight = 0;
    vector<Edge> mst; // To store the MST edges

    // Process each edge
    for (Edge& edge : edges) { 
        int u = edge.u;
        int v = edge.v;

        // Check if the current edge forms a cycle 
        if (findSet(u, parent) != findSet(v, parent)) {
            mst_weight += edge.weight;
            mst.push_back(edge); // Include this edge in the MST 
            unionSets(u, v, parent, rank);
        }
    }

    // Display the MST edges
    cout << "Edges in the MST:\n"; 
    for (Edge& edge : mst) {
        cout << edge.u << " -- " << edge.v << " == " << edge.weight << endl;
    }
    return mst_weight;
}
 
int main() { 
    int n, m;
    cout << "Enter the number of vertices and edges: "; 
    cin >> n >> m;

    vector<Edge> edges(m);
    cout << "Enter the edges (u v weight):\n"; 
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;

    }

    int mst_weight = kruskal(n, edges);
    cout << "Minimum Spanning Tree weight: " << mst_weight << endl;

    return 0;
}
