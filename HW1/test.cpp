#include "SIdict.h"
#include <stdio.h>
#include <iostream>

int main(){
  Dict* d = new Dict();
  printf("%i\n", d -> addOrUpdate("a", 5));
  printf("%i\n", d -> addOrUpdate("b", 7));
  printf("%i\n", d -> addOrUpdate("c", 70));
  printf("%i\n", d -> remKey("c"));
  printf("%i\n", d -> addOrUpdate("d", 7000));
  printf("%i\n", d -> remKey("a"));
  printf("%i\n", d -> lookup("a"));
  printf("%i\n", d -> lookup("b"));
  printf("%i\n", d -> lookup("c"));
  printf("%i\n", d -> lookup("d"));
  printf("%i\n", d -> remKey("l"));
}
