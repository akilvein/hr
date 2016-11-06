#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

template<typename PriorityKey>
class IndexedPQ {
    std::vector<int> mHeap;
    std::vector<int> mInverse;
    std::vector<PriorityKey> mKeys;
    int mSize = 0;

    inline void exch(int i, int j) {
        int swap = mHeap[i];
        mHeap[i] = mHeap[j];
        mHeap[j] = swap;
        mInverse[mHeap[i]] = i;
        mInverse[mHeap[j]] = j;
    }

    inline bool greater(int i, int j) {
        return mKeys[mHeap[i]] > mKeys[mHeap[j]];
    }

    inline void swim(int k) {
        while (k > 0 && greater((k - 1) / 2, k)) {
            exch(k, (k - 1) / 2);
            k = ((k - 1) / 2);
        }
    }

    inline void sink(int k) {
        while (2 * k + 1 < mSize) {
            int j = 2 * k + 1;
            if (j < mSize - 1 && greater(j, j+1))
                j++;
            if (!greater(k, j))
                break;
            exch(k, j);
            k = j;
        }
    }

public:
    IndexedPQ(int n) : mHeap(n), mInverse(n, -1), mKeys(n) {}

    bool notEmpty() {
        return mSize;
    }

    bool contains(int i) {
        assert(i >= 0);
        assert(i < (int)mKeys.size());

        return mInverse[i] != -1;
    }

    PriorityKey get(int i) {
        assert(i >= 0);
        assert(i < (int)mKeys.size());
        assert(contains(i));

        return mKeys[mInverse[i]];
    }

    void push(int i, PriorityKey key) {
        assert(i >= 0);
        assert(i < (int)mKeys.size());
        assert(!contains(i));

        mInverse[i] = mSize;
        mHeap[mSize] = i;
        mKeys[i] = key;
        swim(mSize);
        mSize++;
    }

    int pop() {
        assert(mSize);

        int min = mHeap[0];
        exch(0, --mSize);
        sink(0);
        assert(min == mHeap[mSize]);
        mInverse[min] = -1;
        return min;
    }

    void decrease(int i, PriorityKey key) {
        assert(i >= 0);
        assert(i < (int)mKeys.size());
        assert(contains(i));
        assert(key < mKeys[i]);

        mKeys[i] = key;
        swim(mInverse[i]);
    }

};

class UnionFind {
    std::vector<int> mParent;
    int mCount;

public:

    UnionFind(int n) : mParent(n), mCount(n) {
        for (size_t i = 0; i < mParent.size(); i++) {
            mParent[i] = i;
        }
    }

    int find(int p) {
        assert(p >= 0);
        assert(p < (int)mParent.size());

        while (p != mParent[p]) {
            mParent[p] = mParent[mParent[p]];
            p = mParent[p];
        }
        return p;
    }

    int size() {
        return mParent.size();
    }

    int count() {
        return mCount;
    }

    bool connected(int p, int q) {
        assert(p >= 0);
        assert(p < (int)mParent.size());
        assert(q >= 0);
        assert(q < (int)mParent.size());

        return find(p) == find(q);
    }

    void unite(int p, int q) {
        assert(p >= 0);
        assert(p < (int)mParent.size());
        assert(q >= 0);
        assert(q < (int)mParent.size());

        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) {
            return;
        }

        mParent[rootQ] = rootP;
        mCount--;
    }
};

struct Edge {
    int from;
    int to;
    int length;
};

int main() {
    int nNodes, nEdges;
    cin >> nNodes >> nEdges;
    
    vector<Edge> edges(nEdges);
    for (int i = 0; i < nEdges; i++) {
        int from, to, length;
        cin >> from >> to >> length;
        edges[i] = {from - 1, to - 1, length};
    }
    
    int start;
    cin >> start;
    start--;
    
    IndexedPQ<int> pq(nEdges);
    for (int i = 0; i < nEdges; i++) {
        pq.push(i, edges[i].length);
    }
    
    int totalLength = 0;
    UnionFind uf(nNodes);
    while(pq.notEmpty()) {
        int i = pq.pop();
        Edge e = edges[i];
        
        if (!uf.connected(e.from, e.to)) {
            uf.unite(e.from, e.to);
            totalLength += e.length;
        }
    }
    
    cout << totalLength << endl;
    
    return 0;
}

