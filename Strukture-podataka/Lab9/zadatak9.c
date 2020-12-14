#include<stdio.h>
#include<stdlib.h>

typedef struct _node * Position;

typedef struct _node{
  int data;
  Position leftChild;
  Position rightChild;
} Node;

Position add(Position point, int data);
int printTree(Position point);
Position find(Position point, int data);
int freeAll(Position point);
Position findMin(Position point);
Position findMax(Position point);
Position deleteNode(Position point, int data);

int main(){
  Position root = NULL;
  Position wanted = NULL;
  root = add(root, 6);
  add(root, 2);
  add(root, 8);
  add(root, 1);
  add(root, 5);
  add(root, 3);
  add(root, 4);
  printTree(root);

  printf("Min: %d\n", findMin(root)->data);
  printf("Max: %d\n", findMax(root)->data);

  deleteNode(root, 2);
  printTree(root);

  freeAll(root);
  return 0;
}

Position add(Position point, int data){
  if(point == NULL){
    point = (Position)malloc(sizeof(Node));
    point->data = data;
    point->leftChild = NULL;
    point->rightChild = NULL;
  }
  
  else if(data < point->data){
    point->leftChild = add(point->leftChild, data);
  }
  
  else if(data > point->data){
    point->rightChild = add(point->rightChild, data);
  }

  return point;
}

int printTree(Position point){
  if(point == NULL){
    return 1;
  }
  
  printf("%d\n", point->data);

  printTree(point->leftChild);
  printTree(point->rightChild);

  return 0;
}

Position find(Position point, int data){
  if(point == NULL){
    return NULL;
  }

  else if(data < point->data){
    return find(point->leftChild, data);
  }

  else if(data > point->data){
    return find(point->rightChild, data);
  }

  return point;
}

int freeAll(Position point){
  if(point == NULL){
    return 1;
  }
  freeAll(point->leftChild);
  freeAll(point->rightChild);
  free(point);

  return 0;
}

Position findMin(Position point){
  if(point == NULL){
    return NULL;
  }

  if(point->leftChild == NULL){
    return point;
  } 

  return findMin(point->leftChild);
}

Position findMax(Position point){
  if(point == NULL){
    return NULL;
  }

  else if(point->rightChild == NULL){
    return point;
  } 

  return findMax(point->rightChild);
}

Position deleteNode(Position point, int data){
  if(point == NULL){
    return NULL;
  }

  else if(data < point->data){
    point->leftChild = deleteNode(point->leftChild, data);
  }

  else if(data > point->data){
    point->rightChild = deleteNode(point->rightChild, data);
  }

  else if(point->leftChild != NULL && point->rightChild != NULL){
    Position temp = findMin(point->rightChild);
    point->data = temp->data;
    point->rightChild = deleteNode(point->rightChild, point->data);
  }

  else{
    Position temp = point;
    if(point->leftChild == NULL){
      point = point->rightChild;
    } 
    else{
      point = point->leftChild;
    }
    free(temp);
  }
  return point;
}