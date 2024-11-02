#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

// Function to check if a subset is a testor. Handles alpha updates
bool isTestor(const vector<vector<int>>& BM, const vector<int>& subset, unsigned int &alpha) {
    
    vector<int> zero_rows; // Stores index of all-zero rows
    unsigned int columnNum = BM[0].size();

    // Iterates over every row in BM. Checks if selected columns have an all-zero row
    for(int row = 0; row < BM.size(); row++) {
        bool allZeros = true;

        for(auto column: subset){
            if(BM[row][column] == 1){
                allZeros =  false;
                break;
            }
        }
        if(allZeros) zero_rows.push_back(row);
    }

    
    if(zero_rows.empty()) {

        // If there are no all-zero rows, applies proposition 1.4

        // Calculates k (the position of the rightmost 1 in alpha)
        int k = columnNum;
        for(int i  = columnNum - 1; i >= 0; i--) {
            if(alpha & (1 << i)) k = columnNum - i;
        }

        //Skips 2^(n-k) positions
        alpha += pow(2, columnNum - k);
        return true;
    }

    else {

        // If there are all-zero rows, applies proposition 1.5

        // Calculates k (the position of the last 1 in the all-zero row)
        // If there are multiple all-zero rows, takes the leftmost 1
        int k = columnNum - 1;
        for(auto row: zero_rows){
            int tempK = columnNum - 1;
            for(int column = 0; column < columnNum; column++) {
                if(BM[row][column] == 1) tempK = column; 
            }

            if(tempK < k) k = tempK;
        }
        
        // All positions before k are kept the same
        bitset<32> new_alpha(alpha);
        
        // Position k is set to 1
        new_alpha.set( (columnNum - 1) - k, true);


        // All positions after k are set to zero
        for(int i = 0; i < (columnNum - 1) - k; i++) {
            new_alpha.set(i, false);
        }

        alpha = new_alpha.to_ulong();
        return false;
    }
}

// Main BT algorithm function
set<vector<int>> btAlgorithm(const vector<vector<int>>& BM) {
    set<vector<int>> typicalTestors; // Output set of typical testors
    int columnNum = BM[0].size();

    unsigned int alpha = 1; // Start from (0...01)

    while (alpha < (1u << columnNum)) { 
        vector<int> subset;

        // Translates bits into column index
        for (int j = 0; j < columnNum; j++) {
            if (alpha & (1u << j)) subset.push_back(columnNum - 1 - j);
        }

        // Check if the subset is a testor
        if (isTestor(BM, subset, alpha)) {

            // Check if the new testor is a superset of any testor already stored
            bool isTypical = true;

            // Iterates over every testor stored
            for (const auto& testor : typicalTestors) {
                bool isSuperSet = true;
                for (int column : testor) {

                    // If any element in the typical testor is different to the new testor, the new testor is not a superset
                    if (find(subset.begin(), subset.end(), column) == subset.end()) {
                        isSuperSet = false;
                        break;
                    }
                }
                if (isSuperSet) {
                    isTypical = false;
                    break;
                }
            }
            if (isTypical) typicalTestors.insert(subset); // Store typical testor
        }
    }

    return typicalTestors;
}
