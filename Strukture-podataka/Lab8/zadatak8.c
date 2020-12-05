#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct _treeNode * Position;
typedef struct _stackNode * StackPosition;

typedef struct _treeNode{
  Position firstChild;
  Position nextSibling;
  char * path;
}TreeNode;

typedef struct _stackNode{
  Position data;
  StackPosition next;
} StackNode;

//Tree functions
int createChild(Position node, char * name);
int createSibling(Position node, char * name);
int hasChild(Position node);

//Stack functions
int push(StackPosition head, Position node);
Position pop(StackPosition head);
int printStack(StackPosition head);

//App functions
int directory(Position node);
int app();
Position handleInput(Position node, char * input, StackPosition stack, char * path);
Position changeDirectory(Position node, char * input, StackPosition stack, char * path);
Position changeToPreviousDirectory(StackPosition stack, char * path);
int generatePath(char * path, Position node);


int main(){
  app();

  StackPosition head = (StackPosition)malloc(sizeof(StackNode));
  head->next = NULL;

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

int hasChild(Position node){
  if(node->firstChild != NULL){
    return 1;
  }
  return 0;
}

Position changeDirectory(Position node, char * name, StackPosition stack, char * path ){
  push(stack, node);
  node = node->firstChild;
  generatePath(path, node);
  while(node == NULL || strcmp(node->path, name) != 0){
    node = node->nextSibling;
  }

  if(node == NULL){
    printf("That directory doesn't exist");
    return NULL;
  }
  
  return node;
}

int app(){
  Position root = (Position)malloc(sizeof(TreeNode));
  Position current = (Position)malloc(sizeof(TreeNode));
  StackPosition pathStack  = (StackPosition)malloc(sizeof(StackNode));
  
  root->nextSibling = NULL;
  root->firstChild = NULL;
  root->path = "";

  pathStack->next = NULL;

  char * path = (char *)malloc(sizeof(char) * MAX);
  strcpy(path, "");
  
  current = root;
  char input[MAX];

  do{
    printf("\n~/%s\n", path);
    gets(input);
    current = handleInput(current, input, pathStack, path);

  }while(strcmp(input, "exit") != 0);

  printf("Goodbye cruel world");
  return 0;
}

Position handleInput(Position node, char * input, StackPosition stack, char * path){
  char * command, * argument;

  if(strcmp(input, "exit") == 0){
    return NULL;
  }

  command = strtok(input, " ");
  argument = strtok(NULL, "\0");
  
  if(strcmp(command, "md") == 0){
    if(hasChild(node)){
      createSibling(node->firstChild, argument);
    }
    else{
      createChild(node, argument);
    }
  }
  else if(strcmp(command, "dir") == 0){
    dir(node);
  }
  else if(strcmp(command, "cd") == 0){
    if(strcmp(argument, "..") == 0){
      node = changeToPreviousDirectory(stack, path);
    } 
    else if(hasChild(node)){
      node = changeDirectory(node, argument, stack, path);
    }
    else{
      printf("Directory is empty");
    }
  }
  else{
    printf("Command not found");
  }

  return node;
}

int push(StackPosition head, Position node){
  Position tempData = (Position)malloc(sizeof(TreeNode));
  StackPosition temp = (StackPosition)malloc(sizeof(StackNode));
  if(tempData == NULL || temp == NULL){
    return -1;
  }
  
  tempData->path = (char *)malloc(sizeof(node->path));

  tempData->firstChild = node->firstChild;
  tempData->nextSibling = node->nextSibling;
  strcpy(tempData->path, node->path);

  temp->data = tempData;
  
  temp->next = head->next;
  head->next = temp;

  return  0;
}

Position pop(StackPosition head){
  Position wantedNode = head->next->data;
  StackPosition temp;
  temp = head->next;
  head->next = temp->next;
  free(temp);
  return wantedNode;
}

Position changeToPreviousDirectory(StackPosition stack, char * path){
  path = strrev(path);
  char * temp;
  temp = strchr(path, '/');
  *temp = '\0';
  path = strrev(path);

  return pop(stack);
}

int generatePath(char * name, Position node){
  strcat(name, node->path);
  strcat(name, "/");
  return 0;
}