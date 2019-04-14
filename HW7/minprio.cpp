#include "minprio.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

MinPrio::MinPrio(Comparator compFunc, int maxsize){
  currentSize = 0;
  if (maxsize  < 1){
    maxsize = 1;
  }
  MAXSIZE = maxsize;
  handles = new handle*[MAXSIZE + 1];
  for (int i = 0; i < MAXSIZE + 1; i++){
    handles[i] = NULL;
  }
  comp = compFunc; //Dont know about this
}

MinPrio::~MinPrio(){
  for (int i = 0; i <= MAXSIZE; ++i)
  {
    if (handles[i] != NULL && i!=1)
    {
      handle* temp = handles[i];
      handles[i] = NULL;
      delete temp;
    }
  }
  delete []handles;
}

MinPrio::handle*  MinPrio::enqueue(void* item){  // May have to look at enqueueing NULL
  if (MAXSIZE == currentSize){
    return NULL;
  }
  currentSize++;
  handle* newHand = new handle();
  handles[currentSize] = newHand;
  handles[currentSize] -> content = item;
  handles[currentSize] -> pos = currentSize;
  int index = currentSize;
  while (index >= 2 && comp(handles[index] -> content, handles[index / 2] -> content) < 0){
    handle* temp = handles[index];
    handles[index] = handles[index / 2];
    handles[index] -> pos = index;
    handles[index / 2] = temp;    
    handles[index / 2] -> pos  = index / 2;
    index = index / 2;
  }
  return newHand;
}

bool MinPrio::nonempty(){
  if (currentSize >= 1){
    return true;
  }
  return false;
}

void* MinPrio::dequeueMin(){ // Make sure it isnt making handles[1] NULL
  if (nonempty()){
    void* returnable = handles[1] -> content;
    delete handles[1];
    if (currentSize>1){
      handles[1] = handles[currentSize];
      handles[1] -> pos = 1;
      handles[currentSize] = NULL; // = to NULL
    }
    currentSize--;
    int currentI = 1;
    bool swap = true;
    while (swap && currentSize > currentI * 2){
      swap = false;
      int comparison = comp(handles[currentI * 2] -> content, handles[currentI * 2 + 1] -> content);
      if (comparison >= 0){
	if (comp(handles[currentI] -> content, handles[currentI * 2 + 1] -> content) > 0){
	  handle* temp = handles[currentI * 2 + 1];
	  handles[currentI * 2 + 1] = handles[currentI];
	  handles[currentI * 2 + 1] -> pos = currentI;
	  handles[currentI] = temp; 
	  handles[currentI] -> pos = currentI * 2 + 1;
	  currentI = currentI * 2 + 1;
	  swap = true;
	}
      }
      else if (comparison < 0){
	if (comp(handles[currentI] -> content, handles[currentI * 2] -> content) > 0){
	  handle* temp = handles[currentI * 2];
	  handles[currentI * 2] = handles[currentI];
	  handles[currentI * 2] -> pos = currentI;
	  handles[currentI] = temp;
	  handles[currentI] -> pos = currentI * 2;
	  currentI = currentI * 2;
	  swap = true;
	}
      }
    }
    if (currentSize == currentI * 2){
      if (comp(handles[currentI] -> content, handles[currentI * 2] -> content) > 0){
	handle* temp = handles[currentI * 2];
	handles[currentI * 2] = handles[currentI];
	handles[currentI * 2] -> pos = currentI;
	handles[currentI] = temp;
	handles[currentI] -> pos = currentI * 2;
	currentI = currentI * 2;
      }
    }
    return returnable;
  }
  return NULL;
}

void MinPrio::decreasedKey(handle* hand){
  int index = hand -> pos;
  while (index >= 2 && comp(handles[index] -> content, handles[index / 2] -> content) < 0){
    handle* temp = handles[index];
    handles[index] = handles[index / 2];
    handles[index / 2] = temp;
    handles[index] -> pos = index;
    handles[index / 2] -> pos = index / 2;
    index = index / 2;
  }
  if (index == 1)
  {
    if (handles[2] != NULL && comp(handles[1] -> content, handles[2] -> content) > 0)
    {
      handle* temp = handles[2];
      handles[2] = handles[1];
      handles[2]->pos = 1;
      handles[1] = temp;
      handles[1] -> pos = 2;
    }
  }
}
  
