#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct student {
  char name[100];
  char lesson[100];
  int grade;
};

void addStudent(struct student s[], int * totalStudents) {
  printf("Enter student name: ");
  scanf("%s", s[ * totalStudents].name);
  printf("Enter student's lesson: ");
  scanf("%s", s[ * totalStudents].lesson);
  printf("Enter student's grade: ");
  scanf("%d", & s[ * totalStudents].grade);
  ( * totalStudents) ++;
}

void writeToFile(struct student s[], int totalStudents) {
  FILE * fp;
  fp = fopen("students.txt", "w");
  if (fp == NULL) {
    printf("File could not be opened\n");
    return;
  }
  int i;
  for (i = 0; i < totalStudents; i++) {
    fprintf(fp, "%s %s %d\n", s[i].name, s[i].lesson, s[i].grade);
  }
  fclose(fp);
  printf("Data written to file\n");
}

int main() {
  struct student students[100];
  int totalStudents = 0;
  int choice;
  do {
    printf("1- Add a student\n");
    printf("2- Write data to file\n");
    printf("3- Exit\n");
    printf("Enter your choice: ");
    scanf("%d", & choice);
    switch (choice) {
    case 1:
      addStudent(students, & totalStudents);
      break;
    case 2:
      writeToFile(students, totalStudents);
      break;
    case 3:
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
  } while (choice != 3);
  return 0;
}