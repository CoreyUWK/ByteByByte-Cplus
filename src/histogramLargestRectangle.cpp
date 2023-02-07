/*
 * histogramLargestRectangle.cpp
 *
 *  Created on: 2019-09-04
 *      Author: ckirsch
 */
#include "histogramLargestRectangle.h"
#include <cassert>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

//#define Debug 1

/*
1) brute force O(n*2)
per each spot check left and right to see how long

          | |     
    | |   | |     |
  | | |   | | |   |
  | | |   | | | | |
| | | | _ | | | | |
1 3 4 4 0 5 5 3 2 4

2) using stacks
largest=(4-3)*4=4
value = 0 idx = 4 

 2    4
 1    3 
 0    1
idx  val
*/
int histogramLargestRectangle(const vector<int>& histogram) {
    int largest = 0;
    struct entry {
        int idx;
        int height;
    };
    stack<entry> st;
    for (int i=0; i <= histogram.size(); ++i) {
        int h = (i < histogram.size()) ? histogram[i] : 0;
        if (st.empty() || h > st.top().height) {
            #ifdef Debug
            cout << "Push1: " << i << " " << h << endl;
            #endif 
            st.push(entry{i,h});
        }
        else if (h == st.top().height) {
            #ifdef Debug
            cout << "Not Push: " << i << " " << h << endl;
            #endif
            continue;
        }
        else {
            int lastIdx = st.top().idx;
            while (!st.empty() && st.top().height > h) {
                int size = st.top().height * (i - st.top().idx);
                #ifdef Debug
                cout << "Size:" << size << " " << st.top().height << " " << i << " " << st.top().idx << endl;
                #endif
                if (size > largest) {
                    largest = size;
                    #ifdef Debug
                    cout << "largest:" << largest << endl;
                    #endif
                }
                lastIdx = st.top().idx;
                st.pop();    
            }
            #ifdef Debug
            cout << "Push2: " << lastIdx << " " << h << endl;
            #endif
            st.push({lastIdx, h});
        }
    }
    return largest;
}

void histogramLargestRectangleMain() {
    vector<int> histogram{1,3,4,4,0,5,5,3,2,4};
    cout << histogramLargestRectangle(histogram);
}