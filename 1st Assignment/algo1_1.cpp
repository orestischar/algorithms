#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack> 
using namespace std;

struct shit{
	long long int num;
	int count;
};

/*vector<int> food;
vector<long long int> sum;
vector<long long int> C;

for(int i=0;i<N;i++){
	cin >> k;
	food.push_back(k);
}*/

vector<long long int> L, R, F;
stack<shit> bob;



int main(){
	ios_base::sync_with_stdio(false);
	long long int N;
	cin >> N;
	int i, k;
	long long int previous, sum=0;

	for(i=0;i<N;i++){
		cin >> k;
		F.push_back(k);
	}

	shit s;

	previous=F[0];
	for (i=0;i<N;i++){
		if (F[i]<=previous) {
			sum+=F[i];
			L.push_back(sum);
			s.num=F[i];
			s.count=1;
			bob.push(s);
			previous=F[i];
		}
		
		else{
			int counter=1;
			
			while(!bob.empty() && F[i]>bob.top().num){
				//sum-=counter*bob.top();
				counter+=bob.top().count;
				sum-=bob.top().num * bob.top().count;
				//cout << "bobtop " << bob.top() << endl;
				bob.pop();
			}
			//for (int j=0;j<counter;j++) 
			s.num=F[i];
			s.count=counter;
			bob.push(s);
			sum=sum+s.count*F[i];
			L.push_back(sum);
			previous=F[i];
		}
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////

	previous=F[N-1];
	sum=0;
	while(!bob.empty()){
		bob.pop();
	}
	for (i=N-1;i>=0;i--){
		if (F[i]<=previous) {
			sum+=F[i];
			R.push_back(sum);
			s.num=F[i];
			s.count=1;
			bob.push(s);
			previous=F[i];
		}
		
		else{
			int counter=1;
			
			while(!bob.empty() && F[i]>bob.top().num){
				//sum-=counter*bob.top();
				counter+=bob.top().count;
				sum-=bob.top().num * bob.top().count;
				//cout << "bobtop " << bob.top() << endl;
				bob.pop();
			}
			//for (int j=0;j<counter;j++) 
			s.num=F[i];
			s.count=counter;
			bob.push(s);
			sum=sum+s.count*F[i];
			R.push_back(sum);
			previous=F[i];
		}
	}
////////////////////////////////////////////////////////
	long long int min=L[0]+R[N-1]-F[0];
	for (i=1;i<N;i++){
		if(L[i]+R[N-1-i]-F[i]<min) min = L[i]+R[N-1-i]-F[i];
	}

	cout << min << endl;

}
