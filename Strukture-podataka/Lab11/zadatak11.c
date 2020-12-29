#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

typedef struct _node * Position;
typedef struct _hashTable * HashPos;

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
  int tableSize;
  Position * hashLists;
}HashTable;

HashPos initialize(int size);
int add(HashPos table, char * name, char * surname, int id);
int hash(char * key, int size);
int printList(Position point);
int search(HashPos table);
int insertIntoList(Position head, Position data);

int main(){
  HashPos table = initialize(11);
  add(table, "Matej", "Kozica", 1);
  add(table, "Tonino", "Kastelan", 2);
  add(table, "Ivan", "Tomic", 3);
  add(table, "Roko", "Radanovic", 4);
  /* printf("%d", search(table)); */

  int i = 0;

  for(i = 0; i < 11; i++){
    printf("%d\n", i+1);
    printList(table->hashLists[i]);
  }

  return 0;
}

HashPos initialize(int size){
  HashPos temp = (HashPos)malloc(sizeof(HashTable));
  int i = 0;
  
  if(temp == NULL){
    return NULL;
  }

  temp->tableSize = size;
  temp->hashLists = (Position *)malloc(sizeof(Position)*temp->tableSize);
  if(temp->hashLists == NULL){
    return NULL;
  }

  for(i = 0; i < temp->tableSize; i++){
    temp->hashLists[i] = NULL;
  }

  return temp;
}

int add(HashPos table, char * name, char * surname, int id){
  Position temp = (Position)malloc(sizeof(Node));
  int index = hash(surname, table->tableSize);
  
  if(temp == NULL){
    return 1;
  }

  temp->data.id = id;
  strcpy(temp->data.name, name);
  strcpy(temp->data.surname, surname);

/*   insertIntoList(table->hashLists[index], temp); */


  temp->next = table->hashLists[index];
  table->hashLists[index] = temp;
  return 0;
}

int insertIntoList(Position head, Position data){
  data->next = head;
  head = data;

  return 0;
}

int hash(char * key, int size){
  int a = 0, i = 0;
  for(i = 0; i<5;i++){
    a += key[i];
  }

  return a % size;
}

int printList(Position point){
  if(point == NULL){
    return 1;
  }
  
  while(point != NULL){
    printf("%-15s %-15s %d\n", point->data.name, point->data.surname, point->data.id);
    point = point->next;
  }
  printf("\n");
  return 0;
}

int search(HashPos table){
  char name[MAX];
  char surname[MAX];
  Position temp = (Position)malloc(sizeof(Node));

  printf("Unesite ime i prezime: ");
  scanf("%s %s", name, surname);
  int index = hash(surname, table->tableSize);
  temp = table->hashLists[index];

  while(temp != NULL){
    if(strcmp(temp->data.name, name) == 0 && strcmp(temp->data.surname, surname) == 0){
      return temp->data.id;
    }
    temp = temp->next;
  }
  
  return 0;
}