#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int inf = 10e7;

/*
 * Если индексация массива начинается с 0, то потомки высчитываются как 2v+1, 2v+1;
 * Если индексация массива начинается с 1, то потомки высчитываются как 2v, 2v+1;
 * */

void build(vector<int> &vec, vector<int> &tree, int v, int l, int r){
    if (r - l == 1){
        tree[v] = vec[l];
        return;
    }
    int m = (l + r) / 2; // середина нашего отрезка (обычно от 0 до размера массива)
    build(vec, tree, 2 * v + 1, l, m); // построение для левого потомка
    build(vec, tree, 2 * v + 2, m, r); // построение для правого потомка
    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]); // максимум из дочерних вершин
}
int query(vector<int> &vec, vector<int> &tree, int v, int l, int r, int ql, int qr){
    // v, l, r нужно для того чтобы понимать, где мы находимся
    // ql, qr - сами запросы
    if (ql <= l && r <= qr){ // состояние, когда мы полностью находимся в пределах запроса
        return tree[v];
    } else if (r <= ql || qr <= l){ // вышли за пределы какой-то границы
        return -inf;
    } else {
        int m = (l + r) / 2;
        int ans_left = query(vec, tree, 2 * v + 1, l, m, ql, qr);
        int ans_right = query(vec, tree, 2 * v + 2, m, r, ql, qr);
        return max(ans_left, ans_right);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> vec(n);
    vector<int> tree(n * 4);
    for (auto i = 0; i < n; ++i){
        cin >> vec[i];
    }
    build(vec, tree, 0, 0, n + 1);
    int k;
    cin >> k;
    for (auto i = 0; i < k; ++i){
        int l, r;
        cin >> l >> r;
        cout << query(vec, tree, 0, 0, n + 0, l, r) << " ";
    }
    return 0;
}
