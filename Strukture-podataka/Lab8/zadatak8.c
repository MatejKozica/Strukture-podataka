#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct _treeNode * Position;

typedef struct _treeNode{
  Position firstChild;
  Position nextSibling;
  char * path;
}TreeNode;

int createChild(Position node, char * name);
int createSibling(Position node, char * name);
int cd(Position node, char * name);
int dir(Position node);
int app();
Position handleInput(Position node, char * input);


int main(){
  app();

  return 0;
}

int createChild(Position node, char * name){
  Position temp = (Position)malloc(sizeof(TreeNode));
  if(temp == NULL){
    return -1;
  }

  temp->path = (char *)malloc(sizeof(name));

  node->firstChild = temp;
  temp->firstChild = NULL;
  temp->nextSibling = NULL;
  strcpy(temp->path, name);

  return 0;
}

int createSibling(Position node, char * name){
  Position temp = (Position)malloc(sizeof(TreeNode));
  if(temp == NULL){
    return -1;
  }
  
  temp->path = (char *)malloc(sizeof(name));

  while(node->nextSibling != NULL){
    node = node->nextSibling;
  }

  temp->nextSibling = node->nextSibling;
  node->nextSibling = temp;

  temp->firstChild = NULL;
  strcpy(temp->path, name);
  return 0;
} 

int dir(Position node){
  node = node->firstChild;
  while(node != NULL){
    printf("%s\t", node->path);
    node = node->nextSibling;
  }

  return 0;
}

int app(){
  Position root = (Position)malloc(sizeof(TreeNode));
  Position current = (Position)malloc(sizeof(TreeNode));
  
  root->nextSibling = NULL;
  root->firstChild = NULL;
  root->path = "root";
  
  current = root;
  char input[MAX];

  do{
    printf("\n~/%s/\n", current->path);
    gets(input);
    current = handleInput(current, input);

  }while(strcmp(input, "izlaz") != 0);

  printf("Goodbye cruel world");
  return 0;
}

Position handleInput(Position node, char * input){
  char * command, * argument;

  if(strcmp(input, "izlaz") == 0){
    return NULL;
  }

  command = strtok(input, " ");
  argument = strtok(NULL, "\0");
  
  if(strcmp(command, "md") == 0){
    createChild(node, argument);
  }
  else if(strcmp(command, "dir") == 0){
    dir(node);
  }

  return node;
}



