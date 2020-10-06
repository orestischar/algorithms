#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack> 

using namespace std;

vector<long int> tail;
vector<long int> bob_increasing(1,1);
vector<long int> bob_decreasing;
vector<long int> v;


int binary1(vector<long int>& v, long int l, long int r, long int key) 
{ 
    while (r - l > 1) { 
        long int m = l + (r - l) / 2; 
        if (v[m] >= key) 
            r = m; 
        else
            l = m; 
    } 
  
    return r; 
} 
  
int LIS(vector<long int>& v) 
{ 
    if (v.size() == 0) 
        return 0; 
  
    vector<long int> tail(v.size(), 0); 
    int length = 1; // always points empty slot in tail 
  
    tail[0] = v[0]; 
    for (int i = 1; i < v.size(); i++) { 
  
        if (v[i] < tail[0]) 
            tail[0] = v[i]; 
  
        else if (v[i] > tail[length - 1]) 
            tail[length++] = v[i]; 
  
        else
            tail[binary1(tail, -1, length - 1, v[i])] = v[i]; 

        bob_increasing.push_back(length);
    } 
  
} 



int binary2(vector<long int>& v, long int l, long int r, long int key) 
{ 
    while (r - l > 1) { 
        long int m = l + (r - l) / 2; 
        if (v[m] <= key) 
            r = m; 
        else
            l = m; 
    } 
  
    return r; 
} 


int LDS(vector<long int>& v) 
{ 
    if (v.size() == 0) 
        return 0; 
    
    vector<long int> tail(v.size(), 0); 
     
    int length = 1; // always points empty slot in tail 
  
    tail[0] = v[v.size()-1]; 
    for (int i = v.size()-1; i >=0; i--) { 
  
        if (v[i] > tail[0]) 
            tail[0] = v[i]; 
  
        else if (v[i] < tail[length - 1]) 
            tail[length++] = v[i]; 

        else
            tail[binary2(tail, -1, length - 1, v[i])] = v[i]; 
        
        bob_decreasing.push_back(length);
    } 
    
  
} 


int main(){
	long int N,k;
	ios_base::sync_with_stdio(false);

	cin >> N;

	for(int i=0;i<N;i++){
		cin >> k;
		v.push_back(k);
	}

	for (int i=0;i<v.size();i++){

		tail.push_back(0);
	}

	LIS(v);

	/*for (int i=0;i<v.size();i++){

		tail[i]=0;
	}*/

	LDS(v);
	
	long int max=1;
	long int bob_size=bob_increasing.size();

	for (int i=1;i<bob_size;i++){

		if(bob_increasing[i-1]+bob_decreasing[bob_size-1-i] > max)
			max = bob_increasing[i-1]+bob_decreasing[bob_size-1-i];
	}
	cout << max << '\n';

}