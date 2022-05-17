#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Решение задачи D: https://contest.yandex.ru/contest/37572/problems/D 

#define fast ios_base::sync_with_stdio(0); cin.tie(0);

int main() {
    int n = 0, m = 0, v = 0;
    // кол-во вершин, рёбер и стартовая вершина
    std::cin >> n >> m >> v;
    n++;
    //считываем как список смежности
    std::vector<std::vector<int>> g(n);
    for (size_t i = 0; i < m; ++i) {
        int f = 0, t = 0;
        std::cin >> f >> t;
        g[f].push_back(t);
        g[t].push_back(f);
    }
    // запоминаем номер вершины и ту позицию на которой мы остались при просмотре
    std::vector<std::pair<int, int>> stack;
    std::vector<int> used(n);
    used[v] = 1; // маркируем начальную вершину
    stack.push_back({ v, 0 }); // кладём её в стек с 0-вой позицией
    std::cout << 2 * n - 3 << '\n';
    while (!stack.empty()) {
        int cur = stack.back().first; // текущая вершина
        int pos = stack.back().second; // её позиция
        std::cout << cur << ' ';
        bool any = false; // изначально мы не сделали никакого шага вперёд
        for (size_t i = pos; i < g[cur].size(); ++i) {
            int to = g[cur][i]; // следующая вершина
            // вершина не посещена
            if (!used[to]) {
                used[to] = 1; // маркируем вершину
                stack[stack.size() - 1].second = i + 1; // на последнем элементе меняем позицию на текущую + 1 (на каком месте мы остановились)
                stack.push_back({ to, 0 }); //  кладём в стек новую вершину, которую только что посетили
                any = true; // идём узнавать новую информацию о других вершинах (делаем шаг вперёд)
                break; // выходим и переходим к следующей вершине
            }
        }
        if (!any) stack.pop_back(); // если не можем сделать ни шага (или не сделали), то убираем последнюю вершину
    }
    return 0;
}