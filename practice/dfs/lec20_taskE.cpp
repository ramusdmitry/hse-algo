#include <iostream>
#include <vector>

using namespace std;

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

vector<vector<int>> g;
vector<int> used, color;

int dfs(int v){
    used[v] = 1;
    int cnt = 0;
    int any = 0;
    for (auto to : g[v]){
        if (!used[to]){
            cnt += dfs(to);
            any += color[to];
        }
    }
    if (any == 0){
        color[v] = 1;
        cnt++;
    }
    return cnt;
}

int main(){
    int n = 0;
    cin >> n;
    g = vector<vector<int>>(n + 1);
    used = vector<int>(n + 1, 0);
    color = vector<int>(n + 1, 0);
    int root = 0;
    for (auto from = 1; from <= n; ++from){
        int to = 0;
        cin >> to;
        if (to == 0) { // это корень
            root = from;
            continue;
        }
        g[from].push_back(to);
        g[to].push_back(from);
    }
    cout << dfs(root);
    return 0;
}