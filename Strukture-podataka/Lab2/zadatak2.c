#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LENGTH 50

typedef struct _node * Position;

typedef struct _student{
  char firstName[MAX_LENGTH];
  char lastName[MAX_LENGTH];
  int yearOfBirth;
} Student;

typedef struct _node{
  Student student;
  Position next;
} Node;


int printList(Node *);
int insertBegin(Node *);
int insertEnd(Node *);
int freeList(Node *);
Node * findSurname(Node *, char *);
int deleteNode(Node *, char *);


int main(){
  Node * head = (Node *)malloc(sizeof(Node));
  head->next = NULL;

  insertBegin(head);
  printList(head->next);
  insertBegin(head);
  printList(head->next);
  insertEnd(head);
  printList(head->next);
  deleteNode(head, "Tomic");
  printList(head->next);


  freeList(head);
  return 0;
}

int printList(Node * point){
  
  while(point != NULL){
    printf("%-15s %-15s %d. \n", point->student.firstName, point->student.lastName, point->student.yearOfBirth);
    point = point->next;
  }
  printf("\n");
  return 0;
}

int insertBegin(Node * point){
  Node * newNode = (Node *)malloc(sizeof(Node));
  if(newNode == NULL){
    return -1;
  }
  
  printf("Unesi ime, prezime i godinu rodenja studenta: \n");
  scanf(" %s %s %d", newNode->student.firstName, newNode->student.lastName, &newNode->student.yearOfBirth);
  printf("\n");
  
  newNode->next = point->next;
  point->next = newNode;

  return 0;
}

int insertEnd(Node * point){
  while(point->next != NULL){
    point = point->next;
  }
  
  insertBegin(point);

  return 0;
}

int freeList(Node * point){
  Node * temp;
  while(point->next != NULL){
    temp = point;
    point = point->next;
    free(temp);
  }
  return 0;
}

Node * findSurname(Node * point, char * lastName){
  while(strcmp(point->student.lastName, lastName) != 0){
    point = point->next;
  }
  return point;
}

int deleteNode(Node * point, char * lastName){
  Node * wanted;
  Node * temp;

  wanted = findSurname(point, lastName);
  printf("Deleted student: %s\n", wanted->student.lastName);
  
  while(point->next != NULL){
    if(strcmp(point->next->student.lastName, wanted->student.lastName) == 0){
      temp = point;
      break;
    }
    point = point->next;
  } 

  temp->next = wanted->next;
  free(wanted);
  return 0;
}