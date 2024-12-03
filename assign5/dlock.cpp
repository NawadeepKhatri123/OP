#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

void saftey(vector<vector<int>>& MAX, vector<vector<int>>& ALLOCATION, vector<vector<int>>& NEED, int n, int m, vector<vector<int>>& AVAILABLE){

int main(){
	int i ;
	int n;	//number of processes
	int m;  //number of resource types
	vector<vector<int>> MAX;
	vector<vector<int>> ALLOCATION;
	vector<vector<int>> NEED;
	vector<int> AVAIALBLE;

	ifstream infile("file.txt"); // open the file
	if (!infile){
		cerr << " error : unable to open file \n";
		return 1;
	}

	string line;
    	int lineNumber = 0;

    	// Read each line from the file
    	while (getline(infile, line)) {
        	istringstream iss(line);  // Stream to process the line
        	int num;

        	if (lineNumber < 5) {
            		// For the first 5 lines, store values in MAX
            		vector<int> row;
            		while (iss >> num) {
                		row.push_back(num);
            		}	
            		MAX.push_back(row);  // Add row to MAX
        	} else if (lineNumber == 5) {
            		// The 6th line (after the first 5) goes to p
            		iss >> n;
        	} else if (lineNumber == 6) {
            		// The 7th line goes to n
           	 	iss >> m;
        	}

        	lineNumber++;  // Increment line number
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

    	ALLOCATION.resize(MAX.size(), vector<int>(MAX[0].size(),0));
   	NEED.resize(MAX.size(), vector<int>(MAX[0].size()));
    	for ( i = 0; i < MAX.size(); i++){
		for ( int j =0; j < MAX[i].size();j++){
			NEED[i][j] = MAX[i][j] - ALLOCATION[i][j];

		}

    	} 

    	cout << "Need Matrix:" << endl;
    	for (const auto& row : NEED) {
        	for (int num : row) {
            	cout << num << " ";
       		}
        	cout << endl;
    	}

    	saftey(MAX, ALLOCATION, NEED, n , m, AVAILABLE);
    	return 0;


}

void saftey(vector<vector<int>>& MAX, vector<vector<int>>& ALLOCATION, vector<vector<int>>& NEED, int n, int m, vector<vector<int>>& AVAILABLE){
	
	int p;

	vector<vector<int>> request(1,vector<int>(3));
	cout << " select a process (0 - 4): ";
	cin >> p;
	cout << " enter your request vector ( .. .. .. ) : ";
	cin >> request[p][0] >> request[p][1] >> request[p][2];
	
	vector<int> finish(5,0);
	vector<int> work(3,0);
	for (int i = 0; i < AVAILABLE.size(); i++){
		work[i] = AVAILABLE[i];
	}
	int s = 0;
	int move = 0
	while(true){
		for (int i = 0; i < n; i++){
			if (finish[i] == 0){
				for ( int j = 0; j < m; j++){
					if (NEED[i][j] < work[j]){
						work[j] = work[j] + ALLOCATION[i];
						finish[i]++;
						s++;
					}else{
						break;
					}
				}
			}
			if ( s >= n){
				break;
			}
		}

	}
	cout << " request accepted \n";

}

