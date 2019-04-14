#include "SIdict.h"
#include <string>
#include <iostream>
#include<stdio.h>

// I pledge on my honor that I have abided by the Stevens Honor System
//Daniel Kramer

struct Dict::DictNode{
  string key;
  int value;
  DictNode* left;
  DictNode* right;
  bool isDeleted;
};

Dict::Dict(){
  first = NULL;
}

void destructHelper(Dict::DictNode *current){
  if (current == NULL){

  }
  else if (current -> left != NULL && current -> right != NULL){
    destructHelper(current -> left);
    destructHelper(current -> right);
  }
  else if (current -> left == NULL){
    destructHelper(current -> right);
  }
  else if (current -> right != NULL){
    destructHelper(current -> left);
  }
}
Dict::~Dict(){
  destructHelper(first);
}


int compareKey(Dict::DictNode *current, string key){
  if (current == NULL) {
    return 0;
  }
  if (((current -> key).compare(key) == 0) && !(current -> isDeleted)){
    return 1;
  }
  if (((current -> key).compare(key) == 0) && (current -> isDeleted)){
    return 0;
  }
  if ((current -> key).compare(key) > 0){
    return compareKey(current -> right, key);
  }
  if ((current -> key).compare(key) < 0){
    return compareKey(current -> left, key);
  }
  else return -9999; //Error testing
}

/* whether key is present. 
   Returns 1 if key is present, 0, if not present*/
int Dict::hasKey(string key){
  return compareKey(first, key);
}


/* map key to val; return 1 if 
   key was already present (and update the node with the new val) 
   else 0 (and insert the new node) 
   An empty key *is* considered a valid input, and can be inserted into the data structure,
   just like any other key. You shouldn't return an error for the empty string "".
*/

int updateNode(Dict::DictNode *current, string key, int val){
  if ((current -> key).compare(key) == 0){
    current -> value = val;
    return 1;
  }
  else if ((current -> key).compare(key) > 0){
    updateNode(current->right, key, val);
  }
  else if ((current -> key).compare(key) < 0){ 
    updateNode(current -> left, key, val);
  }
}
int addNode(Dict::DictNode *current, string key, int val){
  if ((current -> key).compare(key) == 0){
    current -> isDeleted = false;
    current -> value = val;
    return 0;
  }
  else if ((current -> key).compare(key) > 0){
    if (current -> right == NULL){
      //add node code
      Dict::DictNode* newNode1 = new Dict::DictNode();
      current -> right = newNode1;
      newNode1 -> left = NULL;
      newNode1 -> right = NULL;
      newNode1 -> value = val;
      newNode1 -> key = key;
      return 0;
    }
    addNode(current -> right, key, val);
  }
  else if ((current -> key).compare(key) < 0){
    if (current -> left == NULL){
      //add node code
      Dict::DictNode* newNode1 = new Dict::DictNode();
      current -> left = newNode1;
      newNode1 -> left = NULL;
      newNode1 -> right = NULL;
      newNode1 -> value = val;
      newNode1 -> key = key;
      return 0;
    }
    addNode(current -> left, key, val);
  }

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
      newNode -> left = NULL;
      newNode -> right = NULL;
      return 0;
    }
    else{
      addNode(first, key, val);
      return 0;
    }
  }
}

/* get value associated with key
   Precondition: key is present 
   Returns value of the key. You do not need to check the precondition, but
   if you do, return -1 if the key is not found
*/
int findKey(Dict::DictNode* current, string key){
  if ((current -> key).compare(key) == 0){
    return current -> value;
  }
  else if ((current -> key).compare(key) > 0){
    return findKey(current -> right, key);
  }
  else if ((current -> key).compare(key) < 0){ 
    return findKey(current -> left, key);
  }
}

int Dict::lookup(string key){
  if (hasKey(key) == 1){
    return findKey(first, key);
  }
  else{
    return -1;
  }
}

/* remove key/val, and return 1 if the node is successfully removed
   Precondition: key is present. You do not need to check the precondition, but
   if you do, return -1 if the key is not found */
void flag(Dict::DictNode* current, string key){
  if ((current -> key).compare(key) == 0){
    current -> isDeleted = true;
  }
  else if ((current -> key).compare(key) > 0){
    flag(current -> right, key);
  }
  else if ((current -> key).compare(key) < 0){ 
    flag(current -> left, key);
  }
}

int Dict::remKey(string key){
  if (hasKey(key) == 1){
    flag(first, key);
    return 1;
  }
  else{
    return -1;
  }
}


