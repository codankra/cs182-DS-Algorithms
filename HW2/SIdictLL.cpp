#include "SIdict.h"
#include <string>
#include <iostream>

// I pledge on my honor that I have abided by the Stevens Honor System
// Conner Zeigman and Daniel Kramer

struct Dict::DictNode{
  string key;
  int value;
  DictNode* next;
};

Dict::Dict(){
  first = NULL;
}

void destructHelper(Dict::DictNode* current){
  if (current == NULL){
    return;
  }
  Dict::DictNode* next = current -> next;
  delete current;
  destructHelper(next);
}
Dict::~Dict(){
  if (first == NULL){
    return;
  }
  destructHelper(first);
}

int compareKey(Dict::DictNode *current, string key){
  if (current == NULL) {
    return 0;
  }
  if ((current -> key).compare(key) == 0){
    return 1;
  }
  return compareKey(current -> next, key);
}

int Dict::hasKey(string key){
  return compareKey(first, key);
}

int updateNode(Dict::DictNode *current, string key, int val){
  if ((current -> key).compare(key) == 0){
    current -> value = val;
    return 1;
  }
  return updateNode(current -> next, key, val);
}
int addNode(Dict::DictNode *current, string key, int val){
  if (current -> next == NULL){
    Dict::DictNode* newNode1 = new Dict::DictNode();
    current -> next = newNode1;
    newNode1 -> next = NULL;
    newNode1 -> value = val;
    newNode1 -> key = key;
    return 1;
  }
    return addNode(current -> next, key, val);
}

int Dict::addOrUpdate(string key, int val){
  if (hasKey(key) == 1){
    updateNode(first, key, val);
    return 1;
  }
  else{
    if (first == NULL){
      DictNode* newNode = new Dict::DictNode();
      first = newNode;
      newNode -> value = val;
      newNode -> key = key;
      newNode -> next = NULL;
    }
    else{
      return addNode(first, key, val);
    }
    return 0;
  }
}


int findKey(Dict::DictNode* current, string key){
  if ((current -> key).compare(key) == 0){
    return current -> value;
  }
    return compareKey(current -> next, key);
}

int Dict::lookup(string key){
  if (hasKey(key) == 1){
    return findKey(first, key);
  }
  else{
    return -1;
  }
}

int remNode(Dict::DictNode* prev, Dict::DictNode* current, string key){
  if (current == NULL){
    return -1;
  }
  else if((current -> key).compare(key) == 0){
    prev -> next = current -> next;
    delete current;
    return 1; 
  }
  else{
    return remNode(current, current-> next, key);
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
    return remNode(prev, current, key);
  }
  return -1;
}
  


