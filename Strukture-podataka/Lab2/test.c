#include<stdlib.h>
#include "test.h"

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
  
  scanStudent(newNode);
  
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

Node * findSurnameBefore(Node * point, char * lastName){
  while(strcmp(point->next->student.lastName, lastName) != 0){
    point = point->next;
  }
  return point;
}

Node * findSurname(Node * point, char * lastName){
  return findSurnameBefore(point, lastName)->next;
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

int insert(Node * wanted){
  Node * newNode = (Node *)malloc(sizeof(Node));
  if(newNode == NULL){
    return -1;
  }
  Node * temp;
  scanStudent(newNode);
  
  temp = wanted->next;
  wanted->next = newNode;
  newNode->next = temp;

  return 0;
}

int scanStudent(Node * point){