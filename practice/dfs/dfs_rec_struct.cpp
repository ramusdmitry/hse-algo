#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
    int N = 0;
    vector<vector<int>> graph;
    vector<int> used;
public:
    vector<int> path;
    Graph(int num);
    void addEdge(int from, int to);
    void DFS(int vertex);
};

Graph::Graph(int num) {
    N = num;
    graph.resize(N);
    used.resize(N);
}

void Graph::addEdge(int from, int to) {
    graph[from].push_back(to);
}

void Graph::DFS(int from) {
    used[from] = 1;
    path.push_back(from);
    for (auto to : graph[from]){
        if (!used[to]){
            DFS(to);
            path.push_back(from);
        }
    }
}


int main(){
    int N = 0, M = 0, V = 0;
    cin >> N >> M >> V;
    N++;
    auto g = Graph(N);

    for (auto i = 0; i < M; ++i){
        int from = 0, to = 0;
        cin >> from >> to;
        g.addEdge(from, to);
        g.addEdge(to, from);
    }
    g.DFS(V);

    cout << g.path.size() << "\n";
    for (auto p : g.path){
        cout << p << " ";
    }
    return 0;
}