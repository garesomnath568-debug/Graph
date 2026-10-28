
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight, id;
};

bool compare(Edge a, Edge b) {
    if (a.weight != b.weight)
        return a.weight < b.weight;
    return a.id < b.id;
}

int findParent(int x, vector<int>& parent) {
    if (parent[x] == x)
        return x;
    return parent[x] = findParent(parent[x], parent);
}

bool unite(int a, int b, vector<int>& parent) {
    a = findParent(a, parent);
    b = findParent(b, parent);

    if (a == b)
        return false;

    parent[a] = b;
    return true;
}

void kruskal(int V, vector<Edge> edges) {
    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(V + 1);
    for (int i = 1; i <= V; i++)
        parent[i] = i;

    int count = 0;
    long long totalCost = 0;

    cout << "\nSelected pipelines:\n";
    cout << "ID\tPipeline\tWeight\tRunning Cost\n";

    for (Edge e : edges) {
        if (unite(e.u, e.v, parent)) {
            totalCost += e.weight;
            count++;

            cout << e.id << "\t"
                 << e.u << "-" << e.v << "\t\t"
                 << e.weight << "\t"
                 << totalCost << "\n";

            if (count == V - 1)
                break;
        }
    }

    cout << "Total installation cost: "
         << totalCost << "\n";

    if (count == V - 1)
        cout << "A spanning tree can be formed.\n";
    else
        cout << "Graph is disconnected. "
             << "A spanning tree cannot be formed.\n";
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

        edges[i].id = i + 1;

        if (edges[i].u < 1 || edges[i].u > V ||
            edges[i].v < 1 || edges[i].v > V) {
            cout << "Invalid tank number.\n";
            return 0;
        }
    }

    cout << "\n--- Original MST ---\n";
    kruskal(V, edges);

    if (E == 0) {
        cout << "No pipeline is available to update.\n";
        return 0;
    }

    int id, newWeight;

    cout << "\nEnter pipeline ID to update (1 to "
         << E << "): ";
    cin >> id;

    if (id < 1 || id > E) {
        cout << "Invalid pipeline ID.\n";
        return 0;
    }

    cout << "Enter new weight: ";
    cin >> newWeight;

    edges[id - 1].weight = newWeight;

    cout << "\n--- Updated MST ---\n";
    kruskal(V, edges);

    return 0;
}