#include <iostream>
#include <vector>

using namespace std;
// https://contest.yandex.ru/contest/37572/problems/E/
vector<vector<int>> g;
vector<int> used, path, ans;

void dfs(int v){
    used[v] = 1;
    path.push_back(v);
    for (auto to : g[v]){
        if (!used[to]){
            dfs(to);
        }
    }
    if (ans.size() < path.size()){
        ans = path;
    }
    path.pop_back();
}

int main(){
    int n;
    cin >> n;
    g = vector<vector<int>>(n + 1);
    used = vector<int>(n + 1, 0);
    for (auto i = 0; i < n - 1; ++i){
        int from = 0; int to = 0;
        cin >> from >> to;
        g[from].push_back(to);
        g[to].push_back(from);
    }

    dfs(1);
    fill(used.begin(), used.end(), 0);
    dfs(ans.back());
    auto c = ans.size() / 2;
    if (ans.size() % 2 == 1){
        cout << c << " " << 1 << " " << ans[c];
    } else {
        int x = ans[c - 1], y = ans[c];
        if (x > y)
            swap(x, y);
        cout << c << " " << 2 << " " << x << " " << y;
    }
    return 0;
}