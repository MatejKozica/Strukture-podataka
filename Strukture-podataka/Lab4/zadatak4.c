#include<stdio.h>
#include<stdlib.h>

typedef struct _node * Position;

typedef struct _polynome{
  int power;
  int coefficient;
} Polynome;

typedef struct _node{
  Polynome data;
  Position next;
} Node;

int readFromFile(char * file, Position first, Position second);
int insert(Position point, int coefficient, int power);
int printList(Position point);
Position sumPolynome(Position first, Position second);
int copyList(Position first, Position second);
Position multiplyPolynome(Position first, Position second);
int freeList(Node * point);

int main(){
  Position head1 = (Position)malloc(sizeof(Node));
  Position head2 = (Position)malloc(sizeof(Node));
  Position head3 = (Position)malloc(sizeof(Node));
  
  head1->next = NULL;
  head2->next = NULL;
  head3->next = NULL;

  readFromFile("input.txt", head1, head2);
  
  printList(head1->next);
  printList(head2->next);
  printf("\n\nMultiply result:\n");
  printList(multiplyPolynome(head1->next, head2->next)->next);
 
  return 0;
}

int readFromFile(char * file, Position firstHead, Position secondHead){
  FILE * openedFile = fopen(file, "r");
  char c;
  int coefficient = 0, power = 0;
  Position tempHead = firstHead;
  
  while(!feof(openedFile)){
    fscanf(openedFile, "%d %d", &coefficient, &power);
    insert(tempHead, coefficient, power);
    if((c=fgetc(openedFile)) == '\n'){
      tempHead = secondHead;
    }
  }

  fclose(openedFile);
}

int insert(Position point, int coefficient, int power){
  Position newNode = (Position)malloc(sizeof(Node));
  if(newNode == NULL){
    return -1;
  }

  newNode->data.coefficient = coefficient;
  newNode->data.power = power;

  while(point->next != NULL && newNode->data.power < point->next->data.power){
    point = point->next;
  }

  newNode->next = point->next;
  point->next = newNode;

  return 0;
}

int printList(Position point){
  if(point == NULL){
    printf("List is empty");
  }
  while(point != NULL){
    printf("%dx%d\t", point->data.coefficient, point->data.power);
    point = point->next;
  }
  printf("\n");
  return 0;
}

Position sumPolynome(Position first, Position second){
  Position result = (Position)malloc(sizeof(Node));
  result->next = NULL;

  while(first != NULL && second != NULL){
    if(first->data.power == second->data.power){
      insert(result, first->data.coefficient + second->data.coefficient, first->data.power);
      first = first->next;
      second = second->next;
     
    }
    else if(first->data.power < second->data.power){
      insert(result, second->data.coefficient, second->data.power);
      second = second->next;
    }
    else if(first->data.power > second->data.power){
      insert(result, first->data.coefficient, first->data.power);
      first = first->next;
    }
  }
  if(first == NULL){
    while(second != NULL){
      insert(result, second->data.coefficient, second->data.power);
      second = second->next;
    }
  }
  
  else if(second == NULL){
    while(first != NULL){
      insert(result, first->data.coefficient, first->data.power);
      first = first->next;
    }
  }

  return result;
}

int copyList(Position first, Position second){
  while(first != NULL){
    insert(second, first->data.coefficient, first->data.power);
    first = first->next;
  }
  return 0;
}

Position multiplyPolynome(Position first, Position second){
  Position result = (Position)malloc(sizeof(Node));
  result->next = NULL;

  Position resultHead = result;
  Position secondHead = second;

  while(first != NULL){
    Position temp= (Position)malloc(sizeof(Node));
    temp->next = NULL;
    while(second != NULL){
      insert(temp, first->data.coefficient * second->data.coefficient, first->data.power + second->data.power);
      second  = second->next;
    }
    result = sumPolynome(result->next, temp->next);
    freeList(temp);
    
    first = first->next;
    second = secondHead;
  }

  return result;
}

int freeList(Position point){
  Position pointHead = point;
  Position temp;
  while(point != NULL){
    temp = point;
    point = point->next;
    free(temp);
  }
  pointHead->next = NULL;
  return 0;
}