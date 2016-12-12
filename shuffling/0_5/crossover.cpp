#include<iostream>
#include<vector>
#include <time.h>
#include <ctime>
#include <cstdlib>
using namespace std;
#define selectionPressure 2


float uniform (){
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);;
}
int uniformInt (int a, int b){
	return (a + (int) (uniform () * (b - a + 1)));
}
void uniformArray (vector<int> &array, int num, int a, int b){
	vector<int> base(b - a + 1);
	int i;
	int r;
	for(i = 0; i < b - a + 1; i++)
		base.at(i) = a + i;
	
	for (i = 0; i < num; i++){
		r = rand()%(b - a - i + 1);
		array.at(i) = base.at(r);
		base.at(r) = base.at(b - a - i);
	}
}
double getFitness(int i, vector<vector<bool> > &A){
	double Fitness = 0;
	for(int j = 0; j < A.at(i).size(); j++){
		
		if(A.at(i).at(j))
			Fitness++;
	}
	return Fitness;
}
double getTotalFitness(vector<double> &F){
	double totalFitness = 0;
	for(int j = 0; j < F.size(); j++){
		totalFitness+=F.at(j);
	}
	return totalFitness;
}
void printAGene(int i, vector<vector<bool> > &A){
	for(int j = 0; j < A.at(i).size(); j++){
		cout<<A.at(i).at(j)<<" ";
	}
	cout<<endl;
}
void uniformCrossover(vector<vector<bool> > &B){
	//cout<<"*********************** uniform crossover *******************"<<endl;
	//vector<int> pair_index(B.size());
	//myRand.uniformArray(pair_index, B.size(), 0, B.size()-1);
	int num = B.size()/2;
	if(B.size()%2 != 0){
		cout<<"error!"<<endl;
		return;
	}
	for(int i = 0; i < num; i++){
		//printAGene(pair_index.at(2*i), B);
		//printAGene(pair_index.at(2*i+1), B);
		bool temp;
		
		
		for(int j = 0; j < B.at(0).size(); j++){
			//cout<<"gene No. "<<j<<endl;
			if(uniform() > 0.5){
				//myRand.flip(0.5)
				//cout<<"order"<<endl;
			}
			else{
				//cout<<"reverse order"<<endl;
				temp = B.at(2*i).at(j);
				B.at(2*i).at(j) = B.at(2*i+1).at(j);
				B.at(2*i+1).at(j) = temp;
				//temp = B.at(pair_index.at(2*i)).at(j);
				//B.at(pair_index.at(2*i)).at(j) = B.at(pair_index.at(2*i+1)).at(j);
				//B.at(pair_index.at(2*i+1)).at(j) = temp;
			}
		}
		//cout<<"****************************************"<<endl;
		//printAGene(pair_index.at(2*i), B);
		//printAGene(pair_index.at(2*i+1), B);
		//cout<<"***************************** END ****************************"<<endl;
	}
}
void onePointCrossover(vector<vector<bool> > &B){
	//cout<<"*********************** onepoint crossover *******************"<<endl;
	//vector<int> pair_index(B.size());
	//myRand.uniformArray(pair_index, B.size(), 0, B.size()-1);
	int num = B.size()/2;
	if(B.size()%2 != 0){
		cout<<"error!"<<endl;
		return;
	}
	
	for(int i = 0; i < num; i++){
		//printAGene(pair_index.at(2*i), B);
		//printAGene(pair_index.at(2*i+1), B);
		bool temp;
		int crossSite = uniformInt(1, B.at(0).size()-1);
		//cout<<"cross point: "<<crossSite<<endl;
		for(int j = crossSite; j < B.at(0).size(); j++){
			temp = B.at(2*i).at(j);
			B.at(2*i).at(j) = B.at(2*i+1).at(j);
			B.at(2*i+1).at(j) = temp;
			//temp = B.at(pair_index.at(2*i)).at(j);
			//B.at(pair_index.at(2*i)).at(j) = B.at(pair_index.at(2*i+1)).at(j);
			//B.at(pair_index.at(2*i+1)).at(j) = temp;
		}
		//cout<<"****************************************"<<endl;
		//printAGene(pair_index.at(2*i), B);
		//printAGene(pair_index.at(2*i+1), B);
		//cout<<"***************************** END ****************************"<<endl;
	}
}
void shufflingCrossover(vector<vector<bool> > &B){
	vector<bool> temp(B.size());
	vector<int> position_index(B.size());
	//cout<<"*********************** shuffling crossover *******************"<<endl;
	for(int i = 0; i < B.at(0).size(); i++){		
		uniformArray(position_index, B.size(), 0, B.size()-1);
		for(int j = 0; j < B.size(); j++){
			temp.at(j) = B.at(position_index.at(j)).at(i);
			//cout<<position_index.at(j)<<" ";
		}
		for(int j = 0; j < B.size(); j++){
			B.at(j).at(i) = temp.at(j);
		}
		//cout<<endl;	
	}
	//cout<<"***************************** END ****************************"<<endl;
}
void tnSelectionWoR(vector<vector<bool> > &A, vector<vector<bool> > &B, vector<double> &F){
	
	if(A.size() != B.size() || A.size() != F.size()){
		cout<<"error!"<<endl;
		return;
	}
	int populationSize = A.size();
	int numTimesARound = populationSize/selectionPressure;
	int numRounds = selectionPressure;
	
	for(int i = 0; i < numRounds; i++){
		//vector<int>competition_index (populationSize);
		
		//uniformArray(competition_index, populationSize, 0, populationSize-1);
		for(int j = 0; j < numTimesARound; j++){
			int candidate_1 = selectionPressure*j;
			int candidate_2 = selectionPressure*j + 1;
			//int candidate_1 = competition_index.at(selectionPressure*j);
			//int candidate_2 = competition_index.at(selectionPressure*j + 1);
			//cout<<"candidate 1: "<<candidate_1<<endl;
			//printAGene(candidate_1, A);
			//cout<<"candidate 2: "<<candidate_2<<endl;
			//printAGene(candidate_2, A);
			if(F.at(candidate_1) > F.at(candidate_2)){
				B.at(i*numTimesARound + j) = A.at(candidate_1);
				//cout<<"winner: candidate 1"<<endl;
			}				
			else{
				B.at(i*numTimesARound + j) = A.at(candidate_2);
				//cout<<"winner: candidate 2"<<endl;
			}
				
		}
	}
}
void replace(vector<vector<bool> > &A, vector<vector<bool> > &B){
	A.swap(B);
}
void evaluate(vector<vector<bool> > &A, vector<double> &F, double &totalFitness){
	totalFitness = 0;
	for(int i = 0; i < A.size(); i++){
		F.at(i) = getFitness(i, A);
		totalFitness += F.at(i);
	}	
}
void printGene(vector<vector<bool> > &A){
	for(int i = 0; i < A.size(); i++){
		for(int j = 0; j < A.at(i).size(); j++){
			cout<<A.at(i).at(j)<<" ";
		}
		cout<<endl;
	}
}



int main(){
	srand (static_cast <unsigned> (time(0)));
	int iarr1[] = {50,100,150,200,250,300,350,400,450,500};
	int iarr2[] = {980,2304,3758,5300,6902,8556,10252,11984,13746,15538};
	vector<vector<bool> > A;
	vector<vector<bool> > B;
	vector<double> F;
	for(int count = 0; count < 6; count++){
	cout<<"count: "<<count<<endl;
	time_t t1, t2;
	t1 = time(NULL);
	int ell = iarr1[count];
	int n = iarr2[count];
	//int ell = 5;
	//int n = 4;	
	A.resize(n);	
	B.resize(n);	
	F.resize(n);
	for(int i = 0; i < n; i++){
		A.at(i).resize(ell);
		B.at(i).resize(ell);
	}	
	double convergence_time = 0;
	for(int c = 0; c < 30; c++){
		cout<<c<<endl;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < ell; j++){
				double p = 0.5;
				if(uniform() > p)
					A.at(i).at(j) = 1;
				else
					A.at(i).at(j) = 0;	
			}
		}
		double preTotalFitness = -1;
		double curTotalFitness = 0;
		double generation = 0;
		
		//cout<<"***************** generation: "<<generation<<" *******************"<<endl;
		evaluate(A, F, curTotalFitness);
		//double maxFitness = F.at(0);
		//printGene(A);
		//cout<<"previous total fitness: "<<preTotalFitness<<endl;
		//cout<<"current total fitness: "<<getTotalFitness(F)<<endl;
		//preTotalFitness != curTotalFitness
		//maxFitness*n > curTotalFitness
		while(preTotalFitness != curTotalFitness){
			generation++;
			preTotalFitness = curTotalFitness;
			//cout<<"***************** generation: "<<generation<<" *******************"<<endl;
			int number = A.size()/2;
			/*
			vector<vector<float> > randM(number);
			for(int p = 0; p < number; p++){
				randM.at(p).resize(ell);
				for(int q = 0; q < ell; q++){
					randM.at(p).at(q) = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				}
			}
			*/
			tnSelectionWoR(A, B, F);
			//tnSelectionWoR(A, B, F, myRand);
			//printGene(B);
			shufflingCrossover(B);
			//uniformCrossover(B);
			//uniformCrossover(B, myRand);
			//onePointCrossover(B);
			replace(A, B);	
			evaluate(A, F, curTotalFitness);
			//if(F.at(0) > maxFitness)
				//maxFitness = F.at(0);
			//printGene(A);
			//cout<<"previous total fitness: "<<preTotalFitness<<endl;
			//cout<<"current total fitness: "<<getTotalFitness(F)<<endl;
			
		}
		convergence_time += generation;
	}
	t2 = time(NULL);
	cout<<"time cost: "<<t2-t1<<" secs"<<endl;
	cout<<convergence_time/30<<endl;
	}
	return 1;
	
}