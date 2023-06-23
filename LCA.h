#ifndef _LCA_H
#define _LCA_H

#include <bits/stdc++.h>
using namespace std;

class LCA {
private:
    int n;
    vector<int> high;
    vector<vector<int>> up;

public:
    LCA(int sz, const vector<vector<int>> &adj) {
        n = sz;
        high.assign(n + 1, 0);
        up.assign(__lg(n) + 1, vector<int>(n + 1, 0));
        
        function<void(int, int)> dfs = [&](int u, int p) {
            high[u] = high[p] + 1;

            up[0][u] = p;
            for (int i = 1; i <= __lg(n); i++)
                if (up[i - 1][up[i - 1][u]]) 
                    up[i][u] =  up[i - 1][up[i - 1][u]];
                
            for (int v: adj[u]) 
                if (v != p) dfs(v, u);
        };
        dfs(1, 0);
    }
    int get(int u, int v) {
        if (high[u] != high[v]) {
            if (high[u] < high[v]) swap(u, v);

            int k = high[u] - high[v];
            for (int i = __lg(k); i >= 0; i--) 
                if (k >> i & 1) {
                    u = up[i][u];
                }
        }
        if (u == v) return u;

        for (int i = __lg(high[u]); i >= 0; i--)
            if (up[i][u] != 0 && up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        
        return up[0][u];
    }
};

#endif