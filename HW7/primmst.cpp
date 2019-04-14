#include "primmst.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
struct content{
  int parent;
  float dist;
};
int compFunc(void* lhs, void* rhs){
  if (((content*)lhs) -> dist > ((content*) rhs) -> dist)
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

Graph* minSpanTree(Graph* g){
  Graph* T = new Graph(g -> numVerts(), 1);
  int* link = new int[g -> numVerts()];
  int* inQ = new int[g -> numVerts()];
  MinPrio::handle** handles = new MinPrio::handle*[g -> numVerts()];
  MinPrio* Q = new MinPrio(&compFunc, g -> numVerts());
  for (int i = 0; i < g -> numVerts(); i++){
    link[i] = 0;
    handles[i] = NULL;
    inQ[i] = 1;
  }  
  content* def = new content();
  def -> dist = 0;
  def -> parent = 0;
  handles[0] = Q -> enqueue(def);
  for (int i = 1; i < g -> numVerts(); i++){
    content* enqueued = new content();
    enqueued -> parent = i;
    enqueued -> dist = INFINITY;
    handles[i] = Q -> enqueue(enqueued); 
  }
  while(Q -> nonempty()){
    content* contentable = (content*) (Q -> dequeueMin());
    int v = contentable -> parent;
    handles[v] = NULL;
    inQ[v] = 0;
    int* suc = g -> successors(v);
    int sucCount = 0;
    int u = suc[sucCount];
    //contentable->parent = v
    //suc[sucCount] = u, a successor of v
    while(u != -1){

      if (inQ[u] && g -> edge(v, u) < ((content*)(handles[u] -> content)) -> dist){

        link[u] = v;
        //update weight
        ((content*)(handles[u] -> content)) -> dist = g -> edge(v, u);
        //call decreased key
        Q -> decreasedKey(handles[u]);
      }
      sucCount++;
      u = suc[sucCount];
    }
  }
  for (int i = 0; i < g -> numVerts(); i++)
  {
    T -> addEdge(i, link[i], g -> edge(i, link[i]));
    T -> addEdge(link[i], i, g -> edge(i, link[i]));
  }
  return T;
}
