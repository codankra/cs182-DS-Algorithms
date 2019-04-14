#include "SIdict.h"
#include <stdio.h>
#include <stdlib.h>

#define TOTAL_TESTS 13

bool run_test(int test_number) {
  switch(test_number) {
  case 1: {
    // test01 : should not have a key that hasn't been added
    Dict* d = new Dict();
    if(d->hasKey("abc")){  //should return false, since doesn't exist
      return false;
    }
    delete d;
    break;
  }

  case 2: {
    // test02 : if you add a key, it should be there
    Dict* d = new Dict();
    if(d->addOrUpdate("abc", 1)!=0){
      return false;
    }
    if(!d->hasKey("abc")){
      return false;
    }
    delete d;
    break;
  }

  case 3: {
    // test03 : if you add a key/value, should get back the value
    Dict* d = new Dict();
    d->addOrUpdate("abc", 42);
    if(d->lookup("abc") != 42) {
      return false;
    } else {
      return true;
    }
  }

  case 4: {
    // test04 : Should not be able to remove a key that isnt there
    Dict* d = new Dict();
    d -> addOrUpdate("abc", 1);
    if (d -> remKey("a") != -1){
      return false;
    }
    break; // if your test suceeds, break
  }

  case 5: {
    // test05 : Remove from a NULL dictionary
    Dict* d = new Dict();
    if (d -> remKey("a") != -1){
      return false;
    }
    break;
  }

  case 6: {
    // test06 : Update a key with a new value
    Dict* d = new Dict();
    d -> addOrUpdate("abc",1);
    d -> addOrUpdate("abc",2);
    if (d -> lookup("abc") != 2){
      return false;
    }
    break;
  }
    
  case 7: {
    // test07 : Add a key, remove it, then see if it is there
    Dict* d = new Dict();
    d -> addOrUpdate("abc",1);
    d -> remKey("abc");
    if (d -> hasKey("abc")){
      return false;
    }
    break;
  }

  case 8: {
    // test08 : Add a key and search for a key that isnt in the dictionary
    Dict* d = new Dict();
    d -> addOrUpdate("abc",1);
    if (d -> hasKey("abcd")){
      return false;
    }
    break;
  }

  case 9: {
    // test09 : Add a key and lookup a key that isnt in the dictionary
    Dict* d = new Dict();
    d -> addOrUpdate("abc",1);
    if (d -> lookup("abcd") != -1){
      return false;
    }
    break;
  }

  case 10: {
    // test10 : Add 3 keys remove the middle one
    Dict* d = new Dict();
    d -> addOrUpdate("a",1);
    d -> addOrUpdate("b",2);
    d -> addOrUpdate("c",3);
    d -> remKey("b");
    if (d -> hasKey("b")){
      return false;
    }
    break;
  }

  case 11: {
    // test11 : Add 3 keys remove the first one
    Dict* d = new Dict();
    d -> addOrUpdate("a",1);
    d -> addOrUpdate("b",2);
    d -> addOrUpdate("c",3);
    d -> remKey("a");
    if (d -> hasKey("a")){
      return false;
    }
    break;
  }  
    
  case 12: {
    // test12 : Add 3 keys remove the last one
    Dict* d = new Dict();
    d -> addOrUpdate("a",1);
    d -> addOrUpdate("b",2);
    d -> addOrUpdate("c",3);
    d -> remKey("c");
    if (d -> hasKey("c")){
      return false;
    }
    break; 
  }

  case 13: {
    // test13 : Add and lookup empty string
    Dict* d = new Dict();
    d -> addOrUpdate("", 1);
    if (d -> lookup("") != 1){
      return false;
    }
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
    printf("%s\n", (result == true ? "succeed" : "FAIL")); //stopping here
    if (result == false) num_fail++;
  }
  printf("SUMMARY: %d FAIL, %d succeed\n", num_fail, TOTAL_TESTS - num_fail);
}

  
