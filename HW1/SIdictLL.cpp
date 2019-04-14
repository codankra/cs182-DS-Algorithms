#include "SIdict.h"
#include <string>
#include <iostream>
// Conner Zeigman and Daniel Kramer
// I pledge on my honor that I have abided by the Stevens Honor System
Dict::Dict(){
  first = NULL;
}

struct Dict::DictNode{
  string key;
  int value;
  DictNode* next;
};

int Dict::hasKey(string key){
  DictNode* current = first;
  while (current != NULL){
    if ((current -> key).compare(key) == 0){
      return 1;
    }
    current = current -> next;
  }
  return 0;
}

int Dict::addOrUpdate(string key, int value){
  DictNode* current = first;
  if (hasKey(key) == 1){
    while (current != NULL){
      if((current -> key).compare(key) == 0){
	current -> value = value;
      }
      current = current -> next;
    }
    return 1;
  }
  else {
    if (current != NULL){
      while ((current -> next) != NULL){
	current = current -> next;
      }
      DictNode* newNode1 = new DictNode();
      current -> next = newNode1;
      newNode1 -> next = NULL;
      newNode1 -> value = value;
      newNode1 -> key = key;
    }
    else {
      DictNode* newNode = new DictNode();
      current = newNode;
      first = newNode;
      newNode -> value = value;
      newNode -> key = key;
      newNode -> next = NULL;
    }
    return 0;
  }
}

int Dict::lookup(string key){
  if (hasKey(key)){
    DictNode* current = first;
    while ((current -> key).compare(key) != 0){
      current = current -> next;
    }
    return current -> value;
  }
  else {
    return -1;
  }
}

int Dict::remKey(string key){
  if (hasKey(key) == 1){
    if(first == NULL){
      return -1;
    }
    DictNode* current = first;
    if ((current -> key).compare(key) == 0){
      first = current -> next;
      delete current;
      return 1;
    }
    DictNode* prev = current;
    current = current -> next;
    while ((current -> next) != NULL && (current -> key).compare(key) != 0){
      prev = current;
      current = current -> next;
    }
    prev -> next = current -> next;
    delete current;
    return 1;
  }
  return -2;
}
