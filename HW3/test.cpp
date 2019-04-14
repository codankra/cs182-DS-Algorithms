#include "SIdict.h"
#include <stdio.h>
#include <stdlib.h>

#define TOTAL_TESTS 10

bool run_test(int test_number) {
  switch(test_number) {
  case 1: {
    // test01 : Add key, remove it, check if it is there
    Dict* d = new Dict();
    d->addOrUpdate("abc", 1);
    d->remKey("abc");
    if(d->hasKey("abc")){  //should return false, since removed
      return false;
    }
    delete d;
    break;
  }
  case 2: {
    // test02 : Add key, remove it, try looking it up
    Dict* d = new Dict();
    d->addOrUpdate("abc", 1);
    d->remKey("abc");
    if(d->lookup("abc") != -1){  //should return false, since removed
      return false;
    }
    delete d;
    break;
  }
  case 3: {
    // test03 : Add key, remove it, add again with updated value try looking it up
    Dict* d = new Dict();
    d->addOrUpdate("abc", 1);
    d->remKey("abc");
    d->addOrUpdate("abc", 4);
    if(d->lookup("abc") != 4){ 
      return false;
    }
    delete d;
    break;
  }
  case 4: {
    // test04 : Add key, check if a different key exists
    Dict* d = new Dict();
    d->addOrUpdate("abc", 1);
    if(d->hasKey("abcd")){ 
      return false;
    }
    delete d;
    break;
  }
  case 5: {
    // test05 : Add key, update value, lookup for new value
    Dict* d = new Dict();
    d->addOrUpdate("abc", 1);
    d->addOrUpdate("abc", 2);
    if(d->lookup("abc") != 2){ 
      return false;
    }
    delete d;
    break;
  }
  case 6: {
    // test06 : Add 2 keys, remove first, try to find 2nd
    Dict* d = new Dict();
    d->addOrUpdate("abc", 1);
    d->addOrUpdate("abcd", 2);
    d-> remKey("abc");
    if(!d->hasKey("abcd")){ 
      return false;
    }
    delete d;
    break;
  }
  case 7: {
    // test07 : Add 2 keys, remove first, lookup 2nd
    Dict* d = new Dict();
    d->addOrUpdate("abc", 1);
    d->addOrUpdate("abcd", 2);
    d-> remKey("abc");
    if(d->lookup("abcd") != 2){ 
      return false;
    }
    delete d;
    break;
  }
  case 8: {
    // test08 : Add a key, remove a different key (nonexistant)
    Dict* d = new Dict();
    d->addOrUpdate("abc", 1);
    if(d-> remKey("abcd") != -1){ 
      return false;
    }
    delete d;
    break;
  }
  case 9: {
    // test09 : Add and look up empty string.
    Dict* d = new Dict();
    d->addOrUpdate("", 1001);
    if(d-> lookup("") != 1001){ 
      return false;
    }
    delete d;
    break;
  }
  case 10: {
    // test10 : Remove a key from empty dictionary.
    Dict* d = new Dict();
    if(d-> remKey("finalcase") != -1){ 
      return false;
    }
    delete d;
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

  
