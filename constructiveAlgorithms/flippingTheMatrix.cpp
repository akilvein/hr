#include <vector>
#include <iostream>

using namespace std;


int max(int i1, int i2, int i3, int i4) {
    return max(
        max(i1, i2),
        max(i3, i4)
    );
}



int main() {
    int nQueries;
    cin >> nQueries;
    
    for (int q = 0; q < nQueries; q++) {
        int n;
        cin >> n;
        
        vector<vector<int> > m(2 * n, vector<int>(2 * n));
        for (int r = 0; r < 2 * n; r++) {
            for (int c = 0; c < 2 * n; c++) {
                cin >> m[r][c];
            }
        }
        
        
        
        int total = 0;
        
        for (int r= 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                total += max(
                    m[r][c], 
                    m[r][2 * n - 1 - c], 
                    m[2 * n - 1 - r][c], 
                    m[2 * n - 1 - r][2 * n - 1 - c]
                );
            }
        }

        
        cout << total << endl;
    }
    
    return 0;
}

