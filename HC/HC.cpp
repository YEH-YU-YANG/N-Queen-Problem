#include<bits/stdc++.h>
using namespace std;


class HillClimbing{
private:
    
    int N; // N*N = size of board
    int max_iterations;

    vector<int> initial_state;
    vector<int> neighbor;
   
public:
    vector<int> solution;
    HillClimbing(int n,int its){
        this->N = n;
        this->max_iterations = its;
        
        for(int i=0;i<n;i++){
            initial_state.push_back(i);
        }

        int swap_times=100;
        for (int i=0;i<swap_times;i++) {
            int x = rand() % N; 
            int y = rand() % N; 
            std::swap(initial_state[x], initial_state[y]); 
        }

        for(int i=0;i<n;i++){
            neighbor.push_back(0);
        }
        
    }

    void HillClimbingMethod(){
        vector<int> current_state(initial_state);
        for(int i=0;i<max_iterations;i++){
            neighbor = generate_random_neighbor(current_state);
            int neighbor_queens_attack_nums = queen_attack_nums(neighbor);
            int current_queens_attack_nums = queen_attack_nums(current_state);
            if(neighbor_queens_attack_nums < current_queens_attack_nums){
                current_state = neighbor;
            }
        }
        for(int i=0;i<N;i++) solution.push_back(current_state[i]);
    }
 // print_state(current_state,i);
    vector<int> generate_random_neighbor(vector<int>& state){
        
        int src = rand()%N;
        int des = rand()%N;

        vector<int> copy_state(state);
        std::swap(copy_state[src],copy_state[des]);

        return copy_state;
    }

    int queen_attack_nums(vector<int>& state){
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

    void print_state(vector<int>& state,int iteration){
        cout << "Iteration: " << iteration ;
        cout << ", state = [ ";
        for(auto i:neighbor){
            cout << i << ' ';
        }
        cout << "]" << endl;
    }
};

int main(int argc, char* argv[]){
    
    double START,END; START = clock();
    srand(time(0));
    
    
    string queen_nums = argv[1];
    string output_file = "HC_" + queen_nums + "_Queens.txt";

    ofstream fout(output_file);
    int N=stoi(queen_nums);

    int max_iterations = 1e4;
    HillClimbing g(N,max_iterations);
    g.HillClimbingMethod();

    if(fout.is_open()){
        fout << "Solution: [ ";
        for(auto i:g.solution){
            fout << i << ' ';
        }
        fout << "]" << endl;
        
        END = clock();
        
        fout << "# of Queen attacks: ";
        fout << g.queen_attack_nums(g.solution) << endl;
        fout << "----------" << endl;
        fout << "Time Execution: " << (double)(END - START) / CLOCKS_PER_SEC << " second."<< endl;
        
    }else {
        cerr << "Can't open output file" << endl;
    }
    
    fout.close();
}