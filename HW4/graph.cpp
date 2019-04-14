#include "graph.h"
#include <cstdlib>
#include <stdio.h>

// I pledge on my honor that I have abided by the Stevens Honor System
// Conner Zeigman Daniel Kramer

struct Graph::Node{
  Node* next;
  int vert;
  float weight;
};

Graph::Graph(int n, int rep){
  type = rep;
  if (n < 1){
    numVertices = 1;
  }
  else{
    numVertices = n;
  }
  if(type == 1){
    list = new Node*[numVertices];
    for (int i = 0; i < numVertices; i++){
      list[i] = NULL;
    }
  }
  else{
    type = 0;
    matrix = new float[numVertices * numVertices];
    for (int i = 0; i < numVertices * numVertices; i++){
      // matrix[i] represents the weight of a certain edge
      matrix[i] = INFINITY;
    }
  }
}

Graph::~Graph(){
  if (type == 1){
    for (int i = 0; i < numVertices; i++){
      Node* current = list[i];
      if (current != NULL){
	while(current -> next != NULL){
	  Node* hold = current;
	  current = current -> next;
	  delete hold;
	}
      }
      delete current;
    }
  }
  else{
    delete[] matrix;
  }
}

Graph* Graph::cloneGraph(int rep){
  if (rep == 1 || rep == 0){
    Graph* copy = new Graph(numVertices, rep);
    for (int i = 0; i < numVertices; i++){
      int j = 0;
      int *putToNode = successors(i);
      while (putToNode[j] != -1){
	copy -> addEdge(i, putToNode[j], edge(i, putToNode[j]));
	j++;
      }
    }
    return copy;
  }
  else{
    return NULL;
  }
}

int Graph::numVerts(){
  return numVertices;
}

bool Graph::addEdge(int source, int target, float w){
  if (w == INFINITY || w < 0){
    return false;
  }
  if (source >= numVertices || source < 0 || target >= numVertices || target < 0){
    return false;
  }
  if (type == 1){
    if (list[source] == NULL){
      list[source] = new Node();
      list[source] -> next = NULL;
      list[source] -> vert = target;
      list[source] -> weight = w;
      return true;
    }
    else{
      Node* current = list[source];
      while (current -> next != NULL){
	if (current -> next -> vert == target){
	  return false;
	}
	current = current -> next;
      }
      current -> next = new Node();
      current -> next -> next = NULL;
      current -> next -> vert = target;
      current -> next -> weight = w;
      return true;
    }
  }
  else{
    int index = numVertices * source + target;
    if (matrix[index] != INFINITY){
      return false;
    }
    matrix[index] = w;
    return true;
  }
}

bool Graph::delEdge(int source, int target){
  if (source >= numVertices || source < 0 || target >= numVertices || target < 0){
    return false;
  }
  if (type == 1){
    if (list[source] == NULL){
      return false;
    }
    Node* current = list[source];
    if (current -> vert == target){
      list[source] = current -> next;
      delete current;
      return true;
    }
    while (current -> next != NULL && current -> next -> vert != target){
      current = current -> next;
    }
    if (current -> next == NULL){
      return false;
    }
    current -> next = current -> next -> next;
    return true;
  }
  else{
    int index = numVertices * source + target;
    if (matrix[index] == INFINITY){
      return false;
    }
    matrix[index] = INFINITY;
    return true;
  }
}

float Graph::edge(int source, int target){
  if (source >= numVertices || source < 0 || target >= numVertices || target < 0){
    return -1.0;
  }
  if (type == 1){
    if (list[source] == NULL){
      return INFINITY;
    }
    Node* current = list[source];
    if (current -> vert == target){
      return current -> weight;
    }
    while (current -> next != NULL && current -> next -> vert != target){
      current = current -> next;
    }
    if (current -> next == NULL){
      return INFINITY;
    }
    return current -> next -> weight;
  }
  else{
    return matrix[numVertices * source + target];
  }
}

int* Graph::successors(int source){
  if (source < 0 || source >= numVertices){
    return NULL;
  }
  int size = numVertices + 1;
  int* suc = (int*)malloc(size * sizeof(int));
  int count = 0;
  if (type == 1){
    Node* current = list[source];    
    while (current != NULL){
      suc[count] = current -> vert;
      count++;
      current = current -> next;
    }
  }
  else{
    int index = source * numVertices;
    for (int i = index; i < index + numVertices; i++){
      // not going into this if statement
      if (matrix[i] != INFINITY){
	suc[count] = i % numVertices;
	count++;
      }
    }
  }
  suc[count] = -1;
  return suc;
}

int* Graph::predecessors(int target){
  if (target < 0 || target >= numVertices){
    return NULL;
  }
  int size = numVertices + 1;
  int* pred = (int*)malloc(size * sizeof(int));
  int count = 0;
  if (type == 1){
    for(int i = 0; i < numVertices; i++){
      Node* current = list[i];
      while (current != NULL){
	if (current -> vert == target){
	  pred[count] = i;
	  count++;
	}
	current = current -> next;
      }
    }
  }
  else{
    for (int i = target; i < numVertices * numVertices; i += numVertices){
	if (matrix[i] != INFINITY){
	  pred[count] = i / numVertices;
	  count++;
	}
    }
  }
  pred[count] = -1;
  return pred;
}
