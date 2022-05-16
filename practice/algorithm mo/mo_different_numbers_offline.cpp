#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

vector<ll> cnt;  // массив количества элементов встреченных на отрезке
vector<ll> meet;  // массив индексов наших элементов (чтобы получать за  О(1))
vector<ll> ans; // ответ

int sz = 0;
int res = 0;
int L = 0;
int R = -1;

struct query{
    int l, r, idx;
    ll res = 0;
    query(int l, int r, int idx) : l(l), r(r), idx(idx) {}
};

bool cmp(query &first, query &second){
    if (first.l / sz == second.l / sz){
        return first.r < second.r;
    }
    return first.l < second.l;
}

void add(int i){
    if (cnt[meet[i]]++ == 0)
        res++;
}
void del(int i){
    if (--cnt[meet[i]] == 0)
        res--;
}

void mo(query &q){
    // пока посчитанная предыдущая левая граница меньше границы запроса
    while (L < q.l){
        //del(L++);
        cnt[meet[L]]--; // убавляем в массиве кол-ве этого числа на этом отрезке (пояснить)
        if (cnt[meet[L]] == 0) 
            res--; // это оказалось неуникальное число, значит уменьшаем
        L++; // // двигаем вправо левую границу (не сохраняя в L)
    }
    // пока посчитанная предыдущая левая граница больше границы запроса
    while (L > q.l){
        //add(--L);
        L--; // двигаем влево левую границу (не сохраняя в L)
        if (cnt[meet[L]] == 0) // если новое число встречалось 0 раз
            res++; // прибавляем результат в переменную различных чисел
        cnt[meet[L]]++; // прибавляем в массив кол-ве этого числа на этом отрезке
    }
    // пока посчитанная предыдущая правая граница меньше границы запроса
    while (R < q.r){
        //add(++R);
        R++; // двигаем вправо правую границу (не сохраняя в R)
        if (cnt[meet[R]] == 0) // если новое число встречалось 0 раз 
            res++; // прибавляем результат в переменную различных чисел
        cnt[meet[R]]++; // прибавляем в массив кол-ве этого числа на этом отрезке
    }
    // пока посчитанная предыдущая правая граница больше границы запроса
    while (q.r < R){
        //del(R--);
        cnt[meet[R]]--; // убавляем в массиве кол-ве этого числа на этом отрезке (пояснить)
        if (cnt[meet[R]] == 0)
            res--; // это оказалось неуникальное число, значит уменьшаем
        R--; // двигаем влево правую границу (не сохраняя в R)
    }

    q.res = res;
    ans[q.idx--] = q.res;
}

void bs(vector<int> &vec, int i){
    int l = -1, r = vec.size();
    while (r - l > 1){
        int m = (l + r) / 2;
        if (vec[m] <= meet[i]){
            l = m;
        } else {
            r = m;
        }
    }
    meet[i] = l;
}

int main() {
    int n, k, idx = 0, L = 0, R = -1;
    cin >> n;

    sz = static_cast<int>(sqrt(n)); // size of block
    // выделяем n элементов на массив подсчёта и индексов
    cnt.resize(n);
    meet.resize(n);

    fill(cnt.begin(), cnt.end(), 0);

    //считываем входные данные и чтобы не было мусора маркируем в массиве meet
    vector<int> vec(n);
    for (auto i = 0; i < n; ++i){
        cin >> vec[i];
        meet[i] = vec[i];
    }

    // через бинарный поиск находим индексы элементов массива
    sort(vec.begin(), vec.end());
    for (auto i = 0; i < n; ++i) {
        bs(vec, i);
    }

    //считываем запросы и выделяем под ответ массив размера k
    cin >> k;
    ans.resize(k);
    vector<query> Q;
    while (k--){
        int l, r;
        cin >> l >> r;
        Q.emplace_back(--l, --r, idx++);
        // так как индексация с 0
    }

    //сортируем запросы, чтобы упростить подсчёт (оффлайн)
    sort(Q.begin(), Q.end(), cmp);

    for (auto &i : Q){
        mo(i);
    }

    for (auto i : ans){
        cout << i << "\n";
    }

    return 0;
}