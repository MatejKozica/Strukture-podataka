#include<stdio.h>
#include<stdlib.h>

typedef  struct _node * Position;

typedef struct _node{
  int data;
  Position next;
} Node;

int sortInput(Position head, int flag, int data);
int printList(Position head);
Position listIntersection(Position firstHead, Position secondHead);
Position listUnion(Position firstHead, Position secondHead);

int main(){
  Position head1 = (Position)malloc(sizeof(Node));
  Position head2 = (Position)malloc(sizeof(Node));

  head1->next = NULL;
  head2->next = NULL;

  printf("Prvi niz: \n");
  sortInput(head1, 1, 0);
  sortInput(head1, 1, 0);
  sortInput(head1, 1, 0);
  sortInput(head1, 1, 0);

  printf("Drugi niz: \n");
  sortInput(head2, 1, 0);
  sortInput(head2, 1, 0);
  sortInput(head2, 1, 0);
  sortInput(head2, 1, 0);
  
  printList(head1->next);
  printList(head2->next);

  printf("listIntersection: \n");
  printList(listIntersection(head1->next, head2->next)->next);

  printf("listUnion: \n");
  printList(listUnion(head1->next, head2->next)->next);

  return 0;
}

int sortInput(Position head, int flag, int data){
  Position temp = (Position)malloc(sizeof(Node));
  temp->next = NULL;
  if(temp == NULL){
    return -1;
  }
  
  if(flag == 1){
    int t_data = 0;
    printf("Unesite broj: \n");
    scanf(" %d", &t_data);
    temp->data = t_data;
  }
  else if(flag == 0){
    temp->data = data;
  }
  
  while(head->next != NULL && temp->data > head->next->data){
    head  = head->next;
  }

  temp->next = head->next;
  head->next = temp;

  return 0;
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

Position listIntersection(Position firstHead, Position secondHead){
  Position result = (Position)malloc(sizeof(Node));
  result->next = NULL;

  while(firstHead != NULL){
    if(firstHead->data < secondHead->data){
      firstHead = firstHead->next;
    }
    else if(firstHead->data == secondHead->data){
      sortInput(result, 0, firstHead->data);
      firstHead = firstHead->next;
      secondHead = secondHead->next;
    }
  }

  return result;
}

Position listUnion(Position firstHead, Position secondHead){
  Position result = (Position)malloc(sizeof(Node));
  result->next = NULL;

  while(firstHead != NULL && secondHead != NULL){
    if(firstHead->data < secondHead->data){
      sortInput(result, 0, firstHead->data);
      firstHead = firstHead->next;
    }
    else if(firstHead->data > secondHead->data){
      sortInput(result, 0, secondHead->data);
      secondHead = secondHead->next;
    }
    else if(firstHead->data == secondHead->data){
      sortInput(result, 0, firstHead->data);
      firstHead = firstHead->next;
      secondHead = secondHead->next;
    }
  }

  if(firstHead == NULL){
    while(secondHead != NULL){
      sortInput(result, 0, secondHead->data);
      secondHead = secondHead->next;
    }
  }
  else if(secondHead == NULL){
    while(firstHead != NULL){
      sortInput(result, 0, firstHead->data);
      firstHead = firstHead->next;
    }
  }

  return result;
}