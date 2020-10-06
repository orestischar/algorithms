#include <cstdio>  
#include <vector>  
#include <iostream>  
#include <algorithm>  
#include <stack>   
#include <cmath>   
  
  
using namespace std;  
const int MAXN = 1000005;  

long long int food[MAXN], sum[MAXN], C[MAXN];  
  
vector <long long> bob, susan;  
int current = 0;  


    void setcurrent(long long x) {  
    if (current > (int) bob.size() - 1)  
        current = (int) bob.size() - 1;  

    while (current < (int) bob.size() - 1 && (bob[current + 1] * x + susan[current + 1] >= bob[current] * x + susan[current]))  
        current++;  
} 

void updatelines(long long int m, long long int b) {  
    while ( (int) bob.size() >= 2 && ((susan[susan.size() - 2] - b) * (bob[bob.size() - 1] - bob[bob.size() - 2]) < (susan[susan.size() - 2] - susan[susan.size() - 1]) * (m - bob[bob.size() - 2]) ) ){  
        bob.pop_back(); 
        susan.pop_back();  
    }  
    bob.push_back(m); 
    susan.push_back(b);  
}  

  
int main(){  
	ios_base::sync_with_stdio(false);
    int N, a, k;  
    long long int b, c;  
    cin >> N >> a >> b >> c;  
  
    for(int i=0;i<N;i++){  
        cin >> k;  
        food[i]=k;  
    }  
             
    for(int i=0;i<N;i++)  
        sum[i]=(sum[i-1]+food[i]);  

    C[0]=(a*sum[0]*sum[0]+b*sum[0]+c);  
    updatelines(0,0);  

    //recursion: C[i] = a*S^2[i] + bS[i] +c + max{(C[j]+aS^2[j]-bS[j]-2aS[j]S[i])}
    //if a=-2aS[j], b=C[j]+aS^2[j]-bS[j], y=C[i], x=S[i]
    //do the Convex Hull Trick
  
    for(int i=0;i<N;i++){  
        setcurrent(sum[i]);  
        C[i]=(a*sum[i]*sum[i] + b*sum[i] + c + bob[current]*sum[i] + susan[current]);  
        updatelines(-2*a*sum[i], C[i] + a*sum[i]*sum[i] - b * sum[i]);  
    }  
    //for(int i=0;i<=N;i++)  
    cout << C[N-1] << '\n';  
    return 0;  
}