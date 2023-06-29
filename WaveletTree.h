#ifndef _WAVELET_TREE
#define _WAVELET_TREE

#include <bits/stdc++.h>
using namespace std;

template <typename Iterator>
class WaveletTree {
private :
    int lo, hi;
    WaveletTree *l, *r;
    vector<int> pre;

public:
    WaveletTree(Iterator first, Iterator last, int low, int high) {
        lo = low, hi = high;
        if (lo == hi || first >= last) return ;

        int mid = (lo + hi) >> 1;
        auto f = [&](int x) { return x <= mid; };

        pre.reserve(last - first + 1);
        pre.push_back(0);
        for (auto it = first; it != last; it++)
            pre.push_back(pre.back() + f(*it));

        auto pivot = stable_partition(first, last, f);
        l = new WaveletTree(first, pivot, low, mid);
        r = new WaveletTree(pivot, last, mid + 1, high);
    }

    ~WaveletTree() {
        delete l;
        delete r;
    }

    int lower(int lt, int rt, int x) {
        if (lt > rt || x < lo) return 0;
        if (hi <= x) return rt - lt + 1;
        return l->lower(pre[lt - 1] + 1, pre[rt], x) 
             + r->lower(lt - pre[lt - 1], rt - pre[rt], x);
    }

    int range(int lt, int rt, int low, int high) {
        return lower(lt, rt, high) - lower(lt, rt, low - 1);
    }

    int k_th(int lt, int rt, int k) {
        assert(lt <= rt);
        if (lo == hi) return lo;
        if (k <= pre[rt] - pre[lt - 1]) 
            return l->k_th(pre[lt - 1] + 1, pre[rt], k);
        return r->k_th(lt - pre[lt - 1], rt - pre[rt], k - (pre[rt] - pre[lt - 1]));
    }
};

#endif // _WAVELET_TREE