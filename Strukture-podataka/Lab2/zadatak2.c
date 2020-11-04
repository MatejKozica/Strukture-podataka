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
int insertBegin(Node *, int, Node *);
int insertEnd(Node *, int, Node *);
int freeList(Node *);
Node * findSurname(Node *, char *);
Node * findSurnameBefore(Node *, char *);
int deleteNode(Node *, char *);
int insert( Node *);
int scanStudent(Node *);
int countRows(char *);
int readFromFile(char *, Node *);
int writeIntoFile(char *, Node *);
int sortList(Node *);

int main(){
  int counter = 0;
  char name[MAX_LENGTH];
  Node * head = (Node *)malloc(sizeof(Node));
  head->next = NULL;


  readFromFile("input.txt", head);
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

int insertBegin(Node * point, int scanFlag, Node * info){
  Node * newNode = (Node *)malloc(sizeof(Node));
  if(newNode == NULL){
    return -1;
  }
  
  if(scanFlag == 1){
    scanStudent(newNode);
  }
  
  else if(scanFlag == 0){
    newNode->student = info->student;
  }

  newNode->next = point->next;
  point->next = newNode;

  return 0;
}

int insertEnd(Node * point, int scanFlag, Node * info){
  while(point->next != NULL){
    point = point->next;
  }
  
  insertBegin(point, scanFlag, info);

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
  printf("Unesi ime, prezime i godinu rodenja studenta: \n");
  scanf(" %s %s %d", point->student.firstName, point->student.lastName, &point->student.yearOfBirth);
  printf("\n");
  return 0;
}

int countRows(char * file){
  int counter = 0;
  char c;
  FILE * students = fopen(file, "r");

  while((c = fgetc(students)) != EOF){
    if(c == '\n'){
      counter++;
    }
  }

  fclose(students);

  return counter;
}

int readFromFile(char * file, Node * point){
  int rows, i = 0;
  FILE * students = fopen(file, "r");
  rows = countRows(file);
  
  Node * temp = (Node *)malloc(sizeof(Node));

  for(i = 0; i < rows; i++){
    fscanf(students, " %s %s %d", temp->student.firstName, temp->student.lastName, &temp->student.yearOfBirth);
    insertEnd(point, 0, temp);
  }
  
  free(temp);
  fclose(students);
  return 0;
}

int writeIntoFile(char * file, Node * point){
  FILE * students = fopen(file, "w");
  while(point != NULL){
    fprintf(students, "%s %s %d\n", point->student.firstName, point->student.lastName, point->student.yearOfBirth);
    point = point->next;
  }
  return 0;
}


int sortList(Node * point){
  Node * pointer;
  Node * beforePointer;
  Node * temp;
  Node * sorted = NULL;
  
  while(point->next != sorted){
    beforePointer = point;
    pointer = point->next;
    while(pointer->next != sorted){
      if(strcmp(pointer->student.lastName, pointer->next->student.lastName) > 0){
        temp = pointer->next;
        beforePointer->next = temp;
        pointer->next = temp->next;
        temp->next = pointer;
        pointer = temp;
      }
      beforePointer = pointer;
      pointer = pointer->next;
    }
    sorted = pointer;
  }

  return 0;
}