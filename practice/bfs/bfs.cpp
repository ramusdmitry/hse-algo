#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int inf = 1e9;

/* input
8 10
0 1
0 5
1 2
2 4
2 3
3 4
3 5
5 6
6 4
6 7
 * */

/* output
 * 
 * 0->1;
1->2;
5->3;
2->4;
0->5;
5->6;
6->7;
 * */

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (auto i = 0; i < m; ++i){
        int from = 0, to = 0;
        cin >> from >> to;
        g[from].push_back(to);
        g[to].push_back(from);
    }
    vector<int> p(n, -1), r(n, inf); // список предков для запоминания кратчайших расстояний и массив расстояний
    // input
    queue<int> q;
    q.push(0);
    r[0] = 0;
    while (!q.empty()){
        int cur = q.front();
        q.pop();
        for (auto to : g[cur]) { // из текущей вершины начинаем просматривать все инцидентные
            if (r[cur] + 1 < r[to]){
                r[to] = r[cur] + 1; // фиксируем расстояние
                p[to] = cur; // фиксируем предыдущую вершину
                q.push(to);
            }
        }
    }

    for (auto i = 0; i < p.size(); ++i){
        if (p[i] == -1) continue;
        cout << p[i] << "->" << i << ";\n";
    }

    return 0;
}