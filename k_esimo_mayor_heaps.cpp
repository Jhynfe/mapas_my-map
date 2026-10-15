#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
 
template<typename data_type>
struct Heap {
    int _size;
    vector<data_type> a;
    Heap(int size=0) : _size(size) {
        a = vector<data_type>();
    }
    Heap(const vector<data_type> v) : _size(v.size()), a(move(v)) {
        build_heap();
    }
 
    int left(int p) {
        return (p<<1)|1;
    }
    int right(int p) {
        return (p<<1)+2;
    }
    int parent(int p) {
        return (p-1)>>1;
    }
    data_type top()const {
        return a[0];
    }
    void pop() {
        swap(a[0], a[_size-1]);
        a.pop_back();
        --_size;
        sift_down(0);
    }
    data_type extract_min() {
        data_type temp = a[0];
        pop();
        return temp;
    }
    void insert(data_type x) {
        a.emplace_back(x);
        ++_size;
        sift_up(_size-1);
    }
    void sift_down(int p) {
        while (left(p) < _size) {
            int m = p;
            int l = left(p), r = right(p);
 
            if (l < _size && a[l] < a[m]) {
                m = l;
            }
            if (r < _size && a[r] < a[m]) {
                m = r;
            }
            if (m == p) break;
            swap(a[p], a[m]);
            p = m;
        }
    }
    void sift_up(int u) {
        while (u > 0 && a[u] < a[parent(u)]) {
            swap(a[parent(u)], a[u]);
            u = parent(u);
        }
    }
    void build_heap() {
        for (int i=parent(_size-1);i>=0; --i) {
            sift_down(i);
        }
    }
    bool check_heap() {
 
        return true;
    }
    int size() const {
        return _size;
    }
    data_type devolver_posicion(int m) {
        return a[m];
    }
    bool empty() const {
        return _size == 0;
    }
};
 
int main(){
    Heap<int> heap;
    long long r, m;
    cin >> r >> m;
    for (int i = 1; i <= r; ++i) {
        int n;
        cin >> n;
        if (heap.size() < m) {
            heap.insert(n);
        }
        else {
 
            heap.insert(n);
            heap.pop();
        }
 
        if (heap.size() < m) {
            cout << "NONE"<< endl;
        }
        else {
            cout << heap.devolver_posicion(0) << endl;
        }
    }
    return 0;
}
