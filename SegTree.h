#ifndef _SEGTREE_H
#define _SEGTREE_H

#include <bits/stdc++.h>
using namespace std;

template <class T, class Func = function<T(const T &, const T &)>>
class SegTree {
private:
    int n;
    Func cbUpdate, cbGet;
    vector<T> ST;

public:
    SegTree(int sz, const Func &cbUpdate, const Func &cbGet, const T &init = T()) {
        n = 1;
        while (n < sz) n <<= 1;
        ST.assign(n << 1, init);
        this->cbUpdate = cbUpdate;
        this->cbGet = cbGet;
    }
    void update(int id, const T &val) {
        id += n - 1;
        for (ST[id] = cbUpdate(ST[id], val), id >>= 1; id >= 1; id >>= 1)
            ST[id] = cbGet(ST[id << 1], ST[id << 1 | 1]);
    }
    T get(int l, int r, const T &init = T()) {
        T ansL = init, ansR = init;
        for (l += n - 1, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ansL = cbGet(ansL, ST[l++]);
            if (r & 1) ansR = cbGet(ST[--r], ansR);
        }
        return cbGet(ansL, ansR);
    }
};

#endif // _SEGTREE_H