#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _student{
  char firstName[256];
  char lastName[256];
  int yearOfBirth;
  struct _student * next;
} Student;



void printList(Student *);
void insertBegin(Student *);
void insertEnd(Student *);
void freeList(Student *);
Student * findSurname(Student *, char *);
void deleteStudent(Student *, char *);


int main(){
  Student * head = NULL;
  head = (Student *)malloc(sizeof(Student));
  head->next = NULL;
  char * wanted;

  insertEnd(head);
  printList(head);
  insertBegin(head);
  printList(head);
  printf("Unesite prezime studenta kojeg zelite izbrisati: \n");
  scanf("%s", wanted);
  deleteStudent(head, wanted);
  printList(head);

  freeList(head);
  return 0;
}

void printList(Student * point){
  point = point->next;
  while(point != NULL){
    printf("%-15s %-15s %d. \n", point->firstName, point->lastName, point->yearOfBirth);
    point = point->next;
  }
  printf("\n");
}

void insertBegin(Student * point){
  Student * newStudent = (Student *)malloc(sizeof(Student));
  
  printf("Unesi ime, prezime i godinu rodenja studenta: \n");
  scanf(" %s %s %d", newStudent->firstName, newStudent->lastName, &newStudent->yearOfBirth);
  printf("\n");
  
  newStudent->next = point->next;
  point->next =newStudent;
}

void insertEnd(Student * point){
  while(point->next != NULL){
    point = point->next;
  }
  
  Student * newStudent = (Student *)malloc(sizeof(Student));
  
  printf("Unesi ime, prezime i godinu rodenja studenta: \n");
  scanf(" %s %s %d", newStudent->firstName, newStudent->lastName, &newStudent->yearOfBirth);
  printf("\n");
  
  
  newStudent->next = point->next;
  point->next =newStudent;
}

void freeList(Student * point){
  Student * temp;
  point = point->next;
  while(point->next != NULL){
    temp = point;
    point = point->next;
    free(temp);
  }
}

Student * findSurname(Student * point, char * lastName){
  point = point->next;
  while(strcmp(point->lastName, lastName) != 0){
    point = point->next;
  }
  return point;
}

void deleteStudent(Student * point, char * lastName){
  Student * wanted;
  Student * temp;

  wanted = findSurname(point, lastName);
  printf("Deleted student: %s\n", wanted->lastName);
  
  while(point->next != NULL){
    if(strcmp(point->next->lastName, wanted->lastName) == 0){
      temp = point;
      break;
    }
    point = point->next;
  } 

  temp->next = wanted->next;
  free(wanted);
}