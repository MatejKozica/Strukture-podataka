#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

typedef struct _node * Position;
typedef struct _stackNode * StackPosition;

typedef struct _node{
  char * data;
  Position leftChild;
  Position rightChild;
} Node;

typedef struct _stackNode{
  Position data;
  StackPosition next;
} StackNode;

//Tree functions
Position createNode(char * data);
int printInOrder(Position point);

//Stack functions
int push(StackPosition point, Position data);
int printStack(StackPosition point);
Position pop(StackPosition point);

int openFile(char * name, char * expression);
StackPosition createTree(char * expression);
int writeInFile(Position point, FILE * output);

int main(){
  char expression[MAX];
  openFile("input.txt", expression);
  StackPosition expressionTree = createTree(expression);
  printInOrder(expressionTree->next->data);
  FILE * output = fopen("output.txt", "w");
  writeInFile(expressionTree->next->data, output);
  fclose(output);

  return 0;
}

Position createNode(char * data){
  Position point = (Position)malloc(sizeof(Node));
  point->leftChild = NULL;
  point->rightChild = NULL;
  
  point->data = (char *)malloc(sizeof(data));
  strcpy(point->data, data);

  return point;
}

int printInOrder(Position point){
  if(point == NULL){
    return 1;
  }
  
  if(*point->data == '*' || *point->data == '/'){
    printf("(");
    printInOrder(point->leftChild);
    printf(" %s ", point->data);
    printInOrder(point->rightChild);
    printf(")");
  }
  else{
    printInOrder(point->leftChild);
    printf(" %s ", point->data);
    printInOrder(point->rightChild);
  }

  return 0;
}

int push(StackPosition point, Position data){
  StackPosition temp = (StackPosition)malloc(sizeof(StackNode));

  if(temp == NULL){
    return 1;
  }

  temp->data = data;
  temp->next = point->next;
  point->next = temp;

  return 0;
}

int printStack(StackPosition point){
  if(point == NULL){
    printf("List is empty");
    return 1;
  }

  while(point != NULL){
    printInOrder(point->data);
    point = point->next;
  }
  printf("\n");

  return 0;
}

Position pop(StackPosition point){
  Position data = point->next->data;
  StackPosition temp;
  temp = point->next;
  point->next = temp->next;
  free(temp);
  return data;
}

int openFile(char * name, char * expression){
  FILE * input = fopen(name, "r");
  fgets(expression, MAX, input);
  fclose(input);
  return 0;
}

StackPosition createTree(char * expression){
  StackPosition stackHead = (StackPosition)malloc(sizeof(StackNode));
  stackHead->next = NULL;

  char *ptr  = expression;
  char current[MAX];
  int n;
  while(sscanf(ptr, "%s %n", current, &n) == 1){
    if(*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr== '/'){
      Position temp = createNode(current);
      Position a = pop(stackHead);
      Position b = pop(stackHead);
      temp->leftChild = b;
      temp->rightChild = a;
      push(stackHead, temp);
    }
    else{
      Position temp = createNode(current);
      push(stackHead, temp);
    }

    ptr +=n;
    --ptr;
    if(*ptr != ' '){
      break;
    }
    ++ptr;
  }
  printf("\n");
  return stackHead;
}

int writeInFile(Position point, FILE * output){
  if(point == NULL){
    return 1;
  }
  
  if(*point->data == '*' || *point->data == '/'){
    fprintf(output, "(");
    writeInFile(point->leftChild, output);
    fprintf(output, "%s ", point->data);
    writeInFile(point->rightChild, output);
    fprintf(output, ")");
  }

  else{
    writeInFile(point->leftChild, output);
    fprintf(output, "%s ", point->data);
    writeInFile(point->rightChild, output);
  } 

  return 0;
}