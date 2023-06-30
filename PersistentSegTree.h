#ifndef _PERSISTENT_SEGTREE
#define _PERSISTENT_SEGTREE

#include <bits/stdc++.h>
using namespace std;
 
class PersistentSegTree {
private:
    struct STNode {
        int sum = 0;
        STNode *l = nullptr, *r = nullptr;
        STNode() {}
        ~STNode() {
            if (l != nullptr) delete l;
            if (r != nullptr) delete r;
        }
    };

    int n;
    vector<STNode*> root;

public:
    PersistentSegTree(int sz, int nVer = 1) {
        n = sz;
        root.reserve(nVer);
        root.push_back(new STNode());
        build(root.back(), 1, n);
    }

    void build(STNode *id, int l, int r) {
        if (l == r) return;
        id->l = new STNode();
        id->r = new STNode();
        int m = (l + r) >> 1;
        build(id->l, l, m);
        build(id->r, m + 1, r);
    }

    STNode* update(STNode *id, int l, int r, int p, int val) {
        STNode *newId = new STNode();
        *newId = *id;

        if (l == r) {
            newId->sum += val;
            return newId;
        }
        int m = (l + r) >> 1;
        if (p <= m) newId->l = update(id->l, l, m, p, val);
        else newId->r = update(id->r, m + 1, r, p, val);
        newId->sum = newId->l->sum + newId->r->sum;

        return newId;
    }

    int k_th(STNode *lId, STNode *rId, int l, int r, int k) {
        if (l == r) return l;
        int m = (l + r) >> 1;
        int cntLeft = rId->l->sum - lId->l->sum;
        if (k <= cntLeft) return k_th(lId->l, rId->l, l, m, k);
        return k_th(lId->r, rId->r, m + 1, r, k - cntLeft);
    }

    void update(int p, int val) { root.push_back(update(root.back(), 1, n, p, val)); }
    int k_th(int u, int v, int k) { return k_th(root[u - 1], root[v], 1, n, k); }
    STNode* version() { return root.back(); }
};
 
#endif