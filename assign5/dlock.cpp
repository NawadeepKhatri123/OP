#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

int main(){
	int i ;
	int n;	//number of processes
	int m;  //number of resource types
	vector<vector<int>> MAX;
	vector<vector<int>> AVAILABLE;
	vector<vector<int>> NEED;

	ifstream infile("file.txt"); // open the file
	if (!infile){
		cerr << " error : unable to open file \n";
		return 1;
	}

string line;
   while (getline(infile, line)) { // Read each line
        istringstream iss(line);    // Stream to process the line
        vector<int> maxRow;         // Row for MAX
        vector<int> availableRow;   // Row for AVAILABLE
        int num, count = 0;

        // Read integers and divide into MAX and AVAILABLE
        while (iss >> num) {
            if (count < 3) {
                maxRow.push_back(num); // First 3 numbers to MAX
            } else if (count < 6) {
                availableRow.push_back(num); // Next 3 numbers to AVAILABLE
            }
            count++;
        }

        // Store rows in respective vectors
        if (!maxRow.empty()) MAX.push_back(maxRow);
        if (!availableRow.empty()) AVAILABLE.push_back(availableRow);
    }

    infile.close(); // Close the file

    // Print MAX
    cout << "MAX Matrix:" << endl;
    for (const auto& row : MAX) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }

    // Print AVAILABLE
    cout << "AVAILABLE Matrix:" << endl;
    for (const auto& row : AVAILABLE) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
    NEED.resize(MAX.size(), vector<int>(MAX[0].size()));
    for ( i = 0; i < MAX.size(); i++){
	for ( int j =0; j < MAX[i].size();j++){
		NEED[i][j] = MAX[i][j] - AVAILABLE[i][j];

	}

    } 


    return 0;


}

