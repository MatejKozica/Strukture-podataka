#pragma once

#define MAX_LENGTH 50
#ifndef MATEJ
#define MATEJ

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
Node * findSurnameBefore(Node *, char *);
int deleteNode(Node *, char *);
int insert( Node *);
int scanStudent(Node *);

#endif