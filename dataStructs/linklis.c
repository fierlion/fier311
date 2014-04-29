#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node{
  int x;
  struct node * next;
};

int main(int argc, char **argv){
  struct node * root;
  struct node * conductor;

  root = malloc(sizeof(struct node));
  root->next = 0;
  root->x = 12;
  conductor = root;
  if (conductor != 0){
    while (conductor->next != 0){
      conductor = conductor-> next;
    }
  }
  conductor->next = malloc(sizeof(struct node));
  conductor = conductor->next;
  conductor->x = 5
  return 0;


}
