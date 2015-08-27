#include <bits/stdc++.h>
using namespace std;

// Fenwick Tree. Indices de 1 a n. 

struct FenTree {
    vector<int> tree;
    FenTree(int n) : tree(n + 1) {}
    
    void Actualizar(int i, int v) {
        while (i < tree.size()) {
            tree[i] += v;
            i += i & -i;
        }
    }
    
    int Query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= i & -i;
        }
        return sum;
    }
    
    int Rango(int i, int j) {
        return Query(j) - Query(i - 1);
    }
};

// Segment Tree. Version dinamica, para generar
// el arbol completo llamese la funcion Construir.

struct SegTree {
    int dato, i, d;
    SegTree* izq, *der;
    SegTree(int i_, int d_)
        : izq(NULL), der(NULL),
          i(i_), d(d_), dato() {}
    
    ~SegTree() {
        if (izq) delete izq;
        if (der) delete der;
    }
    
    void Construir() {
        if (i == d) return;
        int m = (i + d) >> 1;
        izq = new SegTree(i, m);
        der = new SegTree(m + 1, d);
        dato = izq->dato + der->dato;
    }
    
    int Update(int a, int v) {
        if (a < i || d < a) return dato;
        if (a == i && d == a) return dato = v;
        if (!left) {
            int m = (i + d) >> 1;
            izq = new SegTree(i, m);
            der = new SegTree(m + 1, d);
        }
        return dato = izq->Update(a, v) +
                      der->Update(a, v);
    }
    
    int Query(int a, int b) {
        if (b < i || d < a) return 0;
        if (a <= i && d <= b) return dato;
        return izq? izq->Query(a, b) + 
                    der->Query(a, b): 0;
    }
};





class UnionFind{
    private: vector<int> p,rank;
    
    public:
    UnionFind(int n){
        rank.assign( n,0);
        p.assign(n,0); for( inti i=0;i<n;i++) p[i]=i;
    }
    
    int findSet(int i){
        return (p[i]==i)?i:(p[i]=findSet(p[i]));
    }
    
    bool isSameSet(int i;int j){
        if(!isSameSet(i,j)){
            int x=findSet(i),y=findSet(j);
            if(rank[x] >rank[y])
                p[y]=x;
            else{
                p[x]=y;
                if(rank[x]==rank[y])
                    rank[y]++;
            }   
        }
    }
};

int main() {
    return 0;
}