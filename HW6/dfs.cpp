#include "dfs.h"
#include <stdio.h>
#include <cstdlib>

static int disCount;
static int finCount;

void DFSVisit(int vertex, dfsinfo* d){
  d -> discover[vertex] = disCount;
  disCount++;
  int* s = d -> graph -> successors(vertex);
  int succIndex = 0;
  while (s[succIndex] != -1){ // What if vertex has no more successors (parent of it in particular)
    if (d -> discover[s[succIndex]] == 0){
      d -> parent[s[succIndex]] = vertex;
      DFSVisit(s[succIndex], d);
    }
    
    succIndex++;
  }
  d -> finish[vertex] = finCount;
  finCount++;
}

dfsinfo* DFS(Graph* g){
  dfsinfo* search = new dfsinfo();
  search -> graph = g;
  search -> discover = (int*)malloc(g -> numVerts() * sizeof(int));
  search -> finish = (int*)malloc(g -> numVerts() * sizeof(int));
  search -> parent = (int*)malloc(g -> numVerts() * sizeof(int));
  search -> finorder = (int*)malloc(g -> numVerts() * sizeof(int));
  disCount = 1;
  finCount = 1;
  for (int i = 0; i < g -> numVerts(); i++){
    search -> discover[i] = 0;
    search -> finish[i] = 0;
    search -> parent[i] = -1;
  }
  for (int vertex = 0; vertex < g -> numVerts(); vertex++){
    if (search -> discover[vertex] == 0){ // If the vertex has not been discovered yet
      DFSVisit(vertex, search);
    }
  }
  for (int j = 0; j < g -> numVerts(); j++){ // Orders finished verts in finorder. Come back to this in topocycle
    for (int k = 0; k < g -> numVerts(); k++){
      if (search -> finish[k] == j + 1){
	search -> finorder[j] = k;
      }
    }
  }
  return search;
}
