#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Решение задачи D: https://contest.yandex.ru/contest/37572/problems/D

#define fast ios_base::sync_with_stdio(0); cin.tie(0);

vector<int> used, path;
vector<vector<int>> g;
void dfs(int v){
    used[v] = 1;
    path.push_back(v); // записываем вершину в путь (т.е отслеживаем стек активных вершин)
    for (auto to : g[v]){ // просматриваем все вершины в которые можем сделать шаг
         if (!used[to]){
             dfs(to);
             path.push_back(v); // чтобы записать путь
             //path.pop_back(); // если вышли из вершины (рекурсия отработала)
         }
    }
}

int main() {
    int n = 0, m = 0, v = 0;
    // кол-во вершин, рёбер и стартовая вершина
    std::cin >> n >> m >> v;
    n++;
    //считываем как список смежности
    g.resize(n);
    used.resize(n);
    for (size_t i = 0; i < m; ++i) {
        int f = 0, t = 0;
        std::cin >> f >> t;
        g[f].push_back(t);
        g[t].push_back(f);
    }
    dfs(v);
    cout << path.size() << "\n"; // так как граф с одной компонентой связности, то достаточно получить размер массив пути
    for (auto p : path){
        cout << p << " ";
    }

    return 0;
}