#include <stdio.h>
#include <stdlib.h>

typedef struct _node * Position;


typedef struct _node{
  int data;
  Position next;
} Node;

int push(Position head, float data);
int pop(Position head);
int printList(Position head);

int main(){
  Position stackHead = (Position)malloc(sizeof(Node));
  stackHead->next = NULL;
  char c, d;
  int a, b;

  scanf(" %c", &c);
  while(c != 'k'){
    if(c >= 48 && c <=57){
      float num = c - '0';
      push(stackHead, num);
    }
    
    else{
      switch (c)
      {
        case '+':
          a = pop(stackHead);
          b = pop(stackHead);
          push(stackHead, a + b);
          break;
        case '-':
          a = pop(stackHead);
          b = pop(stackHead);
          push(stackHead, b - a);
          break;
        case '*':
          a = pop(stackHead);
          b = pop(stackHead);
          push(stackHead, b*a);
          break;
        case '/':
          a = pop(stackHead);
          b = pop(stackHead);
          push(stackHead, b/a);
          break;
        default:
          break;
      }
    }
    scanf("%c", &c);
  }
  printList(stackHead->next);

  return 0;
}

int push(Position head, float data){
  Position temp = (Position)malloc(sizeof(Node));
  if(temp == NULL){
    return 1;
  }
  temp->data = data;
  
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
