#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int sz = 0;
struct query{
    int l, r, idx;
    int64_t res = 0;
    query(int l, int r, int idx) : l(l), r(r), idx(idx) {}
};


bool cmp(query &first, query &second){
    if (first.l / sz == second.l / sz){
        return first.r < second.r;
    }
    return first.l < second.l;
}

void mo(vector<int64_t> &vec, int l, int r, query &q){
    while (q.l < l){
        --l;
        q.res += vec[l];
    }
    while (q.r > r){
        ++r;
        q.res += vec[r];
    }
    while (q.l > l){
        q.res -= vec[l];
        ++l;
    }
    while (q.r < r){
        q.res -= vec[r];
        --r;
    }
}

int main() {
    int n, k;
    cin >> n;
    sz = sqrt(n);
    vector<int64_t> vec(n);
    for (auto i = 0; i < n; ++i){
        cin >> vec[i];
    }
    cin >> k;
    int idx = 0;
    vector<query> Q;
    while (k--){
        int l, r;
        cin >> l >> r;
        Q.emplace_back(--l, --r, idx++);
    }
    int L = 0;
    int R = -1;
    sort(Q.begin(), Q.end(), cmp);
    for (auto &i : Q){
        mo(vec, L, R, i);

    }

    sort(Q.begin(), Q.end(), [](query a, query b){
        return a.idx < b.idx;
    });

    for (auto i : Q){
        cout << i.res << " ";
    }

    return 0;
}