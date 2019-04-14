#include "dijkstra.h"
#include <math.h>
#include <stdio.h>
#include <iostream>

struct content{
  int parent;
  float dist;
};
int compFunc(void* lhs, void* rhs){
  if (((content*)lhs)-> dist > ((content*) rhs) -> dist)
  {
    return 1;
  }
  else if (((content*) lhs) -> dist < ((content*) rhs) -> dist){
    return -1;
  }
  else{
    return 0;
  }
}
dijkstra_result* shortestPaths(GraphInfo GI, int s){

	MinPrio* Q = new MinPrio(&compFunc, GI->graph->numVerts());
	MinPrio::handle** h = new MinPrio::handle*[GI->graph->numVerts()];
	int* pred = new int[GI->graph->numVerts()]; //Parent link track array
  	float* d = new float[GI->graph->numVerts()]; //Dist array
	content* def = new content();
	d[s] = 0;
	pred[s] = 0;
	def->dist = 0;
	def->parent = s;

	h[s] = Q->enqueue(def);
	for (int i = 0; i < GI->graph->numVerts(); i++){
		if (i != s){
			d[i] = INFINITY;
		    content* enqueued = new content();
		    enqueued->parent = i;
		    enqueued->dist = d[i];
		    h[i] = Q->enqueue(enqueued);
		}
	}
	for (int i = 0; i < GI->graph->numVerts(); ++i){
		pred[i] = -1;
	}
	while(Q -> nonempty()){
		content* contentable = (content*) (Q -> dequeueMin());
		int v = contentable -> parent;
		h[v] = NULL;
		int* suc = GI->graph->successors(v);
		int sucCount = 0;
		int u = suc[sucCount];
		//contentable->parent = v
		//suc[sucCount] = u, a successor of v
		while(u != -1){
			if ( (d[v] + GI->graph->edge(v, u)) < d[u]){
				d[u] = d[v] + GI->graph->edge(v, u);
				pred[u] = v;
				((content*)(h[u]->content))->dist = d[v] + GI->graph->edge(v, u);
				//call decreased key
				Q->decreasedKey(h[u]);
			}
			sucCount++;
      		u = suc[sucCount];
		}
	}
	dijkstra_result* dr = new dijkstra_result();
	dr->dst = d;
	dr->parent = pred;
	return dr;

}
void printResult(GraphInfo GI, dijkstra_result* dr, int s){
	printf("%s%s\n", "Shortest paths from vertex ", GI->vertnames[s]);
	for (int i = 0; i < GI->graph->numVerts(); i++){
		if (i != s){
			//to B is 9.000000 via E

		    printf("%s%s%s", "  to ", GI->vertnames[i], " is ");
		    if (dr->dst[i] == INFINITY)
		    {
		    	printf("%s\n", "not possible");
		    }
		    else
				printf("%f%s%s\n", dr->dst[i], " via ", GI->vertnames[dr->parent[i]]);
		}
	}
}