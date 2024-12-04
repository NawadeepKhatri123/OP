#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

bool saftey(vector<vector<int>>& MAX, vector<vector<int>>& ALLOCATION, vector<vector<int>>& NEED, int n, int m, vector<int>& AVAILABLE );
void Bankers(vector<vector<int>>& MAX, vector<vector<int>>& ALLOCATION, vector<vector<int>>& NEED, int n, int m, vector<int>& AVAILABLE);
void print(vector<vector<int>>& MAX, vector<vector<int>>& ALLOCATION, vector<vector<int>>& NEED, int n, int m, vector<int>& AVAILABLE );
int main(){
	int i ;
	int n;	//number of processes
	int m;  //number of resource types
	vector<vector<int>> MAX;
	vector<vector<int>> ALLOCATION;
	vector<vector<int>> NEED;
	vector<int> AVAILABLE = {10,5,7};

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

    	Bankers(MAX, ALLOCATION, NEED, n , m, AVAILABLE);
    	return 0;


}

void Bankers(vector<vector<int>>& MAX, vector<vector<int>>& ALLOCATION, vector<vector<int>>& NEED, int n, int m, vector<int>& AVAILABLE){
	
	int p;
	vector<int> request(m);	
	bool flag = true;
	while(true){

		cout << " select a process (0 - 4): ";
		cin >> p;
		cout << " enter your request vector ( .. .. .. ) : ";
		cin >> request[0] >> request[1] >> request[2];
		for (int i = 0; i < m; i++){
			if (request[i] > NEED[p][i] || request[i] > AVAILABLE[i]){
				cerr << " error : invalid request\n" << i;
				flag = false;
			}
		}
		if (flag){
		for (int i = 0; i < m; i++){
			AVAILABLE[i] = AVAILABLE[i] - request[i];	
			ALLOCATION[p][i] = ALLOCATION[p][i] + request[i]; 		 
		}}
	
		// change the needs vector
		if (flag){
		for ( int i = 0; i < MAX.size(); i++){
			for ( int j =0; j < MAX[i].size();j++){
				NEED[i][j] = MAX[i][j] - ALLOCATION[i][j];
			}
    		}}
	
		if (flag){
			if (saftey(MAX, ALLOCATION, NEED, n,m,AVAILABLE)){
				cout<<"\n request is safe\n";
			}
		}
	}

}

bool saftey(vector<vector<int>>& MAX, vector<vector<int>>& ALLOCATION, vector<vector<int>>& NEED, int n, int m, vector<int>& AVAILABLE ){

	for (auto i :AVAILABLE){
		cout<<i<<" ";
	}
	cout<<'\n';
	vector<int> finish(n,0);
	vector<int> work(AVAILABLE.size());
	work = AVAILABLE;
	bool safe = true;
	int flag = 1;
	do{
	safe = false;
	for (int i = 0; i < n; i++){
		if ( finish[i] == 0){
			bool canFinish = true;
			for (int j = 0; j < m; j++){
				if (NEED[i][j] > work[j]){
					canFinish = false;
					break;
				}
			}
			if (canFinish){
				for (int j = 0;j < m; j++){
					work[j] = work[j] + ALLOCATION[i][j];
				}
				finish[i] = 1;
				safe = true;
			}
		}
	} 
	} while(safe);

	for (int i = 0; i < n; i++){
		if (finish[i] != 1){
			return false;
		}
	}
	for (auto i :AVAILABLE){
		cout<<i<<" 1";
	}
	cout<<'\n';

	return true;
}

void print(vector<vector<int>>& MAX, vector<vector<int>>& ALLOCATION, vector<vector<int>>& NEED, int n, int m, vector<int>& AVAILABLE ){

	// Print MAX
    	cout << "MAX Matrix:" << endl;
    	for (const auto& row : MAX) {
        	for (int num : row) {
            	cout << num << " ";
        	}
        	cout << endl;
    	}

	cout << "alloc Matrix:" << endl;	
	for (const auto& row : ALLOCATION) {
        	for (int num : row) {
            		cout << num << " ";
       		}
        	cout << endl;
    	}

	cout << "Need Matrix:" << endl;
    	for (const auto& row : NEED) {
        	for (int num : row) {
            		cout << num << " ";
       		}
        	cout << endl;
    	}

	



}
