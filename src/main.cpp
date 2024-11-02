#include "yyc_algorithm.h"
#include "bt_algorithm.h"
#include "basic_matrix.h"
#include <iomanip>

using namespace std;

//Function to create user-input Matrix
vector<vector<int>> userMatrix() {

    int rowNum;
    int columnNum;
    
    cout << "Number of columns of the matrix: ";
    cin >> columnNum;

    cout << "Number of rows of the matrix: ";
    cin >> rowNum;

    vector<vector<int>> DM(rowNum, vector<int>(columnNum));
    
    cout << endl << "Please enter each row as a string of ONLY 1's and 0's (NO spaces): " << endl;

    string rowInput;
    for(int i = 0; i < rowNum; i++) {
        cout << "Row " << i+1 << ": ";
        cin >> rowInput;

        if(rowInput.size() != columnNum) {
            cout << "Invalid input length. Please enter exactly " << columnNum << " columns" << endl;
            i--;
            continue;
        }

        for(int j = 0; j < columnNum; j++) {
            DM[i][j] = (rowInput[j] == '1') ? 1 : 0;
        }

    }

    return DM;

}

// Function to print a matrix in desired format
void printMatrix(const vector<vector<int>>& matrix) {

    cout << setw(4);
    for(int i = 0; i < matrix[0].size(); i++) cout << "x_" << i + 1 << " ";
    cout << endl;

    for (const auto& row : matrix) {
        for (int val : row) cout << setw(4) << val;
        cout << endl;
    }
    cout << endl;
}

int main() {

    int menu;
    cout << "Welcome to the typical testor calculator! Please select an option: " << endl << endl;

    cout << "1.) Input a new matrix\n"
         << "2.) Use test matrix\n";

    cin >> menu;
    cout << endl;

    vector<vector<int>> DM;

    if(menu == 1) DM = userMatrix(); 

    else if(menu == 2) {
        // Test Matrix
        DM = {
        {0, 0, 1, 0, 0},
        {1, 1, 0, 0, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 0}
        };
    }
    
    else{
        cout << "Please enter a valid option" << endl;
        return -1;
    }

    cout << "Difference Matrix Introduced: " << endl << endl;

    printMatrix(DM);

    vector<vector<int>> BM = reduceMatrix(DM);

    cout << "Reduced Basic Matrix: " << endl << endl;

    printMatrix(BM);

    set<vector<int>> typicalTestors;
    cout << "Which algorithm would you like to use to find the typical testors?" << endl;

    cout << "1.) YYC Algorithm\n"
         << "2.) BT Algorithm\n";
    

    cin >> menu;
    cout << endl;

    if(menu == 1) typicalTestors = yycAlgorithm(BM);

    else if(menu == 2) typicalTestors = btAlgorithm(BM);

    else{
        cout << "Please enter a valid option";
        return -1;
    }

    cout << "Typical Testors found:" << endl;

    int i = 0;
    for (const auto& testor : typicalTestors) {
        cout << "Testor " << i+1 << ": ";
        for (int column : testor) cout << "x_" << column + 1 << " ";
        cout << endl;
        i++;
    }
    return 0;

}
