#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;


int main() {
    ios::sync_with_stdio(false);

    int nNodes, nEdges;
    cin >> nNodes >> nEdges;



    vector<vector<int> > graph(nNodes, vector<int>(nNodes, numeric_limits<int>::max()));
    for (int i = 0; i < nNodes; i++) {
        graph[i][i] = 0;
    }

    for (int i = 0; i < nEdges; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph[from - 1][to - 1] = weight;
    }


    for (int k = 0; k < nNodes; k++) {
        for (int i = 0; i < nNodes; i++) {
            for (int j = 0; j < nNodes; j++) {
                if ((long)graph[i][j] > (long)graph[i][k] + (long)graph[k][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }



    int nQueries;
    cin >> nQueries;

    vector<int> results(nQueries);
    for (int i = 0; i < nQueries; i++) {
        int from, to;
        cin >> from >> to;

        results[i] = (graph[from - 1][to - 1] == numeric_limits<int>::max() ? -1 : graph[from - 1][to - 1]);
    }

    for (int d : results) {
        cout << d << endl;
    }

    return 0;
}

