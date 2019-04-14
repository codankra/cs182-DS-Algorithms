

#include "primmst.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Indicates the error when the test case fails

/* Do NOT test Prim's MST algorithm from this test file
 * Only test your priority queue.
 */
#define TOTAL_TESTS 5

//Comparison function for int
int compInt(void* x, void* y){
  int* a = (int*) x;
  int* b = (int*) y;
  if(a[0] < b[0]) return -1;
  else if (a[0] > b[0]) return 1;
  return 0;
}

//Comparison function for char
int compChar(void* x, void* y){
  char* a = (char*) x;
  char* b = (char*) y;
  
  return strcmp(a,b);
}


bool run_test(int test_number) {
  switch(test_number) {
  case 1: { //Make sure enqueue detects full queue and dequeue detects empty queue
    MinPrio* p = new MinPrio(&compInt, 5);
    int a = 3;
    int b = 2;
    int c = 8;
    int d = -9;
    int e = 5;
    if (p->nonempty())
    {
      delete p;
      return false;
    }
    p->enqueue(&a);
    p->enqueue(&b);
    p->enqueue(&c);
    p->enqueue(&d);
    p->enqueue(&e);

    if (p->enqueue(&a) != NULL)
    {
      delete p;
      return false;
    }
    delete p;
    break;
  }

  case 2: {
    // test02 : Make sure items are dequeued in the correct order
    MinPrio* p = new MinPrio(&compInt, 5);
    int a = 3;
    int b = 2;
    int c = 8;
    int d = -9;
    int e = 5;
    p->enqueue(&a);
    p->enqueue(&b);
    p->enqueue(&c);
    p->enqueue(&d);
    p->enqueue(&e);
    if(compInt(p->dequeueMin(), &d) != 0){
       printf("Incorrect order! Expected: %i", d);
       delete p;
       return false;
    }
    if(compInt(p->dequeueMin(), &b) != 0){
       printf("Incorrect order! Expected: %i", b);
       delete p;
       return false;
    }
    if(compInt(p->dequeueMin(), &a) != 0){
       printf("Incorrect order! Expected: %i", a);
       delete p;
       return false;
    }
    if(compInt(p->dequeueMin(), &e) != 0){
       printf("Incorrect order! Expected: %i", e);
       delete p;
       return false;
    }
    if(compInt(p->dequeueMin(), &c) != 0){
       printf("Incorrect order! Expected: %i", c);
       delete p;
       return false;
    }

    delete p;
    break;
  }

  case 3: {
    // test03 :Make sure decreasedKey re-orders queue correctly
    MinPrio* q = new MinPrio(&compInt, 5);

    int a = 3;
    int b = 2;
    int c = 8;
    int d = -9;
    int e = 5;
    MinPrio::handle* h;
    //Assumes enqueue() works
    q->enqueue(&a);
    q->enqueue(&b);
    h = (q->enqueue(&c));
    q->enqueue(&d);
    q->enqueue(&e);

    //Tests decreasedKey()
    ((int*)h->content)[0] = 9;
    q->decreasedKey(h);


    

    //Now c should be LAST instead of first to dequeue
    q->dequeueMin();
    q->dequeueMin();
    q->dequeueMin();
    q->dequeueMin();
    if (compInt(q->dequeueMin(), &c) != 0){
      printf("Incorrect order! This may be due to your decreasedKey() method. Expected: %i", c);
      delete q;
      return false;
    }
    delete q;
    break;
  }

    
  case 4: {
    // test04 : Tests dequeuing when empty
    MinPrio* p=new MinPrio(&compInt, 5);
    int a = 3;
    int b = 2;
    int c = 8;
    int d = -9;
    int e = 5;
    if(p->nonempty()){
      delete p;
      return false;
    }
    if (p->dequeueMin()!=NULL)
    {
      delete p;
      return false;
    }
    break; // if your test suceeds, break
  }
    
  case 5: {
    // test05 :Enqueueing with uppercase and lowercase chars (and num chars) 0<A<a.
    //Also test multiple of same value in queue
    MinPrio* p=new MinPrio(&compChar, 5);
    char a = 'E';
    char b = 'r';
    char c = 'r';
    char d = '0';
    char e = 'R';
    
    p->enqueue(&c);
    p->enqueue(&d);
    p->enqueue(&e);
    p->enqueue(&a);
    p->enqueue(&b);

    if(compChar(p->dequeueMin(), &d) != 0){
       printf("Incorrect order! Expected: %c", d);
       delete p;
       return false;
    }
    if(compChar(p->dequeueMin(), &a) != 0){
       printf("Incorrect order! Expected: %c", a);
       delete p;
       return false;
    }
    if(compChar(p->dequeueMin(), &e) != 0){
       printf("Incorrect order! Expected: %c", e);
       delete p;
       return false;
    }
    if(compChar(p->dequeueMin(), &b) != 0){
       printf("Incorrect order! Expected: %c", b);
       delete p;
       return false;
    }
    //These last two could be in EITHER order
    if(compChar(p->dequeueMin(), &c) != 0){
       printf("Incorrect order! Expected: %c", c);
       delete p;
       return false;
    }

    delete p;
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

