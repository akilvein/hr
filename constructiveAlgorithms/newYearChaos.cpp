#include <set>
#include <vector>
#include <iostream>

using namespace std;


int solution(vector<int> &q) {
    int counter = 0;
    
    set<int> tmp(q.begin(), q.end());
    
    for (int i = 0; i < (int)q.size(); i++) {
        tmp.erase(tmp.find(q[i]));        
        
        int d = 0;
        auto it = tmp.begin();
        while(it != tmp.end() && *it < q[i]) {
            it++;
            d++;
        }
        counter += d;
        
        if (d > 2) {
            return -1;
        }

    }
    
    return counter;
}


int main(){
    int T;
    cin >> T;
    for(int a0 = 0; a0 < T; a0++){
        int n;
        cin >> n;
        vector<int> q(n);
        for(int q_i = 0;q_i < n;q_i++){
           cin >> q[q_i];
        }
        // your code goes here
        
        int bribes = solution(q);
        
        if (bribes >= 0) {
            cout << bribes << endl;
        } else {
            cout << "Too chaotic" << endl;
        }
        
    }
    return 0;
}

