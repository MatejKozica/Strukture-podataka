#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct _student{
  char name[50];
  char surname[50];
  int points;
} Student;

float relativePoints(int);


void main(){
  int counter = 0, i = 0;
  char c;
  Student *students;

  FILE *studentsInfo;
  studentsInfo = fopen("studenti.txt", "r");

  while((c = fgetc(studentsInfo)) != EOF){
    if(c == '\n'){
      counter++;
    }
  }

  students = (Student *)malloc(counter * sizeof(Student));

  rewind(studentsInfo);
  
  for(i = 0; i < counter; i++){
    fscanf(studentsInfo, "%s %s %d", students[i].name, students[i].surname, &students[i].points);
    printf("%-15s %-15s %2d \t %.2f \n", students[i].name, students[i].surname, students[i]. points, relativePoints(students[i].points));
  }

  fclose(studentsInfo);
  free(students);
}

float relativePoints(int points){
  return (float)points / 50 * 100;
}