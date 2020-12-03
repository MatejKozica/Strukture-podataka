#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 50

typedef struct _node * Position;


typedef struct _node{
  int data;
  Position next;
} Node;

int push(Position head, float data);
int pop(Position head);
int printList(Position head);
int openFile(char * file, char * expression);
float calculate(Position head, char * expression);
int operation(Position head, char operation);

int main(){
  Position stackHead = (Position)malloc(sizeof(Node));
  stackHead->next = NULL;
  char expression[MAX];
  openFile("input.txt", expression);
  printf("%0.1f", calculate(stackHead, expression));


  return 0;
}

int push(Position head, float data){
  Position temp = (Position)malloc(sizeof(Node));
  if(temp == NULL){
    return 1;
  }
  temp->data = data;
  
  temp->next = head->next;
  head->next = temp;

  return  0;
}

int printList(Position head){
  if(head == NULL){
    printf("List is empty");
    return -1;
  }
  while(head != NULL){
    printf("%d\t", head->data);
    head = head->next;
  }
  printf("\n");

  return 0;
}

int pop(Position head){
  int data = head->next->data;
  Position temp;
  temp = head->next;
  head->next = temp->next;
  free(temp);
  return data;
}

int openFile(char * file, char * expression){
  FILE * data = fopen(file, "r");

  fgets(expression, MAX, data);
  fclose(data);
  return 0;
}

float calculate(Position head, char * expression){
  char * current;
  
  current = strtok(expression, " ");
  while(current != NULL){
    if(isdigit(*current))
      push(head, atoi(current));
  
    else
      operation(head, *current);

    current = strtok(NULL, " ");  
  }

  return pop(head);
}

int operation(Position head, char c){
  int a = pop(head);
  int b = pop(head);
  switch (c)
  {
    case '+':
      push(head, a + b);
      break;
    case '-':
      push(head, b - a);
      break;
    case '*':
      push(head, a * b);
      break;
    case '/':
      push(head, b / a);
      break;      
    default:
      break;
  }
  return 0;
}