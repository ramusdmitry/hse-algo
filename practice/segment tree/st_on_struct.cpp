#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define fast ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);

struct tree {

    int lb = 0, rb = 0; // отрезок, который мы обслуживаем
    int64_t MAX = -2e9;
    tree *left = 0, *right = 0; // сведения о потомках (левый и правый)

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
        MAX = max(MAX, val);
        if (left != 0){
            if (id < left->rb){ // обращение к потомку для получения правой границы
                left->add(id, val);
            } else {
                right->add(id, val);
            }
        } // иначе потомков нет
    }

    int64_t get_max(int lq, int rq){
        if (lb >= lq && rb <= rq){ // отрезок, обслуживающий вершину полностью вошёл в запрос
            return MAX;
        } else if (max(lb, lq) >= min(rb, rq)) { // если неравенство выполняется, возвращаем мусорное число и отрезки не пересекаются
            return -2e9;
        } else {
            return max(left->get_max(lq, rq), right->get_max(lq, rq)); // отправляем обработку запроса ниже
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
    for (auto i = 0; i < m; ++i){
        cin >> lq >> rq;
        cout << t->get_max(lq, rq + 1) << " ";
    }

    return 0;
}