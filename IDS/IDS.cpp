/*

[Compile .cpp]
g++ IDS.cpp -o IDS.exe

[Execute .exe with argument]
IDS.exe 8   八皇后
IDS.exe 50  五十皇后

*/
#include<bits/stdc++.h> 
using namespace std; 
using namespace std::chrono;

#define NOT_FOUND 999
class Graph { 
private:
	int N; // No. of row,col 
    int MAX_DEPTH;
	vector<vector<int>> board;
public: 
    vector<int> solution;
	Graph(int N,int MAX_DEPTH); 
	bool IDS(int row); 
    bool find_a_sol();
	bool DLS(int limit,int row); 
    int queens_attack_num(int row,int col);
    int queen_attack_nums(vector<int>& state);
}; 

Graph::Graph(int N,int MAX_DEPTH) { 
	this->N = N; 
    this->MAX_DEPTH = MAX_DEPTH;
    this->board = vector<vector<int>>(N, vector<int>(N, 0));
    this->solution = vector<int>(N,NOT_FOUND);
} 
bool Graph::find_a_sol() { 
	for(int i=0;i<N;i++){
        if(solution[i]==NOT_FOUND) return false;
    }
    return true;
} 
int Graph::queen_attack_nums(vector<int>& state){
    int size = state.size();
    int attack_nums=0;
    for(int i=0;i<size;i++){
        for(int j=i+1;j<size;j++){
            if(state[i]==state[j] || abs(state[i]-state[j])==abs(i-j))
                attack_nums++;
        }
    }
    return attack_nums;
}   
int Graph::queens_attack_num(int row,int col){

     int attack_nums = 0;

    for (int i = 0; i < N; i++) {
        if (i != col && board[row][i] == 1) {
            attack_nums++;
        }
    }

    for (int i = 0; i < N; i++) {
        if (i != row && board[i][col] == 1) {
            attack_nums++;
        }
    }

    
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            attack_nums++;
        }
    }
    for (int i = row + 1, j = col + 1; i < N && j < N; i++, j++) {
        if (board[i][j] == 1) {
            attack_nums++;
        }
    }

   
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 1) {
            attack_nums++;
        }
    }
    for (int i = row + 1, j = col - 1; i < N && j >= 0; i++, j--) {
        if (board[i][j] == 1) {
            attack_nums++;
        }
    }

    return attack_nums;
}
bool Graph::DLS(int limit,int row) { 
	if (limit==0 && find_a_sol()) 
		return true; 

	if (limit <= 0) 
		return false; 

    for (int col = 0; col < N; col++) {
        if(queens_attack_num(row,col)==0){
            board[row][col] = 1;
            solution[row] = col; 
            if(DLS(limit-1,row+1)){
                return true;
            }
            board[row][col] = 0;
            solution[row] = NOT_FOUND;
        }
    }
    return false;
} 

bool Graph::IDS(int row=0) { 
	for (int i = 0; i <= MAX_DEPTH; i++) {
        cout << "Depth: " << i << endl;
        if (DLS(i,row) == true) 
    		return true; 
    }
	return false; 
} 

// Driver code 
int main(int argc, char* argv[]) { 

    double START,END; START = clock();

    //////// file name ////////
    string queen_nums = argv[1];
    string output_file = "IDS_" + queen_nums + "_Queens.txt";
    ofstream fout(output_file);
    int board_size = std::stoi(queen_nums);
	int max_depth = std::stoi(queen_nums); 
	///////////////////////////
    
    Graph g(board_size,max_depth); 

	
    
    if(fout.is_open()){
        if(g.IDS(0)){
            
            fout << "Solution: [ ";
            for(auto i:g.solution){
                fout << i << ' ';
            }
            fout << "]" << endl;

            fout << "# of Queen attacks: ";
            fout << g.queen_attack_nums(g.solution) << endl;
            fout << "----------" << endl;

            END = clock();
            fout << "Time Execution: " << (double)(END - START) / CLOCKS_PER_SEC << " second."<< endl;
    
        }
        
    }
    else {
        cerr << "Can't open output file" << endl;
    }

    fout.close();

	return 0; 
}
