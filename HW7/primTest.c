#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "graph.h"
#include "graphio.h"
#include "primmst.h"
#include <math.h>

/*
 * Checker to ensure a Prim's solution is valid
 * 
 * Christopher Hittner, C 2018
 *
 */


// Find the largest edge on the path
float edge_check(Graph *g, int src, int dst, bool *check) {
    // Trivial outcome
    if (src == dst)
        return 0;
    
    // This node has been visited
    check[src] = true;
    
    int *succ = g->successors(src);
    for (int i = 0; succ[i] >= 0; i++) {
        int a = succ[i];
        
        if (a == dst) {
            // This is an edge leading directly to the result.
            delete succ;
            return g->edge(src, dst);
        } else if (!check[a]) {
            // Get the best edge on the path if it exists
            float w = edge_check(g, a, dst, check);
            if (!isnan(w)) {
                // There is a path.
                float e = g->edge(src, a);
                delete succ;
                return w > e ? w : e;
            }
        }
    }

    delete succ;
    return nan("1");
}

bool isValidPrim(Graph *g, Graph *mst) {

    for (int i = 0; i < g->numVerts(); i++) {
        // Reflexivity implies a cycle.
        if (mst->edge(i, i) != INFINITY)
            return false;

        // Get every outgoing edge in the tree.
        int *succ = g->successors(i);

        for (int j = 0; succ[j] >= 0; j++) {
            if (succ[j] < i)
                continue;

            // Mark list
            bool *check = new bool[g->numVerts()];
            for (int k = 0; k < g->numVerts(); k++)
                check[k] = false;
            
            // Get the largest weight in the tree
            float f = edge_check(mst, i, succ[j], check);
            delete check;

            // If the largest weight is bigger than the non-mst edge, fail
            // Similar if there is no path in the MST, because there must be.
            if (isnan(f) || f > g->edge(i, succ[j])) {
                delete succ;
                return false;
            }
        }

        delete succ;

        succ = mst->successors(i);
        for (int j = 0; succ[j] >= 0; j++)
            if (mst->edge(i, succ[j]) != mst->edge(succ[j], i))
                return false;

        delete succ;

    }

    return true;
}



/* Tests for Prim's MST algorithm.
 * Note: directly reads and writes the graph field of GraphInfo objects,
 * in order to print the spanning tree.
 */

/* Test MST on a graph.
 * Reading it in, we will make it symmetric.
 */
int main(int argc, char* argv[]){ 
   if(argc < 2){ 
     printf("Error! Must provide 1 file argument!\n"); 
     return 1; 
   } 
   printf("\n***************************************\nTesting %s\n", argv[1]); 
   char* filepath = argv[1]; 
   GraphInfo gi; 
   gi = readGraphMakeSymm(filepath, LIST ); //could also be matrix 
 
   //uncomment to print graph 
    printf("Original Graph:\n"); 
    writeGraph(gi);

   Graph* orig = gi->graph;  
   Graph* tree = minSpanTree(orig); 

   //uncomment out to print MST 

   printf("\n A min spanning tree for %s:\n", filepath); 
   gi->graph = tree;  
   writeGraph(gi); 
  
   if (isValidPrim(orig, tree)) 
     printf("MST Verification: PASSED\n"); 
   else 
     printf("MST Verification: FAILED\n"); 

   delete orig; 
   delete tree; 
 } 

