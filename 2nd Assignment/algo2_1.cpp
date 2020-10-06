#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack> 
#include <cmath> 


using namespace std;

vector<int> food;
vector<long long int> sum;
vector<long long int> C;

int main(){
	ios_base::sync_with_stdio(false);
	int N, a, k;
	long long int b, c;
	cin >> N >> a >> b >> c;

	for(int i=0;i<N;i++){
		cin >> k;
		food.push_back(k);
	}
	
	sum.push_back(food[0]);
	
	for(int i=1;i<=N;i++)
		sum.push_back(sum[i-1]+food[i]);


	for(int i=0;i<N;i++){
		
		C.push_back(a*sum[i]*sum[i]+b*sum[i]+c);
		for(int j=0;j<i;j++){

			long long int smth=C[j]+a*(sum[i]-sum[j])*(sum[i]-sum[j])+b*(sum[i]-sum[j])+c;
			if(smth>C[i])
				C[i]=smth;
		}
	}
	cout << C[N-1] << '\n';
}