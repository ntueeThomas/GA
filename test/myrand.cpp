#include "myrand.h"
#include "mt19937ar.cpp"
using namespace std;
MyRand::MyRand ()
{
	
	unsigned long init_key[N];
	
	srand((unsigned long) time (NULL));
	
	for(int i = 0; i < N; i++)
		init_key[i] = (unsigned long) time (NULL) * rand ();
	
	init_by_array (init_key, N);
}

MyRand::~MyRand(){
	//cout<<"MyRand destructor called.."<<endl;
	
}

bool MyRand::flip (double prob){
	return (uniform () < prob);
}

/**From [a,b) */
double MyRand::uniform (double a, double b){
	return uniform () * (b - a) + a;
}

/**From [0,1) */
double MyRand::uniform (){
	return genrand_res53 ();
}

/**Int From [a,b] */
int MyRand::uniformInt (int a, int b){
	return (a + (int) (uniform () * (b - a + 1)));
}
/**Generate a random array of size num, from [a,b] */
/** num <= b-a+1 */
void MyRand::uniformArray (vector<int> &array, int num, int a, int b){
	vector<int> base(b - a + 1);
	//int *base = new int[b - a + 1];
	int i;
	int r;
	for(i = 0; i < b - a + 1; i++)
		base.at(i) = a + i;
	
	for (i = 0; i < num; i++){
		r = uniformInt (0, b - a - i);
		array.at(i) = base.at(r);
		base.at(r) = base.at(b - a - i);
	}
	//delete [] base;
}



