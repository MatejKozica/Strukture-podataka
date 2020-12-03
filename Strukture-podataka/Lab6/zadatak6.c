#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _node * Position;


typedef struct _node{
  int data;
  Position next;
} Node;

int push(Position head);
int pop(Position head);
int printList(Position head);
int add(Position head);

int main(){
  Position stackHead = (Position)malloc(sizeof(Node));
  stackHead->next = NULL;
  Position queueHead = (Position)malloc(sizeof(Node));
  queueHead->next = NULL;

  push(stackHead);
  push(stackHead);
  push(stackHead);
  push(stackHead);
  printList(stackHead->next);
  pop(stackHead);
  printList(stackHead->next);
  printf("\n===========\n");
  add(queueHead);
  printList(queueHead->next);
  add(queueHead);
  add(queueHead);
  printList(queueHead->next);
  pop(queueHead);
  printList(queueHead->next);

  return 0;
}

int push(Position head){
  int upper = 100;
  int lower = 10;
  Position temp = (Position)malloc(sizeof(Node));
  
  int num = (rand() % (upper - lower + 1)) + lower;
  temp->data = num;
  
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

int add(Position head){
  while(head->next != NULL){
    head = head->next;
  }
  push(head);
  return 0;
}