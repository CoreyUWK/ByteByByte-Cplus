// Online C++ compiler to run C++ program online
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <cassert>
#include <queue>
using namespace std;

/* Find the nth order statistis in array. 
That is the nth min value in unsorted array. 
1) Brute force: O(n^2)
loop and search for min, then loop again and find next min.
would need a hash to track visited nodes.
2) maybe use a max heap of nth size and then after pop nth times to get nth min. 
O(n) search over arr and O(logn) for heap making O(nlogn)
3) partial sort and then take nth. O(nlogn)
4) create a sorted linkedlist O(n) then return nth value.
*/
int nthMin(const vector<int> &arr, int n) {
    if (arr.size() < n) {
        throw "n out of array size";
    }
    
    priority_queue<int> heap;
    
    for (auto v : arr) {
        if (heap.size() == n) {
            if (heap.top() > v) heap.pop();
            else continue;
        }
        heap.push(v);
    }
    
    return heap.top();
}

int mostFreq(const vector<int> &arr) {
    unordered_map<int, int> freq;
    for (auto v : arr) {
        if (freq.find(v) == freq.end()) {
            freq[v] = 1;
        }
        else {
            ++freq[v];
        }
    }

    int maxVal = -1;
    int maxFreq = 0;
    for (auto f : freq) {
        if (f.second > maxFreq) {
            maxVal = f.first;
            maxFreq = f.second;
        }
    }

    return maxVal;
}

/* 1) Started this with hash to lookup diff, but then ran into issue with duplicate pairs not getting captures due to map key unquie.
Fixed by adding a list of indexs in map, but code gets complicated and worst case O(n^2) 
2) not sure how to do better. Ok, since issue with lookup in list, make it a set.
*/
vector<pair<int,int>> pairSum(const vector<int> &arr, int sum) {
    unordered_map<int, list<int>> hash;
    for (int i = 0; i < arr.size(); ++i) {
        if (hash.find(arr[i]) == hash.end()) {
            hash[arr[i]] = list<int>{i};
        }
        else {
            hash[arr[i]].push_back(i);
        }
    }
    
    vector<pair<int,int>> pairs;
    for (int i = 1; i < arr.size(); ++i) {
        int diff = sum - arr[i];
        if (hash.find(diff) != hash.end()) {
            bool exists = false;
            auto idxs = hash[diff];
            for (auto idx : idxs) {
                if (i > idx) {
                    exists = true;
                    hash[diff].remove(idx);
                    hash[arr[i]].remove(i);
                    if (hash[diff].empty()) {
                        hash.erase(diff);
                    }
                    if (hash[arr[i]].empty()) {
                        hash.erase(arr[i]);
                    }

                    break;
                }
            }
            
            if (exists)
                pairs.push_back(make_pair(diff, arr[i]));
        }
    }
    
    return pairs;
}

// This one is works better and is more efficient, as just need count/freq per each value to 
// see how many pairs can make
vector<pair<int,int>> pairSumEfficient(const vector<int> &arr, int sum) {
    unordered_map<int, int> freq;
    for (auto v : arr) {
        if (v >= sum) continue; // Skip if to large
        if (freq.find(v) == freq.end()) {
            freq[v] = 0;
        }
        ++freq[v];
    }
    
    vector<pair<int,int>> pairs;
    for (auto &pair : freq) {
        auto a = pair.first;
        auto &aCount = pair.second;
        
        int diff = sum - a;
        if (freq.find(diff) == freq.end()) continue;
        
        auto b = diff;
        auto &bCount = freq[diff];
        //printf("%d: %p %p\n", a, &aCount, &bCount);

        while( (&aCount == &bCount && 1 < aCount) || 
                (&aCount != &bCount && 0 < aCount && 0 < bCount)) {
            pairs.push_back(make_pair(a, b));
            --aCount;
            --bCount;
            //cout << a << ":" << aCount << endl;
        } 
    }
    
    return pairs;
}

/* Given an array of integers, where every element (except 1) appears twice,
find the one element
1) sort inplace O(nlogn) and then search for non-repeating element
2) Brute force O(n^2) search
3) XOR values */
int oneElement(const vector<int> &arr) {
    int missing = 0;
    for (auto v : arr) {
        missing ^= v;
    }
    return missing;
}

int orderStatisticMain() {
    vector<int> arr1{5,6,1,4,12,13,7};
    cout << nthMin(arr1, 7) << endl;
    
    vector<int> arr2{1,5,4,8,4,3,2,9,7,5,3,4};
    cout << mostFreq(arr2) << endl;

    vector<int> arr3{5,1,9,1,9,9,1,5,5};
    auto pairs = pairSum(arr3, 10);
    for (auto p : pairs) {
        cout << p.first << " " << p.second << endl;
    }
    
    vector<int> arr4{1,9,9,1,3,12,12};
    cout << oneElement(arr4) << endl;

    return 0;
}