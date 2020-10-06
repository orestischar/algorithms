#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack> 
#include <map>
#include <list> 

using namespace std;

int yaas;
int hellnah;
int maybe;
map<pair<int,int>,int> freq;

struct Edge { 
    int src, dest, weight;
    bool lame=false; 
}; 

struct Graph { 
    int V, E; 
    struct Edge* edge; 
}; 
  
struct Graph* createGraph(int V, int E) { 
    struct Graph* graph = new Graph; 
    graph->V = V; 
    graph->E = E; 
  
    graph->edge = new Edge[E]; 
  
    return graph; 
} 
  
struct subset { 
    int parent; 
    int rank; 
}; 
  
int find(struct subset subsets[], int i) { 
    if (subsets[i].parent != i) 
        subsets[i].parent = find(subsets, subsets[i].parent); 
  
    return subsets[i].parent; 
} 
  
void Union(struct subset subsets[], int x, int y) { 
    int xroot = find(subsets, x); 
    int yroot = find(subsets, y); 
  
 
    if (subsets[xroot].rank < subsets[yroot].rank) 
        subsets[xroot].parent = yroot; 
    else if (subsets[xroot].rank > subsets[yroot].rank) 
        subsets[yroot].parent = xroot; 
  
    else { 
        subsets[yroot].parent = xroot; 
        subsets[xroot].rank++; 
    } 
} 
  
int myComp(const void* a, const void* b) { 
    struct Edge* a1 = (struct Edge*)a; 
    struct Edge* b1 = (struct Edge*)b; 
    return a1->weight - b1->weight; 
} 

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

int bridges=0;

class FindThoseHoes{
	int V;
	list<int> *adj;
	void bridgeUtil (int v, bool visited[], int disc[], int low[], int parent[]); 
	public: 
    FindThoseHoes(int V);   
    void addEdge(int v, int w);   
    void bridge();    
};
FindThoseHoes::FindThoseHoes(int V) { 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void FindThoseHoes::addEdge(int v, int w) { 
    adj[v].push_back(w); 
    adj[w].push_back(v); 
} 

void FindThoseHoes::bridgeUtil(int u, bool visited[], int disc[], int low[], int parent[]) {
	static int time = 0;
	visited[u]=true;
	disc[u] = low[u] = ++time; 

	list<int>::iterator i; 
    for (i = adj[u].begin(); i != adj[u].end(); ++i)  { 
        int v = *i;  // v is current adjacent of u 
  
        if (!visited[v]) { 
            parent[v] = u; 
            bridgeUtil(v, visited, disc, low, parent); 
            low[u]  = min(low[u], low[v]); 

            if (low[v] > disc[u] && freq[make_pair(u,v)]==1) 
              bridges++; 
        } 
  
        // update low value of u
        else if (v != parent[u]) 
            low[u]  = min(low[u], disc[v]); 
    } 
}

void FindThoseHoes::bridge() { 
    bool *visited = new bool[V]; 
    int *disc = new int[V]; 
    int *low = new int[V]; 
    int *parent = new int[V]; 
  
    for (int u = 0; u < V; u++) { 
    	//cout << "here it goes" << endl;
        adj[u].sort();
    }
    


    for (int i = 0; i < V; i++) { 
        parent[i] = -1; 
        visited[i] = false; 
    } 

    for (int i = 0; i < V; i++) 
        if (visited[i] == false) 
            bridgeUtil(i, visited, disc, low, parent); 
} 

//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------

void sup_with_all_these_MSTs_yaaaaall (struct Graph* graph){
	int V = graph->V;
	int E = graph->E;

    int i = 0; 

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

	struct subset *subsets = new struct subset [V * sizeof(struct subset) ]; 

 	for (int v = 1; v <= V; ++v) { 
        subsets[v].parent = v; 
        subsets[v].rank = 0; 
    }    

    while(i<E){
    	int j;
    	j=i;
    	int num=0, hellnah2=0;

    	while (true) {
    		struct Edge next_edge;
    		next_edge = graph->edge[i];
    		num++;
    		int x = find(subsets, next_edge.src);
    		int y = find(subsets, next_edge.dest);

    		if(x==y) {
    			hellnah2++;
    			graph->edge[i].lame=true;
    		}
    		i++;
    		if (graph->edge[i].weight != next_edge.weight || i==E) break;
    	}
  ///////////////////////////////////////////////////////////////////////

    	bridges=0;
    	
    	vector<int> thevertices;
    	for(int k=j;k<i;k++){
    		if (graph->edge[k].lame==false) {
    		    thevertices.push_back(find(subsets, graph->edge[k].src));
    		    thevertices.push_back(find(subsets,graph->edge[k].dest));
    		}
    	}
    	if (thevertices.size()>0){
    	    	sort(thevertices.begin(), thevertices.end());

    	    	map<int, int> vsv;
    	    	
    	    	vsv.insert(pair<int, int>(thevertices[0],0));
    	    	pair <int, int> pp, pp2;
    	    	pp = make_pair(thevertices[0],0);
                pp2 = make_pair(0, thevertices[0]);
                if (freq.find(pp) != freq.end()) freq[pp]++;
             	else freq[pp] = 1;
                if (freq.find(pp2) != freq.end()) freq[pp2]++;
                else freq[pp2] = 1;

    	    	int number=1;
    	
    	    	for(int k=1;k<thevertices.size();k++){
    	    		if(thevertices[k]!=thevertices[k-1]) {
    	    			vsv.insert(pair<int, int>(thevertices[k],number));
    	    			number++;
    	    		}
    	    	}
    	
    	    	FindThoseHoes graf(number);

    	    	freq.clear();

    	    	for(int k=j;k<i;k++){
    	    		if (graph->edge[k].lame==false){
    	    			int x=(vsv.find(find(subsets,graph->edge[k].src))->second), y=(vsv.find(find(subsets,graph->edge[k].dest))->second);
    	    			pair <int, int> p, p2;
    	    			p = make_pair(x,y);
                		p2 = make_pair(y,x);
                		if (freq.find(p) != freq.end()) freq[p]++;
             		    else freq[p] = 1;
                		if (freq.find(p2) != freq.end()) freq[p2]++;
                		else freq[p2] = 1;


    	    			graf.addEdge(x,y);
    	    		}
    	    	}
    	
    	    	graf.bridge();
    	    }

    	maybe+=num-hellnah2-bridges;
    	yaas+=bridges;
    	hellnah+=hellnah2;

    	for(int k=j;k<i;k++){
    		int x = find(subsets, graph->edge[k].src);
    		int y = find(subsets, graph->edge[k].dest);
    		if (x!=y) Union(subsets,x,y);
    	}
    }
}


int main(){
	ios_base::sync_with_stdio(false);
	int V, E;
	cin >> V >> E;

	struct Graph* graph = createGraph(V, E); 

	for(int i=0; i<E; i++){
		int s, d;
		int w;
		cin >> s >> d >> w;
		graph->edge[i].src=s;
		graph->edge[i].dest=d;
		graph->edge[i].weight=w;
	}

	sup_with_all_these_MSTs_yaaaaall(graph);
	cout << yaas << endl << hellnah << endl << maybe << endl;

	return 0;
}
