#include "yyc_algorithm.h"
#include "bt_algorithm.h"
#include <vector>
#include <set>
#include <chrono>
#include <iomanip>
#include <iostream>

using namespace std;

// Function to print a matrix in desired format
void printMatrix(const vector<vector<bool>>& matrix) {
    cout << setw(4);
    for(int i = 0; i < matrix[0].size(); i++) cout << "x_" << i + 1 << " ";
    cout << endl;

    for (const auto& row : matrix) {
        for (int val : row) cout << setw(4) << val;
        cout << endl;
    }
    cout << endl;
}

// Function to 
void printTypicalTestors (const set<vector<int>>& typicalTestors) {
    int i = 0;

    for (const auto& testor : typicalTestors) {
        cout << "Testor " << i+1 << ": ";
        for (int column : testor) 
            cout << "x_" << column + 1 << " ";
        cout << endl;
        i++;
    }
}


// Function to determine the density of a matrix
float matrixDensity(const vector<vector<bool>>& matrix) {
    int numerator = 0;
    int rows = matrix.size();
    int columns =  matrix[0].size();
    int totalElements = rows*columns;

    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[0].size(); j++) {
            if(matrix[i][j]) numerator++;
        }        
    }

    return static_cast<float>(numerator) / totalElements;
} 


// Function to create a boolean matrix representing typical testors
vector<vector<bool>> typicalTestorsMatrix(const set<vector<int>>& typicalTestors) {

    // Calculate columnNum as the maximum index found in any testor + 1
    int columnNum = 0;
    for (const auto& testor : typicalTestors) {
        for (int col : testor) {
            if (col + 1 > columnNum) {
                columnNum = col + 1;
            }
        }
    }

    vector<vector<bool>> newMatrix;

    for (const auto& testor : typicalTestors) {
        vector<bool> row(columnNum, 0); // Start with a row of zeros
        for (int col : testor) {
            row[col] = 1; // Set to 1 if the column is in the testor
        }
        newMatrix.push_back(row);
    }

    return newMatrix;
}


// Function to 
vector<vector<bool>> thetaOperator(const vector<vector<bool>>& A, const vector<vector<bool>>& B){

    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    vector<vector<bool>> AB(rowsA * rowsB, vector<bool>(colsA + colsB));
    
    int rowIndex = 0;
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B.size(); j++) {

            // Insert A[i] elements into resulting row
            for (int k = 0; k < A[0].size(); k++) {
                AB[rowIndex][k] = A[i][k];
            }

            // Insert B[i] elements into resulting row
            for (int k = 0; k < B[0].size(); k++) {
                AB[rowIndex][colsA + k] = B[j][k];
            }

            rowIndex++;
        }
    }

    return AB;
}


// Function to 
vector<vector<bool>> phiOperator(const vector<vector<bool>>& A, int N) {

    if (N < 1) return {};

    int rows = A.size();
    int cols = A[0].size();

    vector<vector<bool>> result(rows, vector<bool>(N * cols));

    for (int i = 0; i < rows; i++) {
        for (int n = 0; n < N; n++) {
            for (int j = 0; j < cols; j++) { 
                result[i][n * cols + j] = A[i][j];
            }
        }
    }

    return result;
}


// Function to 
vector<vector<bool>> gammaOperator(const vector<vector<bool>>& A, int N) {

    if (N < 1) return {};

    int rows = A.size();
    int cols = A[0].size();

    vector<vector<bool>> result(N * rows, vector<bool>(N * cols, 0));

    for (int n = 0; n < N; ++n) {
        int rowOffset = n * rows;  
        int colOffset = n * cols;  

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result[rowOffset + i][colOffset + j] = A[i][j];
            }
        }
    }

    return result;
}


// Function to 
vector<vector<bool>> sortMatrix (const vector<vector<bool>>& matrix) {

    vector<vector<bool>> sortedMatrix;
    vector<bool> used(matrix.size(), false); 

    for (size_t k = 0; k < matrix.size(); k++) {
        int minOnes = 666;
        int minIndex = -1;

        for (size_t i = 0; i < matrix.size(); i++) {
            if (!used[i]) { 
                int onesCount = count(matrix[i].begin(), matrix[i].end(), 1);
                
                if (onesCount < minOnes) {
                    minOnes = onesCount;
                    minIndex = i;
                }
            }
        }

        
        if (minIndex != -1) {
            sortedMatrix.push_back(matrix[minIndex]);
            used[minIndex] = true;
        }
    }

    return sortedMatrix;
}


// Function that returns the number of typical testors in a matrix
int countTypicalTestors(const set<vector<int>>& typicalTestors) {
    return typicalTestors.size();  
}


// Function to
void printExecutionTime(const vector<vector<bool>>& A, const vector<vector<bool>>& sortedA){

    using namespace std::chrono;

    // Get starting timepoint
    auto start_yycA = high_resolution_clock::now();

    // Call the function
    set<vector<int>> A_typicalTestors = yycAlgorithm(A);

    // Get ending timepoint
    auto stop_yycA = high_resolution_clock::now();

    auto duration_yycA = duration_cast<microseconds>(stop_yycA - start_yycA);

    
    // Get starting timepoint
    auto start_yycSortedA = high_resolution_clock::now();

    // Call the function
    yycAlgorithm(sortedA);

    // Get ending timepoint
    auto stop_yycSortedA = high_resolution_clock::now();

    auto duration_yycSortedA = duration_cast<microseconds>(stop_yycSortedA - start_yycSortedA);

    
    // Get starting timepoint
    auto start_btA = high_resolution_clock::now();

    // Call the function
    btAlgorithm(A);

    // Get ending timepoint
    auto stop_btA = high_resolution_clock::now();

    auto duration_btA = duration_cast<microseconds>(stop_btA - start_btA);

    
    // Get starting timepoint
    auto start_btSortedA = high_resolution_clock::now();

    // Call the function
    btAlgorithm(sortedA);

    // Get ending timepoint
    auto stop_btSortedA = high_resolution_clock::now();

    auto duration_btSortedA = duration_cast<microseconds>(stop_btSortedA - start_btSortedA);

    
    cout << setw(6) << countTypicalTestors(A_typicalTestors);

    // Print execution times for each algorithm in miliseconds or seconds
    auto printDuration = [](auto duration) {
        if(duration.count() < 1000000)
            cout << static_cast<double>(duration.count()) / 1000 << " ms";
        else
            cout << static_cast<double>(duration.count()) / 1000000 << "  s";
    };

    cout << setw(9);
    printDuration(duration_yycA);
    cout << setw(12);
    printDuration(duration_yycSortedA);
    cout << setw(9);
    printDuration(duration_btA);
    cout << setw(11);
    printDuration(duration_btSortedA);

    cout<<endl;
}


