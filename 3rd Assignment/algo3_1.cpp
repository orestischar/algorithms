#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack> 
#include <cmath> 


using namespace std;

struct wassup{
	bool start=false, end=false;
	int sx=-1, sy=-1;
};


int main(){
	ios_base::sync_with_stdio(false);
	int N, M, K;
	int X;
	cin >> N >> M >> K >> X;
	//N=N%1000000103;


	long long int dp [N][M][X+1];
	wassup sup [N][M];

	long long int s,e;

	for(int i=0; i<K; i++){
		cin >> s >> e;
		sup[s/M][s%M].start=true;
		sup[e/M][e%M].end=true;
		sup[e/M][e%M].sx=s/M;
		sup[e/M][e%M].sy=s%M;
	}
	
/*	for (long long int x=0; x<=X; x++){
		for (int i=N-1; i>=0; i--){
			for (int j=M-1; j>=0; j--){
				dp[i][j][x]=0;
			}
		}
	}*/

	for (int x=0; x<=X; x++){
		for (int i=N-1; i>=0; i--){
			for (int j=M-1; j>=0; j--){
				if (i==N-1 && j==M-1) dp[i][j][x]=1;
				else if (j==M-1) {
					if (sup[i+1][j].start==true) dp[i][j][x]=0;
					else dp[i][j][x]=dp[i+1][j][x];
				}
				else if (i==N-1) {
					if (sup[i][j+1].start==true) dp[i][j][x]=0;
					else dp[i][j][x]=dp[i][j+1][x];
				}

				else{
					long long int temp=0;
					if (sup[i+1][j].start==false) temp+=dp[i+1][j][x];
					if (sup[i][j+1].start==false) temp+=dp[i][j+1][x];

					if(sup[i][j].end==true && x!=0){
						temp+=dp[sup[i][j].sx][sup[i][j].sy][x-1];
					}
					dp[i][j][x]=temp%1000000103;
				}
			}
		}
	}
/*	cout << endl;
	for (long long int x=0; x<=X; x++){
		for (int i=0; i<N; i++){
			for (int j=0; j<M; j++){
				cout << dp[i][j][x] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}*/

	cout << dp[0][0][X]%1000000103 << endl;
	return 0;
}
