#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void bsearchish(int N, vector<int> ua, vector<int> ub, vector<int>& ta, vector<int>& tb, int L, int arxh, int telos){
	double x;	int i;
    double mina=1000000000, minai=0;
    double minb=1000000000, minbi=0;
    
    	if(arxh==telos) {
    	x=arxh;
    	for(i=0;i<N;i++){
			if(ta[i]!=-1){
				if(ta[i]+x/ua[i]<=mina){
					mina=ta[i]+x/ua[i];
					minai=i;
				}
		}
			if(tb[i]!=-1){
				if(tb[i]+(L-x)/ub[i]<minb){
	                minb=tb[i]+(L-x)/ub[i];
	                minbi=i;
	            }
	        }
		}
		ta[minai]=-1;
		tb[minbi]=-1;
		cout << minai+1 << ' ' << minbi+1 << endl;
		return;
	}

	else if(telos-arxh<2){
		x=arxh;
		for(i=0;i<N;i++){
			if(ta[i]!=-1){
				if(ta[i]+x/ua[i]<=mina){
					mina=ta[i]+x/ua[i];
					minai=i;
				}
		}
			if(tb[i]!=-1){
				if(tb[i]+(L-x)/ub[i]<minb){
	                minb=tb[i]+(L-x)/ub[i];
	                minbi=i;
	            }
	        }
		}

		if (mina<=minb) {
			ta[minai]=-1;
			tb[minbi]=-1;
			cout << minai+1 << ' ' << minbi+1 << endl;
			return;
		}
		else bsearchish(N,ua,ub,ta,tb,L,telos,telos);
	}


    
	else{
		x = floor((arxh+telos)/2);
		for(i=0;i<N;i++){
			if(ta[i]!=-1){
			if(ta[i]+x/ua[i]<=mina){
				mina=ta[i]+x/ua[i];
				minai=i;
			}
		}
		if(tb[i]!=-1){

			if(tb[i]+(L-x)/ub[i]<minb){
                minb=tb[i]+(L-x)/ub[i];
                minbi=i;
            	}
        	}
		}

		if(mina==minb){
			ta[minai]=-1;
			tb[minbi]=-1;
			cout << minai+1 << ' ' << minbi+1 << endl;
			return;
		}
		//else if(minb-mina==1) {cout << "GOTCHA "; bsearchish(N,ua,ub,ta,tb,L,x,telos);}
		else if (mina<minb) bsearchish(N,ua,ub,ta,tb,L,x,telos);
		//else if(mina-minb==1) {cout << "GOTCHA*2 "; bsearchish(N,ua,ub,ta,tb,L,arxh,x);}
		else bsearchish(N,ua,ub,ta,tb,L,arxh,x);
	}

}


int main(){
	ios_base::sync_with_stdio(false);
	int i,N,L,K;
	cin >> N >> L >> K;
    vector<int> ta(N),tb(N),ua(N),ub(N);
	for (i=0;i<N;i++){
		cin >> ta[i] >> ua[i];
	}
	for (i=0;i<N;i++){
                cin >> tb[i] >> ub[i];
        }

	for (i=0;i<K;i++){
		bsearchish(N,ua,ub,ta,tb,L,0,L);
	}	

}

