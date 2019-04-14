#include "topocycle.h"
#include "dfs.h"
#include <stdio.h>
#include <cstdlib>
#include <math.h>

bool proper_ancestor(dfsinfo* di, int u, int v){ // DONE
  if (di -> discover[u] < di -> discover[v] && di -> finish[v] < di -> finish[u]){
    return true;
  }
  return false;
}

bool cyclic(dfsinfo* di, GraphInfo gi){ // DONE

  // Method 1: (20% efficacy)
  for (int u = 0; u < gi -> graph -> numVerts(); u++){
    for (int v = 0; v < gi -> graph -> numVerts(); v++){
      if (proper_ancestor(di, u, v) && gi -> graph -> edge(v, u) != 1.0/0.0){
	     return true;
      }
    }
  }
  return false;
  /*
  //Method 2:
  for (int u = 0; u < gi -> graph -> numVerts(); u++){
    int i = u;
    while (di->parent[i] != -1){
      if (di->parent[i] == u){
        return true;
        printf("%i%s%i\n", u, " does equal ", di->parent[i]);
      }
      printf("%i%s%i\n", u, " should eventually equal ", di->parent[i]);
      i = di->parent[i];
    }
    if (di->parent[i] = -1){
      printf("%s\n", "hreeeeeeeeee");
      int* arr = gi->graph->successors(u);
      int count = 0;
      while (arr[count] != -1){
        if (arr[count] = i){
          return true;
        }
        count++;
      }

    }
  }
  return false;
  */
}

int* topocycle(GraphInfo gi){ // DONE
  dfsinfo* info = DFS(gi -> graph);
  if (cyclic(info, gi)){
    return NULL;
  }
  int* topSort = (int*)malloc((gi -> graph -> numVerts() + 1) * sizeof(int));
  int count = gi -> graph -> numVerts() - 1;
  for (int i = 0; i < gi -> graph -> numVerts(); i++){
    topSort[i] = info -> finorder[count];
    count--;
  }
  topSort[gi -> graph -> numVerts()] = -1;
  return topSort;
}

void printTopocycle(GraphInfo gi){ // DONE
  int* sort = topocycle(gi);
  if (sort == NULL){
    printf("no possible sort");
  }
  else{ // vertnames is array for vertex names
    int index = 0;
    while (sort[index] != -1){
      printf("%s ", gi -> vertnames[sort[index]]);
      index++;
    }
  }
}

int* getCycleIfExists(dfsinfo* di, GraphInfo gi){ // Look at diff method for doing finorder (like when one is finished push it immediately into the array // Check each vertex and see if you can trace it back to negative one, if so not a cycle, else if get same num twice print the cycle
    if (cyclic(di, gi)){
      int* cycle = new int(gi -> graph -> numVerts() + 1); // -1 terminates the array so can just use the numVerts() as a max
      int u;
      int v;
      for (int i = 0;  i < gi -> graph -> numVerts(); i++){
        for (int j = 0; j < gi -> graph -> numVerts(); j++){
          if (proper_ancestor(di, i, j) && gi -> graph -> edge(j, i) != INFINITY){
            u = i;
            v = j;
            j = gi -> graph -> numVerts();
            i = gi -> graph -> numVerts();
          }    
        }
      }
      cycle[0] = v;
      int cycCount = 1;
      while (di -> parent[cycle[cycCount - 1]] != u ){ //INF LOOP
        cycle[cycCount] = di -> parent[cycle[cycCount - 1]];
        cycCount++;
      }
      cycle[cycCount] = u;
      while (di -> parent[cycle[cycCount -1]] != u){
        cycle[cycCount] = di -> parent[cycle[cycCount - 1]];
        cycCount++;
      }
      cycle[cycCount + 1] = -1;
      int flipper = 0;
      int* cycle2 = new int(gi -> graph -> numVerts() + 1);
      for (int i = cycCount; i >= 0; i--)
      {
        cycle2[flipper] = cycle[i];
        flipper++;
      }
      cycle2[flipper] = -1;
      return cycle2;
  }
  else{
    printf("%s\n", "cycle not detected");
    return NULL;
  }
}

void printCycleIfExists(dfsinfo* di, GraphInfo gi){
  if (cyclic(di, gi)){
    int* theCycle = getCycleIfExists(di, gi);
    int index = 0;
    while (theCycle[index] != -1){
      printf("%s ", gi -> vertnames[theCycle[index]]);
      index++;
    }
  }
  else{
    printf("no cycle");
  }
}
