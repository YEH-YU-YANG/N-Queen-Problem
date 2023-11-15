#include<bits/stdc++.h>
using namespace std;

class GeneticAlgorithm{
private:
    int N; // N*N = size of board
    int max_generation;
    int size_of_population;
    int mutation_probabiity;
public:
    pair<vector<int>,int> solution;

    GeneticAlgorithm(int N,int max_generation,int size_of_population,int mutation_probabiity);
    void GeneticAlgorithmMethod();
    void generate_initial_individule(vector<pair<vector<int>,int>>& population);
    vector<int> selection(vector<pair<vector<int>,int>>& population);
    void calculate_fitness_for_each_state(vector<pair<vector<int>,int>>& population);
    void find_best_individule(vector<pair<vector<int>,int>>& population,pair<vector<int>,int>& best_state,pair<vector<int>,int>& secon_best_state);
    int fitness(vector<int>& state);
    vector<int> cross_over(vector<int>& father,vector<int>& mother);
    void mutation(vector<int>& state);
    void print_best_individule(pair<vector<int>,int> best_individule){
        cout << "Best individule: " ;
        cout << "[ ";
        for(auto i:best_individule.first){
            cout << i << ' ';
        }
        cout << "]" << endl;
    }
};

GeneticAlgorithm::GeneticAlgorithm(int N,int max_generation,int size_of_population,int mutation_probabiity){
    this->N = N;
    this->max_generation=max_generation;
    this->size_of_population=size_of_population;
    this->mutation_probabiity=mutation_probabiity;
}


void GeneticAlgorithm::GeneticAlgorithmMethod(){

    vector<pair<vector<int>,int>> population;
    generate_initial_individule(population);
 
    for(int i=0;i<max_generation;i++){

        calculate_fitness_for_each_state(population);
        pair<vector<int>,int> best_individule;
        pair<vector<int>,int> second_best_individule;

        find_best_individule(population,best_individule,second_best_individule);
        
        vector<pair<vector<int>,int>> new_population;
        new_population.push_back(best_individule);
        new_population.push_back(second_best_individule);

        while(new_population.size() < size_of_population){
            
            vector<int> father = selection(new_population);
            vector<int> mother = selection(new_population);
            vector<int> child = cross_over(father,mother);
            
            int mp = rand()%100 + 1; // 1 <= mp <= 100
            if(mp<mutation_probabiity){
                mutation(child);
            }
            int child_fitness = fitness(child);
            new_population.push_back( {child,child_fitness} );
        }

        population = new_population;
    
        find_best_individule(population,solution,second_best_individule);
        
    }
}

void GeneticAlgorithm::generate_initial_individule(vector<pair<vector<int>,int>>& population){
    
    int size_of_initial_individule = 5;

    for(int T=0;T<size_of_initial_individule;T++){
        vector<int> individule;
        for(int i=0;i<N;i++){
            individule.push_back(i);
        }

        int swap_times=20;
        for (int i=0;i<swap_times;i++) {
            int x = rand() % N; 
            int y = rand() % N; 
            std::swap(individule[x], individule[y]); 
        }
        population.push_back({individule,0});
    }

   
}


void GeneticAlgorithm::calculate_fitness_for_each_state(vector<pair<vector<int>,int>>& population){
    for(int i=0;i<population.size();i++){
        int fit = fitness(population[i].first);
        population[i].second = fit;
    }   
}

void GeneticAlgorithm::find_best_individule(
    vector<pair<vector<int>,int>>& population,
    pair<vector<int>,int>& best_state,
    pair<vector<int>,int>& second_best_state
){
    
    vector<int> max1;
    int min_attack_nums=INT32_MAX;
    
    vector<int> max2;
    int second_min_attack_nums = INT32_MAX;

    int size = population.size();
  
    for (int i=0;i<size;i++) {
        if (population[i].second < min_attack_nums) {
           
            max2 = max1;
            second_min_attack_nums = min_attack_nums;

            max1 = population[i].first;
            min_attack_nums = population[i].second;
        } else if (population[i].second < second_min_attack_nums) {
            
            max2 = population[i].first;
            second_min_attack_nums = population[i].second;
        }
    }
    best_state = {max1,min_attack_nums};
    second_best_state = {max2,second_min_attack_nums};
}


vector<int> GeneticAlgorithm::selection(vector<pair<vector<int>,int>>& population){
    vector<int> best_state;
    int min_attack_nums=INT32_MAX;
    int selection_size = 10;
    for(int i=0;i<selection_size;i++){
        int x=rand()%population.size();
        if(population[x].second < min_attack_nums){
            best_state = population[x].first;
            min_attack_nums = population[x].second;
        }
    }
    return best_state;
}


int GeneticAlgorithm::fitness(vector<int>& state){
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

vector<int> GeneticAlgorithm::cross_over(vector<int>& father,vector<int>& mother){
    int swap_point=rand()%N;
    
    vector<int> child;

    for(int i=0;i<swap_point;i++){
        child.push_back(father[i]);
    }
    for(int i=swap_point;i<N;i++){
        child.push_back(mother[i]);
    }

    return child;
}

void GeneticAlgorithm::mutation(vector<int>& state){
    int i=rand()%N;
    int j=rand()%N;
    std::swap(state[i],state[j]);
}

int main(int argc, char* argv[]){
    
    double START,END; START = clock();
    srand(time(0));
    
    //////// file name ////////
    string queen_nums = argv[1];
    string output_file = "GA_" + queen_nums + "_Queens.txt";
    ofstream fout(output_file);
    int N=stoi(queen_nums);
    ///////////////////////////

    int max_generation = 10;
    int size_of_population = 10000;
    int mutation_probabiity = 10;

    GeneticAlgorithm g(N,max_generation,size_of_population,mutation_probabiity);
    g.GeneticAlgorithmMethod();

    if(fout.is_open()){
        fout << "Solution: [ ";
        for(auto i:g.solution.first){
            fout << i << ' ';
        }
        fout << "]" << endl;
        
        END = clock();
        
        fout << "# of Queen attacks: ";
        fout << g.solution.second << endl;
        fout << "----------" << endl;
        fout << "Time Execution: " << (double)(END - START) / CLOCKS_PER_SEC << " second."<< endl;

    }else {
        cerr << "Can't open output file" << endl;
    }
    
    fout.close();
}