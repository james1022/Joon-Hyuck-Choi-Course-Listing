/*
 * Homework4, 600.120 Spring 2015
 * testList.c
 * Name: Joon Hyuck Choi
 * Date: Mar 11, 2015
 * Assignment 4 Checkpoint
 * Phone: 667-239-0288
 * BB login: jchoi100
 * email: jchoi100@jhu.edu
 * Updated: 20:07 03/11/2015
 */

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

/**
 * Copied over from HW2 sample file.
 * Reads lhs and rhs character by character until either reaches eof.
 * Returns true if the files can be read and the two files match
 * character by character. Returns false if two files either can't be
 * opened or don't match.
 */
bool fileeq(char lhsName[], char rhsName[]) {
    FILE* lhs = fopen(lhsName, "r");
    FILE* rhs = fopen(rhsName, "r");

    // don't compare if we can't open the files
    if (!lhs || !rhs) return false;

    bool match = true;
    // read until both of the files are done or there is a mismatch
    while (!feof(lhs) || !feof(rhs)) {
        if (feof(lhs) ||                  // lhs done first
            feof(rhs) ||                  // rhs done first
            (fgetc(lhs) != fgetc(rhs))) { // chars don't match
            match = false;
            break;
        }
    }
    fclose(lhs);
    fclose(rhs);
    return match;
} //end fileeq()

/**
 * Tests the add function in list.c
 */
void testAdd(FILE* dataBase) {

  //TEST1
  FILE* testAddFile = fopen("testAddFile.txt", "w");
  FILE* expectedAddFile = fopen("expectedAddFile.txt", "w");

  Node* head = NULL;
  Node* newNode = 0;
  newNode = malloc(sizeof(Node));
  add(&head, '6', '0', '0', '1', '2', '0', 'A', '+', &newNode, dataBase);
  char newLine = '\n';

  fprintf(testAddFile, "EN.%c%c%c.%c%c%c %c.%c %s %c%c%c", head->cStruct.dept1, 
	  head->cStruct.dept2, head->cStruct.dept3, head->cStruct.class1, 
	  head->cStruct.class2, head->cStruct.class3, head->cStruct.wCredit, 
	  head->cStruct.dCredit, head->cStruct.className, 
	  head->cStruct.letterGrade, head->cStruct.gradeSign, newLine);

  fclose(testAddFile);

  fprintf(expectedAddFile, "EN.600.120 4.0 Intro to Java A+\n");
  fclose(expectedAddFile);
  assert(fileeq("testAddFile.txt", "expectedAddFile.txt"));
  free(newNode);
} //end testAdd()

/**
 * Test the remove function in list.c
 */
void testRemove(FILE* dataBase) {

  //TEST1
  FILE* testRemFile = fopen("testRemFile.txt", "w");
  FILE* expectedRemFile = fopen("expectedRemFile.txt", "w");

  Node* head = NULL;
  Node* newNode = 0;
  newNode = malloc(sizeof(Node));
  add(&head, '6', '0', '0', '1', '2', '0', 'A', '+', &newNode, dataBase);
  removeC(&head, '6', '0', '0', '1', '2', '0');

  char nullchar = '\0';

  if (head == NULL) {
    fprintf(testRemFile, "%c", nullchar);
  } else {
    fprintf(testRemFile, "%c%c%c%c%c%c%c%c%c%c", head->cStruct.dept1, 
	    head->cStruct.dept2, head->cStruct.dept3, head->cStruct.class1, 
	    head->cStruct.class2, head->cStruct.class3, head->cStruct.wCredit, 
	    head->cStruct.dCredit, head->cStruct.letterGrade, head->cStruct.gradeSign);
  }
  fclose(testRemFile);

  fprintf(expectedRemFile, "%c", nullchar);
  fclose(expectedRemFile);
  assert(fileeq("testRemFile.txt", "expectedRemFile.txt"));

} //end testRemove()

/**
 * This function was directly copied from the list.c
 * that I wrote with the purpose of minor modification.
 * The modification serves to print the list in a file,
 * not on stdout as in the original function.
 * This function takes in a semester's linked list
 * and prints out all the courses in order.
 */
void displaySemester2(FILE* tester, Node* ary) {

  Node* current;

  if (ary == NULL) {
    fprintf(stderr, "No courses this semester.\n");
    return;
  } else {
    current = ary;
    while (current != NULL) {
      fprintf(tester, "EN.%c%c%c.%c%c%c %c.%c %s %c%c\n", current->cStruct.dept1, 
	      current->cStruct.dept2, current->cStruct.dept3, current->cStruct.class1, 
	      current->cStruct.class2, current->cStruct.class3, current->cStruct.wCredit, 
	      current->cStruct.dCredit, current->cStruct.className, 
	      current->cStruct.letterGrade, current->cStruct.gradeSign);
      current = current->next;
    }
  }

} //end displaySemester()

/**
 * Tests the displaySemester function.
 */
void testDisplaySemester(FILE* dataBase) {

 //TEST1
  FILE* testSemFile = fopen("testSemFile.txt", "w");
  FILE* expectedSemFile = fopen("expectedSemFile.txt", "w");

  Node* head = NULL;
  Node* newNode = 0;
  newNode = malloc(sizeof(Node));
  add(&head, '6', '0', '0', '1', '2', '0', 'A', '+', &newNode, dataBase);
  
  displaySemester2(testSemFile, head);
  fclose(testSemFile);

  fprintf(expectedSemFile, "EN.600.120 4.0 Intro to Java A+\n");
  fclose(expectedSemFile);
  assert(fileeq("testSemFile.txt", "expectedSemFile.txt"));
  free(newNode);

} //end testDisplaySemester()

/**
 * This function was directly copied from the list.c
 * that I wrote for the same reason as the function above.
 * This function takes in the whole data structure of 
 * all 10 semesters' linked lists and creates a long 
 * list of courses in a sorted fashion.
 * Once it's looked at all the values, it prints the list.
 */
void displayAll2(FILE* tester, Node** const ary) {

  Node* temp;
  int pos = 0;
  Node* copiedList;
  int initialSize = 20;
  copiedList = malloc(initialSize * sizeof(Node));

  for (int i = 0; i < 2; i++) {
    if (*(ary + i) != NULL) {
      temp = *(ary + i);

      while (temp != NULL) {

	Node course;
	course.cStruct.dept1 = temp->cStruct.dept1;
	course.cStruct.dept2 = temp->cStruct.dept2;
	course.cStruct.dept3 = temp->cStruct.dept3;

	course.cStruct.class1 = temp->cStruct.class1;
	course.cStruct.class2 = temp->cStruct.class2;
	course.cStruct.class3 = temp->cStruct.class3;

	course.cStruct.wCredit = temp->cStruct.wCredit;
	course.cStruct.dCredit = temp->cStruct.dCredit;

	strcpy(course.cStruct.className, temp->cStruct.className);

	course.cStruct.letterGrade = temp->cStruct.letterGrade;
	course.cStruct.gradeSign = temp->cStruct.gradeSign;

	if (pos >= initialSize) {
	  initialSize *= 2;
	  copiedList = realloc(copiedList, initialSize * sizeof(Node));
	}
	copiedList[pos++] = course;
	temp = temp->next;

      } //end while

    } //end if the semester is not null

  } //end for iterate through each semester

  Node a;

  int valI = 0;
  int valJ = 0;

  for (int i = 0; i < pos; i++) {

    for (int j = i + 1; j < pos; j++) {

      valI = copiedList[i].cStruct.dept1 * 100000 + copiedList[i].cStruct.dept2 * 10000 + 
	copiedList[i].cStruct.dept3 * 1000 + copiedList[i].cStruct.class1 * 100 + 
	copiedList[i].cStruct.class2 * 10 + copiedList[i].cStruct.class3;

      valJ = copiedList[j].cStruct.dept1 * 100000 + copiedList[j].cStruct.dept2 * 10000 
	+ copiedList[j].cStruct.dept3 * 1000 + copiedList[j].cStruct.class1 * 100 
	+ copiedList[j].cStruct.class2 * 10 + copiedList[j].cStruct.class3;

      if (valI > valJ) {
	a = copiedList[i];
	copiedList[i] = copiedList[j];
	copiedList[j] = a;
      } else if (valI == valJ) {
	copiedList[j] = copiedList[pos - 1];
	pos--;
      }

    }

  }

  for (int i = 0; i < pos; i++) {
    fprintf(tester, "EN.%c%c%c.%c%c%c %c.%c %s %c%c\n", copiedList[i].cStruct.dept1, 
	    copiedList[i].cStruct.dept2, copiedList[i].cStruct.dept3, 
	    copiedList[i].cStruct.class1, copiedList[i].cStruct.class2, 
	    copiedList[i].cStruct.class3, copiedList[i].cStruct.wCredit, 
	    copiedList[i].cStruct.dCredit, copiedList[i].cStruct.className, 
	    copiedList[i].cStruct.letterGrade, copiedList[i].cStruct.gradeSign);
  }
 
  if (pos == 0) {
    fprintf(stderr, "There are no courses in any of the semesters.\n");
  }

  free(copiedList);

} //end displayAll()

/**
 * Tests the displayAll function.
 */
void testDisplayAll(FILE* dataBase) {

  //TEST1
  Node* head1 = NULL;
  Node* head2 = NULL;
  Node* listptr[2] = {head1, head2};

  Node* newNode1 = 0;
  newNode1 = malloc(sizeof(Node));
  Node* newNode2 = 0;
  newNode2 = malloc(sizeof(Node));

  add(&head1, '6', '0', '0', '1', '2', '0', 'A', '+', &newNode1, dataBase);
  add(&head2, '6', '0', '0', '1', '2', '0', 'A', '+', &newNode2, dataBase);

  FILE* testAllFile = fopen("testAllFile.txt", "w");
  displayAll2(testAllFile, listptr);
  fclose(testAllFile);

  FILE* expectedAllFile = fopen("expectedAllFile.txt", "w");
  fprintf(expectedAllFile, "EN.600.120 4.0 Intro to Java A+\n");
  fclose(expectedAllFile);

  assert(fileeq("testAllFile.txt", "expectedAllFile.txt"));
  free(newNode1);
  free(newNode2);

} //end testDisplayAll()

/**
 * This function was directly copied from the list.c
 * that I wrote with the purpose of minor modification.
 * The modification serves to print the list in a file,
 * not on stdout as in the original function.
 */
void displayDataBase2(FILE* dataBase5, FILE* tester) {

  fseek(dataBase5, 0, SEEK_SET);
  char c41 = 0, c42 = 0;
  char d41 = 0, d42 = 0, d43 = 0;
  char n41 = 0, n42 = 0, n43 = 0;
  char div41 = 0, div42 = 0;
  char title4[31];

  printf("\n");

  for (int i = 0; i < 560000; i++) { 
    fread(&div41, sizeof(char), 1, dataBase5);
    fread(&div42, sizeof(char), 1, dataBase5);
    fseek(dataBase5, 1, SEEK_CUR);
    fread(&d41, sizeof(char), 1, dataBase5);
    fread(&d42, sizeof(char), 1, dataBase5);
    fread(&d43, sizeof(char), 1, dataBase5);
    fseek(dataBase5, 1, SEEK_CUR);
    fread(&n41, sizeof(char), 1, dataBase5);
    fread(&n42, sizeof(char), 1, dataBase5);
    fread(&n43, sizeof(char), 1, dataBase5);
    fseek(dataBase5, 1, SEEK_CUR);
    fread(&c41, sizeof(char), 1, dataBase5);
    fseek(dataBase5, 1, SEEK_CUR);
    fread(&c42, sizeof(char), 1, dataBase5);
    fseek(dataBase5, 1, SEEK_CUR);
    fread(title4, sizeof(char), 31, dataBase5);
    fseek(dataBase5, 1, SEEK_CUR);

    if (d41 == '0' && d42 == '0' && d43 == '0') {
      //this is when the entry is emtpy
      continue;
    } else {
      fprintf(tester, "%c%c.%c%c%c.%c%c%c %c.%c %s", div41, div42, d41, d42, d43, 
	     n41, n42, n43, c41, c42, title4);
      fprintf(tester, "\n");
    } //end if-else

  } //end for

} //end displayDataBase2()

/**
 * Test two functions at once. The createOneCourse function and
 * the displayDataBase function.
 */
void testCreateNewCourseNDisplay(FILE* dataBase) {

  //TEST1
  FILE* expectedCreate1 = fopen("expectedCreate1.txt", "w");

  char div1 = 'E', div2 = 'N';
  char period = '.';
  char d1 = '6';
  char d2 = '0';
  char d3 = '0';
  char n1 = '1';
  char n2 = '2';
  char n3 = '0';
  char c1 = '4';
  char c2 = '0';
  char space = 0x20;
  char title[31] = "Intermediate Programming";
  char newLine = 0xa;

  fprintf(expectedCreate1, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%s%c", 
	  div1, div2, period, d1, d2, d3, period, n1, n2, n3, 
	  space, c1, period, c2, space, title, newLine); 
  fclose(expectedCreate1);

  createOneCourse(dataBase, d1, d2, d3, n1, n2, n3, c1, c2, title);

  FILE* compareCreate1 = fopen("compareCreate1.txt", "w");
  displayDataBase2(dataBase, compareCreate1);
  fclose(compareCreate1);

  assert(fileeq("expectedCreate1.txt", "compareCreate1.txt"));

} //end testCreateNewCourseNDisplay()

/**
 * This function was directly copied from the list.c
 * that I wrote with the purpose of minor modification.
 * The modification serves to print the list in a file,
 * not on stdout as in the original function.
 */
void displayDetail2(FILE* dataBase4, char d31, char d32, char d33, char n31, char n32, char n33, FILE* tester) {

  if(departmentCheck(d31, d32, d33) == 0) {
    fprintf(stderr, "There was a problem with the department format!\n");
    return;
  }

  if (courseNumberCheck(n31, n32, n33) == 0) {
    fprintf(stderr, "There was a problem with the course number format!\n");
    return;
  }
  int dSkip3 = 0;
  int nSkip3 = 0;
  int numByteSkip3 = 0; //number of bytes to skip per line
  //calculate the number of lines to skip
  dSkip3 = ((d31 - 48) * 80000 + (d32 - 48)* 8000 + ((d33 - 48) - 1) * 800);
  nSkip3 = (((n31 - 48)- 1) * 100 + (n32 - 48)* 10 + (n33 - 48));
  numByteSkip3 = (dSkip3 + nSkip3) * 47;
  fseek(dataBase4, numByteSkip3, SEEK_SET);

  char div31 = 0;
  char div32 = 0;
  char c31 = 0;
  char c32 = 0;
  char title3[LENGTH + 1];
  fread(&div31, sizeof(char), 1, dataBase4);
  fread(&div32, sizeof(char), 1, dataBase4);
  fseek(dataBase4, 1, SEEK_CUR);
  fread(&d31, sizeof(char), 1, dataBase4);
  fread(&d32, sizeof(char), 1, dataBase4);
  fread(&d33, sizeof(char), 1, dataBase4);
  fseek(dataBase4, 1, SEEK_CUR);
  fread(&n31, sizeof(char), 1, dataBase4);
  fread(&n32, sizeof(char), 1, dataBase4);
  fread(&n33, sizeof(char), 1, dataBase4);
  fseek(dataBase4, 1, SEEK_CUR);
  fread(&c31, sizeof(char), 1, dataBase4);
  fseek(dataBase4, 1, SEEK_CUR);
  fread(&c32, sizeof(char), 1, dataBase4);
  fseek(dataBase4, 1, SEEK_CUR);
  fread(title3, sizeof(char), 31, dataBase4);

  if (d31 == '0' && d32 == '0' && d33 == '0') {
    fprintf(stderr, "No course is listed under that number.\n");
  } else {
    fprintf(tester, "%c%c.%c%c%c.%c%c%c %c.%c %s\n", div31, div32, d31, d32, d33, 
	   n31, n32, n33, c31, c32, title3);
  }

} //end displayDetail2()

/**
 * Tests the function in list.c that displays the details of a particular
 * course in the database.
 */
void testDisplayDetail(FILE* dataBase) {

	FILE* expectedDetail1 = fopen("expectedDetail1.txt", "w");

	char div1 = 'E', div2 = 'N';
	char period = '.';
	char d1 = '6';
	char d2 = '0';
	char d3 = '0';
	char n1 = '1';
	char n2 = '2';
	char n3 = '0';
	char c1 = '4';
	char c2 = '0';
	char space = 0x20;
	char title[31] = "Intermediate Programming";
	char newLine = 0xa;

	fprintf(expectedDetail1, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%s%c", 
		div1, div2, period, d1, d2, d3, period, n1, n2, n3, 
		space, c1, period, c2, space, title, newLine); 
	fclose(expectedDetail1);

	FILE* compareDetail1 = fopen("compareDetail1.txt", "w");
	displayDetail2(dataBase, d1, d2, d3, n1, n2, n3, compareDetail1);
	fclose(compareDetail1);

	assert(fileeq("expectedDetail1.txt", "compareDetail1.txt"));

} //end testDisplayDetail()

/**
 * Another test for displayDetail.
 */
void testDisplayDetail2(FILE* dataBase) {

	FILE* expectedDetail2 = fopen("expectedDetail2.txt", "w");

	char div1 = 'E', div2 = 'N';
	char period = '.';
	char d1 = '6';
	char d2 = '0';
	char d3 = '0';
	char n1 = '1';
	char n2 = '2';
	char n3 = '0';
	char c1 = '4';
	char c2 = '0';
	char space = 0x20;
	char title[31] = "Intro to Java";
	char newLine = 0xa;

	fprintf(expectedDetail2, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%s%c", 
		div1, div2, period, d1, d2, d3, period, n1, n2, n3, 
		space, c1, period, c2, space, title, newLine); 
	fclose(expectedDetail2);

	FILE* compareDetail2 = fopen("compareDetail2.txt", "w");
	displayDetail2(dataBase, d1, d2, d3, n1, n2, n3, compareDetail2);
	fclose(compareDetail2);

	assert(fileeq("expectedDetail2.txt", "compareDetail2.txt"));

} //end testDisplayDetail2()

/**
 * Tests the function in list.c that changes a course name in the database.
 */
void testChangeCourseName(FILE* dataBase) {

	FILE* expectedChange1 = fopen("expectedChange1.txt", "w");

	char div1 = 'E', div2 = 'N';
	char period = '.';
	char d1 = '6';
	char d2 = '0';
	char d3 = '0';
	char n1 = '1';
	char n2 = '2';
	char n3 = '0';
	char c1 = '4';
	char c2 = '0';
	char space = 0x20;
	char title[31] = "Advanced Programming";
	char newLine = 0xa;

	fprintf(expectedChange1, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%s%c", 
		div1, div2, period, d1, d2, d3, period, n1, n2, n3, 
		space, c1, period, c2, space, title, newLine); 
	fclose(expectedChange1);

	FILE* compareChange1 = fopen("compareChange1.txt", "w");
	changeCourseName(dataBase, d1, d2, d3, n1, n2, n3, title);
	displayDetail2(dataBase, d1, d2, d3, n1, n2, n3, compareChange1);
	fclose(compareChange1);
	//TEST1
	assert(fileeq("expectedChange1.txt", "compareChange1.txt"));

	FILE* expectedChange2 = fopen("expectedChange2.txt", "w");

	char title2[31] = "Intro to Java";

	fprintf(expectedChange2, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%s%c", 
		div1, div2, period, d1, d2, d3, period, n1, n2, n3, 
		space, c1, period, c2, space, title2, newLine); 
	fclose(expectedChange2);

	FILE* compareChange2 = fopen("compareChange2.txt", "w");
	changeCourseName(dataBase, d1, d2, d3, n1, n2, n3, title2);
	displayDetail2(dataBase, d1, d2, d3, n1, n2, n3, compareChange2);
	fclose(compareChange2);
	//TEST2
	assert(fileeq("expectedChange2.txt", "compareChange2.txt"));

}

/**
 * Tests the deleteCourse function in list.c
 * Deletes a course from the database.
 */
void testDeleteCourse(FILE* dataBase) {

  deleteCourse(dataBase, '6', '0', '0', '1', '2', '0');

  FILE* expectedDelete1 = fopen("expectedDelete1.txt", "w");
  fclose(expectedDelete1);

  FILE* compareDelete1 = fopen("compareDelete1.txt", "w");
  displayDataBase2(dataBase, compareDelete1);
  fclose(compareDelete1);

  assert(fileeq("expectedDelete1.txt", "compareDelete1.txt"));

}

/**
 * Main driver that calls all the tests in operation.
 */
int main(void) {
 
        //Test for making new database
	printf("\nRunning write database test...\n");
	FILE* dataBase1 = fopen("testBase.dat", "w+d");
	writeNewDataBase(dataBase1);
	assert(dataBase1 != NULL);
	fclose(dataBase1);
	printf("Passed all write database tests!\n\n");

	//Tests for Option 2 and Option 4
	FILE* dataBase2 = fopen("testBase.dat", "r+d");
	printf("\nRunning create new course and display whole database test...\n");
	testCreateNewCourseNDisplay(dataBase2);
	printf("Passed all create new course and display whole database tests!\n\n");
	fclose(dataBase2);

	//Tests for Option 3
	FILE* dataBase3 = fopen("testBase.dat", "r+d");
	printf("\nRunning display detail test...\n");
	testDisplayDetail(dataBase3);
	printf("Passed all display detail tests!\n\n");
	fclose(dataBase3);

	//Tests for Option 3
	FILE* dataBase4 = fopen("testBase.dat", "r+d");
	printf("\nRunning display detail test2...\n");
	testDisplayDetail(dataBase4);
	printf("Passed all display detail2 tests!\n\n");
	fclose(dataBase4);

	//Tests for Option 5
	FILE* dataBase5 = fopen("testBase.dat", "r+d");
	printf("\nRunning change course name test...\n");
	testChangeCourseName(dataBase5);
	printf("Passed all change course name tests!\n\n");
	fclose(dataBase5);

	//Tests for Option 7
	FILE* dataBase6 = fopen("testBase.dat", "r+d");
	printf("\nRunning add test...\n");
	testAdd(dataBase6);
	printf("Passed all add tests!\n\n");
	fclose(dataBase6);
 
	//Tests for Option 8
 	FILE* dataBase7 = fopen("testBase.dat", "r+d");
	printf("Running remove test...\n");
	testRemove(dataBase7);
	printf("Passed all remove tests!\n\n");
	fclose(dataBase7);

	//Tests for Option 9
	FILE* dataBase9 = fopen("testBase.dat", "r+d");
	printf("Running displaySemester test...\n");
	testDisplaySemester(dataBase9);
	printf("Passed all displaySemester tests!\n\n");
	fclose(dataBase9);

	//Tests for Option 6
	FILE* dataBase10 = fopen("testBase.dat", "r+d");
	printf("Running remove from database test...");
	testDeleteCourse(dataBase10);
	printf("Passed all removeDataBase tests!\n\n");
	fclose(dataBase10);

  return 0;

} //end main
