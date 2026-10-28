
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

int findParent(int x, vector<int>& parent) {
    if (parent[x] == x)
        return x;
    return parent[x] = findParent(parent[x], parent);
}

void unite(int a, int b, vector<int>& parent) {
    a = findParent(a, parent);
    b = findParent(b, parent);
    parent[a] = b;
}

int main() {
    int V, E;

    cout << "Enter number of tanks: ";
    cin >> V;

    cout << "Enter number of pipelines: ";
    cin >> E;

    if (V <= 0 || E < 0) {
        cout << "Invalid input.\n";
        return 0;
    }

    vector<Edge> edges(E);

    cout << "Enter source, destination and cost:\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v
            >> edges[i].weight;

        if (edges[i].u < 1 || edges[i].u > V ||
            edges[i].v < 1 || edges[i].v > V) {
            cout << "Invalid tank number.\n";
            return 0;
        }
    }

    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(V + 1);
    for (int i = 1; i <= V; i++)
        parent[i] = i;

    int count = 0;
    long long totalCost = 0;

    cout << "\nSelected pipelines:\n";

    for (Edge e : edges) {
        int a = findParent(e.u, parent);
        int b = findParent(e.v, parent);

        if (a != b) {
            cout << e.u << " - " << e.v
                 << " : " << e.weight << "\n";

            unite(a, b, parent);
            totalCost += e.weight;
            count++;

            if (count == V - 1)
                break;
        }
    }

    if (count == V - 1)
        cout << "Total installation cost: "
             << totalCost << "\n";
    else
        cout << "Spanning tree cannot be formed.\n";

    return 0;
}