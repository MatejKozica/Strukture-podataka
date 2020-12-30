#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

typedef struct _node * Position;
typedef struct _hashTable * HashPosition;

typedef struct _student{
  char name[MAX];
  char surname[MAX];
  int id;
}Student;

typedef struct _node{
  Student data;
  Position next;
}Node;

typedef struct _hashTable{
  int size;
  Position * list;
}HashTable;

int printList(Position point);
int sortInput(Position point, char * name, char * surname, int id);
HashPosition createTable(int size);
int hash(char * key, int size);
int add(HashPosition table, char * name, char * surname, int id);
int search(HashPosition table);
int printTable(HashPosition table);

int main(){
  HashPosition table = createTable(11);
  add(table, "Ivan", "Tomic", 4);
  add(table, "Roko", "Radanovic", 1);
  add(table, "Matej", "Kozica", 2);
  add(table, "Tonino", "Kastelan", 3);
  printf("%d\n", search(table));
  printTable(table);

  return 0;
}

int printList(Position point){
  if(point == NULL){
    return 1;
  }
  
  while(point != NULL){
    printf("%-15s %-15s %d\n", point->data.surname, point->data.name, point->data.id);
    point = point->next;
  }
  printf("\n");

  return 0;
}

int sortInput(Position point, char * name, char * surname, int id){
  Position temp = (Position)malloc(sizeof(Node));

  if(temp == NULL){
    return 1;
  }

  if(point == NULL){
    printf("Invalid head");
    return 1;
  }
  
  temp->data.id = id;
  strcpy(temp->data.name, name);
  strcpy(temp->data.surname, surname);

  while(point->next != NULL && 
        (strcmp(surname, point->next->data.surname) > 0 || (strcmp(surname, point->next->data.surname) == 0 && strcmp(name, point->next->data.name) > 0)))
  {
    point = point->next;
  }

  temp->next = point->next;
  point->next = temp;

  return 0;
}

HashPosition createTable(int size){
  HashPosition temp = (HashPosition)malloc(sizeof(HashTable));
  temp->size = size;

  if(temp == NULL){
    return NULL;
  }

  temp->list = (Position *)malloc(sizeof(Position)*size);

  if(temp->list == NULL){
    return NULL;
  }

  int i = 0;

  for(i = 0; i < size; i++){
    temp->list[i] = (Position)malloc(sizeof(Node));
    temp->list[i]->next = NULL;
  }

  return temp;
}

int hash(char * key, int size){
  int a = 0, i = 0;
  for(i = 0; i < 5; i++){
    a += key[i];
  }

  return a % size;
}

int add(HashPosition table, char * name, char * surname, int id){
  int index = hash(surname, table->size);
  sortInput(table->list[index], name, surname, id);

  return 0;
}

int search(HashPosition table){
  char name[MAX];
  char surname[MAX];
  
  printf("Unesite ime i prezime: ");
  scanf("%s %s", name, surname);

  int index = hash(surname, table->size);

  Position temp = table->list[index];

  while(temp != NULL){
    if(strcmp(temp->data.name, name) == 0 && strcmp(temp->data.surname, surname) == 0){
      return temp->data.id;
    }
    temp = temp->next;
  }
  
  return 0;
}

int printTable(HashPosition table){
  int i = 0;

  for(i = 0; i < table->size; i++){
    printf("%d\n", i+1);
    printList(table->list[i]->next);
  }

  return 0;
}