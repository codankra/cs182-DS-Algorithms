#include "sorting.hpp"
#include <stdio.h>
#include <iostream>

int binsearch(std::string ar[], int low, int high, std::string value){
  int mid;
  if (low == high){
    return low;
  }
  mid = low + (high - low) / 2;
  if (value.compare(ar[mid]) > 0){
    return binsearch(ar, mid + 1, high, value);
  }
  else if (value.compare(ar[mid]) < 0){
    return binsearch(ar, low, mid, value);
  }
  return mid;
}

  void insertionsort(std::string ar[], int l, int r){
  for (int i = l; i < r; i++){
    int insert = binsearch(ar, 0, i, ar[i]);
    string temp = ar[i];
    for (int j = i - 1; j >= insert; j--){
      ar[j + 1] = ar[j];
    }
    ar[insert] = temp;
  }
}

void quicksort(std::string arr[], int l, int r){
  if (l < r){
    std::string pivot = arr[l];
    int i = l;
    if (l == (r - 1))
    {
      i = l-1;
    }
    int j = r;
    do {
      do{ 
        i++;
      } while (!(arr[i].compare(pivot) >= 0) && i < (r - 1));
      do{
        j--;
      } while (!(arr[j].compare(pivot) <= 0) && j > l);
      std::string temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;

    } while (!(i >= j));
    std::string temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    temp = arr[l];
    arr[l] = arr[j];
    arr[j] = temp;
    
    quicksort(arr, l, j); // j - 1 b/c j is now the pivot and sorted
    quicksort(arr, j + 1, r);
  }
}

void quicksortPlus(std::string arr[], int l, int r){
  if ((r - l) <11){
    insertionsort(arr, l, r);
  }
  else if (l < r){
    string pivot;
    string left = arr[l];
    string right = arr[r - 1];
    string mid = arr[(l+r)/2];
    std::string temp;
    int pivI;
    if (left.compare(mid) <= 0 && left.compare(right) >= 0 || left.compare(mid) >= 0 && left.compare(right) <= 0){
      pivot = left;
      pivI = l;
    }
    if (mid.compare(left) <= 0 && mid.compare(right) >= 0 || mid.compare(left) >= 0 && mid.compare(right) <= 0){
      pivot = mid;
      pivI = (r + l)/2;
    }
    else{
      pivot = right;
      pivI = r - 1;
    }

    temp = arr[l];
    arr[l] = pivot;
    arr[pivI] = temp;

    int i = l;
    int j = r;
    do {
      do{ 
        i++;
      } while (!(arr[i].compare(pivot) >= 0) && i < (r - 1));
      do{
        j--;
      } while (!(arr[j].compare(pivot) <= 0) && j > l);
      temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;

    } while (!(i >= j));
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    temp = arr[l];
    arr[l] = arr[j];
    arr[j] = temp;

    quicksortPlus(arr, l, j); // j - 1 b/c j is now the pivot and sorted
    quicksortPlus(arr, j + 1, r);
  }
}
/* Assume arr has length at least len.
 * For each of the three sort functions, run it 10 times on arr, and print the total time 
 * for each of the three functions in a format simlar to the one below:
 * (it doesn't need to be identical to the below output or in the same order as below,
 *  but it should print the sort name, total time, and time per each iteration)
     QuickSort: 100ms total, 5ms per iteration
   QuickSortPlus: 80ms total, 4ms per iteration
   Insertion Sort: 600ms total, 30ms per iteration
   
 * Reference sortTimeDemo for an example of using timings.
 */ 
void compareSorts(std::string arr[], int len){
  clock_t begin, end;
  double time_spent;
  string acopy[len];
  

  begin = clock();
  
  for (int i = 0; i < 10; ++i)
  {
    for (int i = 0; i < len; i++)
      acopy[i] = arr[i];
    quicksort(acopy, 0, len);
  }
  end = clock();
  time_spent = ((double)(end - begin)) / CLOCKS_PER_SEC;

  printf("Quicksort: %fs total, %fs per iteration\n", time_spent, time_spent/10);

  begin = clock();
  
  for (int i = 0; i < 10; ++i)
  {
    for (int i = 0; i < len; i++)
      acopy[i] = arr[i];
    quicksortPlus(acopy, 0, len);
  }
  end = clock();
  time_spent = ((double)(end - begin)) / CLOCKS_PER_SEC;
  printf("QuicksortPlus: %fs total, %fs per iteration\n", time_spent, time_spent/10);
  


  begin = clock();
  
  for (int i = 0; i < 10; ++i)
  {
    for (int i = 0; i < len; i++)
      acopy[i] = arr[i];
    insertionsort(acopy, 0, len);
  }
  end = clock();
  time_spent = ((double)(end - begin)) / CLOCKS_PER_SEC;
  printf("Insertion Sort: %fs total, %fs per iteration\n", time_spent, time_spent/10);
  
}
