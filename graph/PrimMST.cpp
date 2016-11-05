#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

template<typename PriorityKey>
class indexedPQ {
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
    indexedPQ(int n) : mHeap(n), mInverse(n, -1), mKeys(n) {}

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

        return mKeys[i];
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

    pair<int, PriorityKey> pop() {
        assert(mSize);

        int min = mHeap[0];
        exch(0, --mSize);
        sink(0);
        assert(min == mHeap[mSize]);
        mInverse[min] = -1;
        return make_pair(min, mKeys[min]);
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

int main() {
    int nNodes, nEdges;
    cin >> nNodes >> nEdges;
    
    vector<vector<pair<int, int> > > adj(nNodes);
    for (int i = 0; i < nEdges; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        
        adj[from - 1].push_back(make_pair(to - 1, weight));
        adj[to - 1].push_back(make_pair(from - 1, weight));
    }
    
    int src;
    cin >> src;
    src--;
    
    indexedPQ<int> work(nNodes);
    work.push(src, 0);
    

    vector<bool> marked(nEdges, false);
    int totalWeight = 0;
    while(work.notEmpty()) {
        pair<int, int> nearestNode = work.pop();
        totalWeight += nearestNode.second;
        marked[nearestNode.first] = true;
        
        for (pair<int, int> edge : adj[nearestNode.first]) {
            int node = edge.first;
            int dist = edge.second;
            
            if (!marked[node]) {
                if (work.contains(node)) {
                    int oldDist = work.get(node);
                    if (dist < oldDist) {
                        work.decrease(node, dist);
                    }
                } else {
                    work.push(node, dist);
                }
            }
        }
    }
    
    cout << totalWeight << endl;
    
    return 0;
}

