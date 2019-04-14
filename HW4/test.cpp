#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "ArrayEq.h"

#define TOTAL_TESTS 10

bool run_test(int test_number) {
  switch(test_number) {
  case 1: {
    // test01 : Add an edge to a graph (matrix) and make sure its there
    Graph* g = new Graph(4, 0);
    g -> addEdge(0, 1, 5);
    if (g -> edge(0, 1) != 5){
      return false;
    }
    delete g;
    break;
  }

  case 2: {
    // test02 : Add an edge to a graph (list) and make sure its there
    Graph* g = new Graph(4, 1);
    g -> addEdge(0, 1, 5);
    if (g -> edge(0, 1) != 5){
      return false;
    }
    delete g;
    break;
  }

    
  case 3: {
    // test03 : Adds a bunch of edges to a graph (matrix) and then checks the successors to one
    Graph* g = new Graph(6, 0);
    g -> addEdge(3, 0, 4);
    g -> addEdge(3, 1, 1);
    g -> addEdge(3, 2, 2);
    g -> addEdge(0, 1, 3);
    g -> addEdge(1, 0, 3);
    g -> addEdge(2, 0, 5);
    g -> addEdge(2, 5, 1);
    int *successor = g -> successors(2);
    int i = 0;
    bool false1 = false;
    bool false2 = false;
    while (successor[i] != -1){
      if (successor[i] == 0){
	false1 = true;
      }
      if (successor[i] == 5){
	false2 = true;
      }
      i++;
    }
    if (!false1 || !false2){
      return false;
    }
    delete g;
    break;
  }
  case 4: {
    // test04 : Adds a bunch of edges to a graph (matrix) and then checks the preds to one
    Graph* g = new Graph(6, 0);
    g -> addEdge(3, 0, 4);
    g -> addEdge(3, 1, 1);
    g -> addEdge(3, 2, 2);
    g -> addEdge(0, 1, 3);
    g -> addEdge(1, 0, 3);
    g -> addEdge(2, 1, 5);
    g -> addEdge(2, 2, 1);
    int * pred = g -> predecessors(2);
    int i = 0;
    bool false1 = false;
    bool false2 = false;
    while (pred[i] != -1){
      if (pred[i] == 2){
	false1 = true;
      }
      if (pred[i] == 3){
	false2 = true;
      }
      i++;
    }
    if (!false1 || !false2){
      return false;
    }
    delete g;
    break;
  }
    
    
  case 5: {
    // test05 : Add an edge to a graph, copy the graph, and then search for the edge in the old and new graph
    Graph* g = new Graph(8, 0);
    g -> addEdge(4, 4, 6);
    Graph* k = g -> cloneGraph(0);
    if (g -> edge(4, 4) != 6 || k -> edge(4, 4) != 6){
      return false;    
    }
    delete g;
    delete k;
    break;
  }


  case 6: {
    // test06 : Add an edge to a graph, copy the graph, and check to see if the successors are the same
    Graph* g = new Graph(6, 0);
    g -> addEdge(3, 0, 4);
    g -> addEdge(3, 1, 1);
    g -> addEdge(3, 2, 2);
    g -> addEdge(0, 1, 3);
    g -> addEdge(1, 0, 3);
    g -> addEdge(2, 1, 5);
    g -> addEdge(2, 2, 1);
    Graph* k = g -> cloneGraph(0);
    if (!eq(g -> successors(2), k -> successors(2))){
      return false;    
    }
    delete g;
    delete k;
    break;
  }

  case 7: {
    // test07 : Add an edge to a graph, copy the graph, and check to see if the predessors are the same
    Graph* g = new Graph(6, 0);
    g -> addEdge(3, 0, 4);
    g -> addEdge(3, 1, 1);
    g -> addEdge(3, 2, 2);
    g -> addEdge(0, 1, 3);
    g -> addEdge(1, 0, 3);
    g -> addEdge(2, 1, 5);
    g -> addEdge(2, 2, 1);
    
    Graph* k = g -> cloneGraph(0);
    if (!eq(g -> predecessors(2), k -> predecessors(2))){
      return false;
    }
    delete g;
    delete k;
    break;
  }
  case 8: {
    // test08 : Unadded edge should give infinity weight
    Graph* g = new Graph(4, 1);
    if (g -> edge(0, 1) != 1.0 / 0.0){
      return false;
    }
    delete g;
    break;
  }
  case 9: {
    // test09 : Deleted edge should give infinity weight
    Graph* g = new Graph(4, 1);
    g -> addEdge(0, 1, 5);
    g -> addEdge(1, 1, 6);
    g -> delEdge(1, 1);
    if (g -> edge(1, 1) != 1.0 / 0.0){
      return false;
    }
    delete g;
    break;
  }
  case 10: {
    // test10 : Cannot delete edge twice
    Graph* g = new Graph(4, 1);
    g -> addEdge(1, 1, 6);
    g -> addEdge(0, 1, 5);
    g -> delEdge(1, 1);
    if (g -> delEdge(1, 1)){
      return false;
    }
    delete g;
    break;
  }

    
  default: {
    printf("ERROR! Test number %d was not found!\n", test_number);
    exit(1);
  }
    
  }
  // test must have passed.
  return true;
}

int main() {
  int num_fail = 0;
  for (int tn = 1; tn <= TOTAL_TESTS; tn++) {
    printf("- running test # %02d ... ", tn);
    int result = run_test(tn);
    printf("%s\n", (result == true ? "succeed" : "FAIL"));
    if (result == false) num_fail++;
  }
  printf("SUMMARY: %d FAIL, %d succeed\n", num_fail, TOTAL_TESTS - num_fail);
}
