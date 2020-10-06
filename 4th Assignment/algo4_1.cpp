#include <cstdio>
#include <vector>
#include <iostream>
#include <list> 
#include <stack> 
#include <map>
#include <stdio.h> 
#include <limits.h> 

using namespace std;

#define N2 100
#define K2 10
int result[N2][N2][11];
// A utility function to find the vertex with minimum distance value, from 
// the set of vertices not yet included in shortest path tree 
int minDistance(int dist[], bool sptSet[], int V) { 
   // Initialize min value 
   int min = INT_MAX, min_index; 
   
   for (int v = 0; v < V; v++) 
     if (sptSet[v] == false && dist[v] <= min) 
         min = dist[v], min_index = v; 
   
   return min_index; 
} 
   
// A utility function to print the constructed distance array 
int printSolution(int dist[], int n, int V, int src) { 
   for (int i = 0; i < V; i++) {
      result[src][i][0] = dist[i]; 
      //cout << dist[i];
   }
} 
   
// Function that implements Dijkstra's single source shortest path algorithm 
// for a graph represented using adjacency matrix representation 
void dijkstra(int V, int graph[N2][N2], int src) 
{ 
     int dist[V];     // The output array.  dist[i] will hold the shortest 
                      // distance from src to i 
   
     bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest 
                     // path tree or shortest distance from src to i is finalized 
   
     // Initialize all distances as INFINITE and stpSet[] as false 
     for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX, sptSet[i] = false; 
   
     // Distance of source vertex from itself is always 0 
     dist[src] = 0; 
   
     // Find shortest path for all vertices 
     for (int count = 0; count < V-1; count++) { 
       // Pick the minimum distance vertex from the set of vertices not 
       // yet processed. u is always equal to src in the first iteration. 
       int u = minDistance(dist, sptSet, V); 
   
       // Mark the picked vertex as processed 
       sptSet[u] = true; 
   
       // Update dist value of the adjacent vertices of the picked vertex. 
       for (int v = 0; v < V; v++) 
   
         // Update dist[v] only if is not in sptSet, there is an edge from  
         // u to v, and total weight of path from src to  v through u is  
         // smaller than current value of dist[v] 
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v]) 
            dist[v] = dist[u] + graph[u][v]; 
     } 
   
     // print the constructed distance array 
     printSolution(dist, V, V, src); 
} 


//----------------------------------------------------------------------------------


int main(){
    ios_base::sync_with_stdio(false);
    int N, M, K, Q, i, j;
    cin >> N >> M >> K >> Q;

    int graph[N2][N2], invertedgraph[N2][N2];
    for (i=0;i<N;i++){
        for (j=0;j<N;j++){
            graph[i][j]=0;
            invertedgraph[i][j]=0;
        }
    }



    for (i=0;i<M;i++){
        int u,v,w;
        cin >> u >> v >> w;
        graph[u-1][v-1]= w;
        invertedgraph[v-1][u-1] = w;
    }
    for(i=0; i< N; i++){
        dijkstra(N, graph, i);
    }

    for(int k=1;k<=K;k++){
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                int mind = result[i][j][k-1];
                for(int l=0;l<N;l++){
                    if (invertedgraph[i][l]!=0 && result[l][j][k-1]!=INT_MAX){
                        if(mind > invertedgraph[i][l] + result[l][j][k-1]) mind = invertedgraph[i][l] + result[l][j][k-1];
                    }
                }
                result[i][j][k] = mind;
            }
        }
        for(int kkk=0;kkk<N;kkk++){
            for(i=0;i<N;i++){
                for(j=0;j<N;j++){
                    int mind = result[i][j][k];
                    for(int l=0;l<N;l++){
                        if (graph[i][l]!=0 && result[l][j][k]!=INT_MAX){
                            if(mind > graph[i][l] + result[l][j][k]) mind = graph[i][l] + result[l][j][k];
                        }
                    }
                    result[i][j][k] = mind;
                }
            }
        }

    }    

    for (i=0;i<Q;i++){
        int u, v, p;
        cin >> u >> v >> p;
        if (result[u-1][v-1][p]!=INT_MAX) cout << result[u-1][v-1][p] << endl;
        else cout << "IMPOSSIBLE" << endl;
    }
    /*for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            cout << result[i][j][0] << " ";
        }
        cout << endl;
    }*/

    return 0;
}

