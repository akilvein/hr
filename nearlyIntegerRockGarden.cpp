
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <cassert>
#include <sstream>
#include <iterator>


using namespace std;



map<double, vector<pair<int, int> > > pointsByDistance() {
    map<double, vector<pair<int, int> > > result;

    for (int x = -12; x <= 12; x++) {
        for (int y = -12; y <= 12; y++) {
            double d = sqrt(x * x + y * y);
            if (d != round(d)) {
                auto &v = result[d];
                v.push_back(make_pair(x, y));
            }
        }
    }

    assert(result.size() == 68);

    return result;
}

vector<vector<pair<int, int> > > pointsByIndex() {
    auto m = pointsByDistance();


    vector<vector<pair<int, int> > > result;
    for (auto &i : m) {
        result.push_back(i.second);
    }

    assert(result.size() == 68);
    return result;
}


struct SixPoints {
    double sum;
    char indexes[6];
};


void addResult(const SixPoints &l, const SixPoints &r, vector<vector<int> > &combinations, vector<bool> &existing) {
    vector<int> combo;
    for (int i = 0; i < 6; i++) {
        combo.push_back(l.indexes[i]);
        combo.push_back(r.indexes[i]);
    }

    bool isNew = false;
    for (int i : combo) {
        if (!existing[i]) {
            isNew = true;
            existing[i] = true;
        }
    }

    if (!isNew) {
        return;
    }


    combinations.push_back(combo);


    stringstream ss;
    copy(combo.begin(), combo.end(), ostream_iterator<int>(ss,", "));

    cout << "{" << ss.str() << "}," << endl;
}


bool isPairValid(const SixPoints &l, const SixPoints &r, const vector<int> &distNums) {
    double sum = l.sum + r.sum;
    double sigma = abs(sum - round(sum));

    if (sigma < 0.9e-12) {
        vector<int> dn(distNums);

        for (int i : l.indexes) {
            dn[i]--;

            if (dn[i] < 0) {
                return false;
            }
        }

        for (int i : r.indexes) {
            dn[i]--;

            if (dn[i] < 0) {
                return false;
            }
        }

        return true;
    }

    return false;
}


void possibleSets() {
    auto pointsMap = pointsByDistance();

    vector<double> distVals;
    for (auto &i : pointsMap) {
        distVals.push_back(i.first);
    }

    vector<int> distNums;
    for (auto &i : pointsMap) {
        distNums.push_back(i.second.size());
    }

    vector<SixPoints> possibilities;

    int n = pointsMap.size();
    for (int i0 = 0; i0 < n; i0++) {
        for (int i1 = i0; i1 < n; i1++) {
            for (int i2 = i1; i2 < n; i2++) {
                for (int i3 = i2; i3 < n; i3++) {
                    for (int i4 = i3; i4 < n; i4++) {
                        for (int i5 = i4; i5 < n; i5++) {
                            possibilities.push_back({distVals[i0] + distVals[i1] + distVals[i2] + distVals[i3] + distVals[i4] + distVals[i5],
                                                     {(char)i0, (char)i1, (char)i2, (char)i3, (char)i4, (char)i5}});
                        }
                    }
                }
            }
        }
    }

    cout << "filled" << endl;

    for (SixPoints &sp : possibilities) {
        sp.sum -= floor(sp.sum);
    }

    cout << "normalized" << endl;

    sort(possibilities.begin(), possibilities.end(),
         [](const SixPoints &l, const SixPoints &r) { return l.sum < r.sum; }
    );


    cout << "sorted" << endl;


    vector<vector<int> > combinations;
    vector<bool> existing(pointsMap.size(), false);


    auto l = possibilities.begin();
    auto r = possibilities.end() - 1;

    while (l < r) {
        SixPoints &left = *l;
        SixPoints &right = *r;

        if (isPairValid(left, right, distNums)) {
            addResult(left, right, combinations, existing);
        }

        if (left.sum + right.sum > 1) {
            r--;
        } else {
            l++;
        }
    }

    for (int i = 0; i < (int)pointsMap.size(); i++) {
        assert(existing[i]);
    }

}

vector<vector<int> > combos = {
    {8, 4, 13, 25, 28, 27, 49, 37, 51, 43, 65, 45},
    {4, 10, 6, 19, 30, 33, 41, 59, 43, 59, 47, 59},
    {12, 15, 45, 23, 48, 47, 54, 52, 65, 57, 65, 65},
    {9, 26, 15, 31, 31, 34, 33, 34, 60, 37, 63, 41},
    {9, 15, 15, 31, 31, 34, 33, 34, 60, 37, 63, 56},
    {4, 1, 19, 30, 26, 32, 33, 43, 59, 47, 59, 59},
    {6, 2, 31, 13, 31, 30, 46, 31, 50, 45, 52, 54},
    {9, 7, 26, 31, 31, 34, 33, 34, 37, 56, 60, 63},
    {18, 18, 30, 28, 40, 31, 42, 48, 44, 49, 61, 66},
    {11, 35, 12, 37, 29, 43, 31, 44, 44, 57, 60, 64},
    {3, 2, 6, 20, 7, 26, 8, 34, 25, 39, 62, 43},
    {16, 9, 31, 16, 33, 31, 34, 34, 56, 37, 56, 63},
    {4, 3, 11, 21, 22, 34, 34, 34, 42, 35, 54, 47},
    {10, 9, 21, 21, 25, 24, 30, 41, 38, 44, 62, 48},
    {4, 28, 28, 33, 40, 41, 40, 45, 54, 54, 66, 55},
    {11, 29, 12, 31, 35, 37, 43, 44, 44, 57, 53, 67},
    {3, 7, 17, 8, 17, 16, 34, 20, 39, 25, 43, 26},
    {3, 14, 21, 36, 21, 36, 37, 37, 44, 54, 62, 66},
    {0, 8, 1, 10, 3, 25, 20, 39, 34, 43, 41, 62},
    {13, 5, 16, 30, 22, 31, 31, 31, 45, 46, 54, 52},
    {18, 21, 22, 26, 45, 46, 51, 53, 65, 58, 65, 65}
};


int getIndexAndRemove(pair<int, int> point, vector<vector<pair<int, int> > > &points) {

    for (int i = 0; i < (int)points.size(); i++) {
        vector<pair<int, int> > &v = points[i];

        auto it = find(v.begin(), v.end(), point);
        if (it != v.end()) {
            v.erase(it);
            return i;
        }
    }

    assert(false);
    return -1;
}


pair<int, int> getPointAndRemove(int index, vector<vector<pair<int, int> > > &points) {
    assert(index > 0);
    assert(index < (int)points.size());

    auto &v = points[index];

    assert(v.size() > 0);

    auto result = v[0];
    v.erase(v.begin());

    return result;
}


vector<int> getCombo(int index) {
    for (vector<int> combo : combos) {
        auto it = find(combo.begin(), combo.end(), index);
        if (it != combo.end()) {
            combo.erase(it);
            return combo;
        }
    }

    assert(false);
    return vector<int>();
}


int main()
{

    int x, y;
    cin >> x >> y;

    auto points = pointsByIndex();
    int index = getIndexAndRemove(make_pair(x, y), points);
    auto combo = getCombo(index);


    for (int i : combo) {
        auto point = getPointAndRemove(i, points);
        cout << point.first << " " << point.second << endl;
    }


    return 0;
}
