#include <iostream>
#include <cmath>
using namespace std;

#define fast ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);

int64_t gcd(int64_t a, int64_t b) {
    if (a < b) {
        std::swap(a, b);
    }
    while (b != 0) {
        long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

struct tree {

    int lb = 0, rb = 0; // отрезок, который мы обслуживаем
    int64_t gcd_ = 0;
    tree *left = nullptr, *right = nullptr; // сведения о потомках (левый и правый)

    tree(int lb, int rb){
        this->lb = lb;
        this->rb = rb;
        // рекурсивное построение дерева
        if (lb + 1 < rb){
            int m = (lb + rb) / 2;
            this->left = new tree(lb, m);
            this->right = new tree(m, rb);
        }
    }
    //процедура добавления с номером вершины
    void add(int id, int64_t val) {
        gcd_ = gcd(gcd_, val);
        if (left != nullptr){
            if (id < left->rb){ // обращение к потомку для получения правой границы
                left->add(id, val);
            } else {
                right->add(id, val);
            }
        } // иначе потомков нет
    }

    int64_t get_gcd(int lq, int rq){
        if (lb >= lq && rb <= rq){ // отрезок, обслуживающий вершину полностью вошёл в запрос
            return gcd_;
        } else if (max(lb, lq) >= min(rb, rq)) { // если неравенство выполняется, возвращаем мусорное число и отрезки не пересекаются
            return 0;
        } else {
            return gcd(left->get_gcd(lq, rq), right->get_gcd(lq, rq)); // отправляем обработку запроса ниже
        }
    }

};

int main(){
    fast
    int n = 0, m = 0, x = 0, lq = 0, rq = 0;
    cin >> n;
    tree* t = new tree(1, n + 1);
    for (auto i = 1; i <= n; ++i){
        cin >> x;
        t->add(i, x);
    }
    cin >> m;
    for (auto i = 1; i <= m; ++i){
        cin >> lq >> rq;
        cout << t->get_gcd(lq, rq + 1) << " ";
    }

    return 0;
}