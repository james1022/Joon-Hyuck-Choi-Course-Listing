/*
 * Homework4, 600.120 Spring 2015
 * list.c
 * Name: Joon Hyuck Choi
 * Date: Mar 11, 2015
 * Assignment 4
 * Phone: 667-239-0288
 * BB login: jchoi100
 * email: jchoi100@jhu.edu
 * Updated: 21:47 03/11/2015
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/**
 * Takes in a database file pointer and fills it 
 * with 560000 lines of emptry course entries.
 */
void writeNewDataBase(FILE* dataBase) {

  //write 560000 empty entries in the database.
  for(int i = 0; i < 560000; i++) {

    char div1 = 'E';
    char div2 = 'N';
    char* desc = malloc((LENGTH + 1) * sizeof(char));
    desc[0] = '\0';

    char d1 = '0';
    char d2 = '0';
    char d3 = '0';
    char n1 = '0';
    char n2 = '0';
    char n3 = '0';
      
    char c1 = '0';
    char c2 = '0';
       
    char space = 0x20;
    char period = 0x2e;
    char newLine = 0x0a;

    //Write the blank entries in the database file
    fwrite(&div1, sizeof(char), 1, dataBase); //E
    fwrite(&div2, sizeof(char), 1, dataBase); //N

    fwrite(&period, sizeof(char), 1, dataBase); //.

    fwrite(&d1, sizeof(char), 1, dataBase); //0
    fwrite(&d2, sizeof(char), 1, dataBase); //0
    fwrite(&d3, sizeof(char), 1, dataBase); //0

    fwrite(&period, sizeof(char), 1, dataBase); //.

    fwrite(&n1, sizeof(char), 1, dataBase); //0
    fwrite(&n2, sizeof(char), 1, dataBase); //0
    fwrite(&n3, sizeof(char), 1, dataBase); //0

    fwrite(&space, sizeof(char), 1, dataBase); // 

    fwrite(&c1, sizeof(char), 1, dataBase); //0
    fwrite(&period, sizeof(char), 1, dataBase); //.
    fwrite(&c2, sizeof(char), 1, dataBase); //0

    fwrite(&space, sizeof(char), 1, dataBase); // 

    fwrite(desc, sizeof(char), 31, dataBase); //31 empty spaces

    fwrite(&newLine, sizeof(char), 1, dataBase); //\n

    free(desc);

    fflush(dataBase);

  } //end for 560000

} //end writeNewDataBase()

/**
 * Choice 1
 * Takes in a text file to creat new courses in the database.
 * A course number should not already be in use.
 * Check for invalid inputs in the textfile, but ignore
 * erroenous inputs and keep processing until the end.
 */
void createNewCourse(FILE* textFile, FILE* dataBase2) {

  //Scan each line in the textfile for a course entry
  while (!feof(textFile)) {
	
    char c1 = 0, c2 = 0;
    char d1 = 0, d2 = 0, d3 = 0;
    char n1 = 0, n2 = 0, n3 = 0;
    char div1[3], title1[31];
    int count1 = 0;
    int c3 = ' ';
    int dSkip1 = 0;
    int nSkip1 = 0;
    int numByteSkip1 = 0; //nuumber of bytes to skip per line

    //scan for EN.000.000 0.0 
    fscanf(textFile, "%2s.%c%c%c.%c%c%c %c.%c", div1, &d1, &d2, &d3, 
	   &n1, &n2, &n3, &c1, &c2);

    if (c3 == EOF) {
      break;
    } //break out once we've reached the end of file

    //Error checking
    if (departmentCheck(d1, d2, d3) == 0) {
      fprintf(stderr, "Invalid department code.\n");
      goto here1;
    }

    //Error checking
    if (courseNumberCheck(n1, n2, n3) == 0) {
      fprintf(stderr, "Invalid course number.\n");
      goto here1;
    }

    //Error checking
    if ((c1 - 48) < 0 || (c1 - 48) > 5) {
      fprintf(stderr, "Invalid credit.\n");
      goto here1;
    }

    //Error checking
    if ((c2 - 48) != 0 && (c2 - 48) != 5) {
      fprintf(stderr, "The decimal credit must be a 0 or a 5.\n");
      goto here1;
    }

    //scan for "Course description"\n
    while (count1 < 30 && (c3 = fgetc(textFile)) != '\n') {
      title1[count1++] = (char) c3;
    } //end while

    title1[count1] = '\0';

    while (c3 != '\n') {
      c3 = fgetc(textFile); //skip to end of line
    } //end while

    //calculate how many lines need to be skipped in the database
    dSkip1 = ((d1 - 48) * 80000 + (d2 - 48)* 8000 + ((d3 - 48) - 1) * 800);
    nSkip1 = (((n1 - 48)- 1) * 100 + (n2 - 48)* 10 + (n3 - 48));
    numByteSkip1 = (dSkip1 + nSkip1) * 47;
    fseek(dataBase2, numByteSkip1 + 3, SEEK_SET);

    //write the new data in the database file
    fwrite(&d1, sizeof(char), 1, dataBase2);
    fwrite(&d2, sizeof(char), 1, dataBase2);
    fwrite(&d3, sizeof(char), 1, dataBase2);
    fseek(dataBase2, 1, SEEK_CUR);
    fwrite(&n1, sizeof(char), 1, dataBase2);
    fwrite(&n2, sizeof(char), 1, dataBase2);
    fwrite(&n3, sizeof(char), 1, dataBase2);
    fseek(dataBase2, 1, SEEK_CUR);
    fwrite(&c1, sizeof(char), 1, dataBase2);
    fseek(dataBase2, 1, SEEK_CUR);
    fwrite(&c2, sizeof(char), 1, dataBase2);
    fseek(dataBase2, 1, SEEK_CUR);
    fwrite(title1, sizeof(char), 31, dataBase2);
    
    fflush(dataBase2);

  here1:
	
    //set the title back to null
    for (int i = 0; i < 31; i++) {
      title1[i] = '\0';
    } //end for
	
  } //end while

} //end createNewCourse()

/**
 * Choice 2
 * Takes in one line of course specification 
 * and adds it in the database.
 * The function exits upon detecting 
 * an error in innput or if the
 * specified course space is not empty.
 */
void createOneCourse(FILE* dataBase3, char d21, char d22, char d23, 
		     char n21, char n22, char n23, 
		     char c4, char c5, char* title2) {

  //check for input errors
  if(departmentCheck(d21, d22, d23) == 0) {
    fprintf(stderr, "There was a problem with the department format.\n");
    return;
  }

  //Error checking
  if (courseNumberCheck(n21, n22, n23) == 0) {
    fprintf(stderr, "There was a problem with the course number format!\n");
    return;
  }

  //Error checking
  if ((c4 - 48) < 0 || (c4 - 48) > 5) {
    fprintf(stderr, "There was a problem with the credit format!\n");
    return;
  }

  //Error checking
  if ((c5 - 48) != 0 && (c5 - 48) != 5) {
    fprintf(stderr, "The decimal credit must be a 0 or a 5!\n");
    return;
  }

  int dSkip2 = 0;
  int nSkip2 = 0;
  int numByteSkip2 = 0; //nuumber of bytes to skip per line
    
  //calculate the number of lines to skip
  dSkip2 = ((d21 - 48) * 80000 + (d22 - 48)* 8000 + ((d23 - 48) - 1) * 800);
  nSkip2 = (((n21 - 48)- 1) * 100 + (n22 - 48)* 10 + (n23 - 48));
  numByteSkip2 = (dSkip2 + nSkip2) * 47;

  char tempd21 = '\0', tempd22 = '\0', tempd23 = '\0';

  //Check if the space is empty
  fseek(dataBase3, numByteSkip2 + 3, SEEK_SET); 
  fread(&tempd21, sizeof(char), 1, dataBase3);
  fread(&tempd22, sizeof(char), 1, dataBase3);
  fread(&tempd23, sizeof(char), 1, dataBase3);

  //if the space is empty
  if (tempd21 == '0' && tempd22 == '0' && tempd23 == '0') {
    //write new data on top of it
    fseek(dataBase3, numByteSkip2 + 3, SEEK_SET);
    fwrite(&d21, sizeof(char), 1, dataBase3);
    fwrite(&d22, sizeof(char), 1, dataBase3);
    fwrite(&d23, sizeof(char), 1, dataBase3);
    fseek(dataBase3, 1, SEEK_CUR);
    fwrite(&n21, sizeof(char), 1, dataBase3);
    fwrite(&n22, sizeof(char), 1, dataBase3);
    fwrite(&n23, sizeof(char), 1, dataBase3);
    fseek(dataBase3, 1, SEEK_CUR);
    fwrite(&c4, sizeof(char), 1, dataBase3);
    fseek(dataBase3, 1, SEEK_CUR);
    fwrite(&c5, sizeof(char), 1, dataBase3);
    fseek(dataBase3, 1, SEEK_CUR);
    fwrite(title2, sizeof(char), 31, dataBase3);

    //Message upon success
    printf("EN.%c%c%c.%c%c%c %c.%c %s was added!\n", d21, d22, d23, 
	   n21, n22, n23, c4, c5, title2);

  } else{
    //if the space wasn't empty
    fprintf(stderr, "There is already a course under that number.\n");
  }

} //end createOneCourse()

/**
 * Choice 3
 * Takes in a department code and course code and displays details.
 * Hnadles exceptions. (Course is blank, input error, etc.)
 * Upon finding an exception, the function exits.
 */
void displayDetail(FILE* dataBase4, char d31, char d32, char d33, 
		   char n31, char n32, char n33) {

  //Error checking
  if(departmentCheck(d31, d32, d33) == 0) {
    fprintf(stderr, "There was a problem with the department format!\n");
    return;
  }

  //Error checking
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

  //read the details of a specified course
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

  //check if the course is blank
  if (d31 == '0' && d32 == '0' && d33 == '0') {
    fprintf(stderr, "No course is listed under that number.\n");
  } else {
    printf("\n%c%c.%c%c%c.%c%c%c %c.%c %s\n", div31, div32, d31, d32, d33, 
	   n31, n32, n33, c31, c32, title3);
  } //end if-else

} //end displayDetail()

/**
 * Choice 4
 * Don't show blank courses.
 * This function call can have NO exceptions.
 */
void displayDataBase(FILE* dataBase5) {

  fseek(dataBase5, 0, SEEK_SET);
  char c41 = 0, c42 = 0;
  char d41 = 0, d42 = 0, d43 = 0;
  char n41 = 0, n42 = 0, n43 = 0;
  char div41 = 0, div42 = 0;
  char title4[31];

  printf("\n");

  //search through the entire database for nonempty courses
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
      //skip any empty entries
      continue;
    } else {
      printf("%c%c.%c%c%c.%c%c%c %c.%c %s", div41, div42, d41, d42, d43, 
	     n41, n42, n43, c41, c42, title4);
      printf("\n");
    } //end if-else

  } //end for

} //end displayDataBase()

/**
 * Choice 5
 * Takes in a department code, course code, and the new name.
 * Changes the corresponding course's name as user input.
 * Handles exceptions. (Course is blank, input error, etc.)
 */
void changeCourseName(FILE* dataBase6, char d51, char d52, char d53, 
		      char n51, char n52, char n53, char* title5) {

  //Error checking
  if(departmentCheck(d51, d52, d53) == 0) {
    fprintf(stderr, "There was a problem with the department format!\n");
    return;
  }

  //Error checking
  if (courseNumberCheck(n51, n52, n53) == 0) {
    fprintf(stderr, "There was a problem with the course number format!\n");
    return;
  }
 
  int dSkip5 = 0;
  int nSkip5 = 0;
  int numByteSkip5 = 0; //number of bytes to skip per line

  //calculate the number of lines to skip
  dSkip5 = ((d51 - 48) * 80000 + (d52 - 48)* 8000 + ((d53 - 48) - 1) * 800);
  nSkip5 = (((n51 - 48)- 1) * 100 + (n52 - 48)* 10 + (n53 - 48));
  numByteSkip5 = (dSkip5 + nSkip5) * 47;

  char temp1 = 0, temp2 = 0, temp3 = 0;
  fseek(dataBase6, numByteSkip5 + 3, SEEK_SET);
  fread(&temp1, sizeof(char), 1, dataBase6);
  fread(&temp2, sizeof(char), 1, dataBase6);
  fread(&temp3, sizeof(char), 1, dataBase6);

  fseek(dataBase6, numByteSkip5 + 15, SEEK_SET);

  if (temp1 == '0' && temp2 == '0' && temp3 == '0') {
    //this is when the entry is emtpy
    fprintf(stderr, "The course record is blank.\n");
  } else {
    fwrite(title5, sizeof(char), 31, dataBase6);
  } //end if-else

} //end changeCourseName

/**
 * Choice 6
 * Takes in a deparment code and a course code.
 * Finds the matching course and deletes it from the database.
 * The old spot is replaced with a blank record.
 * Handles exceptions. (Course is blank, input error, etc.)
 */
void deleteCourse(FILE* dataBase7, char d61, char d62, char d63, 
		  char n61, char n62, char n63) {

  int dSkip6 = 0;
  int nSkip6 = 0;
  int numByteSkip6 = 0; //number of bytes to skip per line
  char* title6 = malloc((31) * sizeof(char));
  title6[0] = '\0';
  int nullChar = '0';

  //check for errors in dept code
  if(departmentCheck(d61, d62, d63) == 0) {
    fprintf(stderr, "There was a problem with the department format!\n");
    return;
  }

  //check for error in course number
  if (courseNumberCheck(n61, n62, n63) == 0) {
    fprintf(stderr, "There was a problem with the course number format!\n");
    return;
  }
 
  //calculate the nubmer of lines to skip
  dSkip6 = ((d61 - 48) * 80000 + (d62 - 48)* 8000 + ((d63 - 48) - 1) * 800);
  nSkip6 = (((n61 - 48)- 1) * 100 + (n62 - 48)* 10 + (n63 - 48));
  numByteSkip6 = (dSkip6 + nSkip6) * 47;

  char temp61 = 0, temp62 = 0, temp63 = 0;
  fseek(dataBase7, numByteSkip6 + 3, SEEK_SET);
  fread(&temp61, sizeof(char), 1, dataBase7);
  fread(&temp62, sizeof(char), 1, dataBase7);
  fread(&temp63, sizeof(char), 1, dataBase7);

  fseek(dataBase7, numByteSkip6 + 3, SEEK_SET);

  if (temp61 == '0' && temp62 == '0' && temp63 == '0') {
    //this is when the entry is emtpy
    fprintf(stderr, "The course record is blank.\n");
  } else {
    //overwrite the place with null data
    fwrite(&nullChar, sizeof(char), 1, dataBase7);
    fwrite(&nullChar, sizeof(char), 1, dataBase7);
    fwrite(&nullChar, sizeof(char), 1, dataBase7);

    fseek(dataBase7, 1, SEEK_CUR);

    fwrite(&nullChar, sizeof(char), 1, dataBase7);
    fwrite(&nullChar, sizeof(char), 1, dataBase7);
    fwrite(&nullChar, sizeof(char), 1, dataBase7);

    fseek(dataBase7, 1, SEEK_CUR);

    fwrite(&nullChar, sizeof(char), 1, dataBase7);
    fseek(dataBase7, 1, SEEK_CUR);
    fwrite(&nullChar, sizeof(char), 1, dataBase7);

    fseek(dataBase7, 1, SEEK_CUR);

    fwrite(title6, sizeof(char), 31, dataBase7);

  } //end if-else

  free(title6);

} //end deleteCourse()

/**
 * Choice 7
 * This function takes in one semester's linked list
 * and the department code, class code, and grade of
 * the new course to add to the linked list.
 * The newly added course will be added in a sorted
 * fashion, increasing in numerical order.
 */
void add(Node** ary, char d1, char d2, char d3, 
	 char n1, char n2, char n3, char lG, char sG, 
	 Node** newNode, FILE* dataBase8) {

  Node* current;
  Node* current2;
  int detector = 1; 
  char c1 = '\0', c2 = '\0';

  //Set the new node's data with the given data
  (*newNode)->cStruct.dept1 = d1;
  (*newNode)->cStruct.dept2 = d2;
  (*newNode)->cStruct.dept3 = d3;

  (*newNode)->cStruct.class1 = n1;
  (*newNode)->cStruct.class2 = n2;
  (*newNode)->cStruct.class3 = n3;

  (*newNode)->cStruct.letterGrade = lG;
  (*newNode)->cStruct.gradeSign = sG;
  (*newNode)->next = NULL;

  //Error checking
  if(departmentCheck(d1, d2, d3) == 0) {
    fprintf(stderr, "There was a problem with the department format!\n");
    return;
  }

  //Error checking
  if (courseNumberCheck(n1, n2, n3) == 0) {
    fprintf(stderr, "There was a problem with the course number format!\n");
    return;
  }

  //Error checking
  if (lG != 'A' && lG != 'B' && lG != 'C' && lG != 'D'
      && lG != 'F' && lG != 'I' && lG != 'S' && lG != 'U') {
    fprintf(stderr, "Invalid letter grade!\n");
    return;
  }

  //Error checking
  if (sG != '+' && sG != '-' && sG != '/') {
    fprintf(stderr, "Invalid subgrade!\n");
    return;
  }

  int dSkip7 = 0;
  int nSkip7 = 0;
  int numByteSkip7 = 0; //number of bytes to skip per line

  //calculate the number of lines to skip
  dSkip7 = ((d1 - 48) * 80000 + (d2 - 48)* 8000 + ((d3 - 48) - 1) * 800);
  nSkip7 = (((n1 - 48)- 1) * 100 + (n2 - 48)* 10 + (n3 - 48));
  numByteSkip7 = (dSkip7 + nSkip7) * 47;
  fseek(dataBase8, numByteSkip7, SEEK_SET);

  //read the course data from the database
  char title7[LENGTH + 1];
  fseek(dataBase8, 3, SEEK_CUR);
  fread(&d1, sizeof(char), 1, dataBase8);
  fread(&d2, sizeof(char), 1, dataBase8);
  fread(&d3, sizeof(char), 1, dataBase8);
  fseek(dataBase8, 1, SEEK_CUR);
  fread(&n1, sizeof(char), 1, dataBase8);
  fread(&n2, sizeof(char), 1, dataBase8);
  fread(&n3, sizeof(char), 1, dataBase8);
  fseek(dataBase8, 1, SEEK_CUR);
  fread(&c1, sizeof(char), 1, dataBase8);
  fseek(dataBase8, 1, SEEK_CUR);
  fread(&c2, sizeof(char), 1, dataBase8);
  fseek(dataBase8, 1, SEEK_CUR);
  fread(title7, sizeof(char), 31, dataBase8);

  //check if the entry is empty
  if (d1 == '0' && d2 == '0' && d3 == '0') {
    fprintf(stderr, "No course is listed under that number.\n");
    return;
  }

  //now we can se thte course's credit obtained from the DB
  (*newNode)->cStruct.wCredit = c1;
  (*newNode)->cStruct.dCredit = c2;
  //Also the course name
  strcpy((*newNode)->cStruct.className, title7);

  //the numerical value of the department code
  int baseVal = d1 * 100000 + d2 * 10000 + d3 * 1000 + n1 * 100 + n2 * 10 + n3;

  int depVal2 = 0, depVal21 = 0;

  //check if the semester was an empty list
  //or compare the new node's dep+cls value with the current head
  //The simple arithmetic shown right below shows up all through out
  //So here is a brief description of the logic (though it may seem obvious)
  //for instance, a course with the code 600.120 will have a unique numerical value of 600120
  //and a course with the code 600.226 will have a value of 600226.
  //We will compare the numerical values of 600120 and 600226 to see which one comes after.
  //The same logic applies in the code through out the whole assignment.
  if (*ary == NULL || (*ary)->cStruct.dept1 * 100000 
      + (*ary)->cStruct.dept2 * 10000 
      + (*ary)->cStruct.dept3 * 1000 
      + (*ary)->cStruct.class1 * 100 
      + (*ary)->cStruct.class2 * 10 
      + (*ary)->cStruct.class3 > baseVal) {
    (*newNode)->next = *ary;
    *ary = *newNode;
  } else {

    current2 = *ary;

    //check for duplicates and set a flag value
    while (current2->next != NULL) {
    
      depVal2 = (current2->cStruct.dept1) * 100000 
	+ (current2->cStruct.dept2) * 10000 
	+ (current2->cStruct.dept3) * 1000 
	+ (current2->cStruct.class1) * 100  
	+ (current2->cStruct.class2) * 10 
	+ (current2->cStruct.class3);

      depVal21 =  (current2->next->cStruct.dept1) * 100000 
	+ (current2->next->cStruct.dept2) * 10000 
	+ (current2->next->cStruct.dept3) * 1000 
	+ (current2->next->cStruct.class1) * 100  
	+ (current2->next->cStruct.class2) * 10 
	+ (current2->next->cStruct.class3);

      if (depVal2 == baseVal || depVal21 == baseVal) {
	detector = 0;
      } //end if
      
      current2 = current2->next;
    } //end while

    current = *ary;

    //see how much down the list we have to go by comparing the numerical values of the courses
    while (current->next != NULL && ((current->next->cStruct.dept1) * 100000) 
	   + (current->next->cStruct.dept2) * 10000 
	   + ((current->next->cStruct.dept3) * 1000) 
	   + (current->next->cStruct.class1) * 100 
	   + (current->next->cStruct.class2) * 10 
	   + (current->next->cStruct.class3) < baseVal) {
      current = current->next;
    }
    if (detector == 0) {
      fprintf(stderr, "The same course is already in the list!\n");
      return;
    }
    (*newNode)->next = current->next;
    current->next = (*newNode);
  } //end if-else

} //end add()

/**
 * Choice 8
 * This function takes in a semester's linked list,
 * and the department and class codes of the course
 * to remove from the list. It makes sure that the
 * ordering does not change afterwards.
 */
void removeC(Node** ary, char d1, char d2, char d3, 
	     char n1, char n2, char n3) {

  Node* oldhead;
  Node* newhead;
  Node* current;
  int count = 0;
  Node* current2;
  int baseVal = d1 * 100000 + d2 * 10000 + d3 * 1000 + n1 * 100 + n2 * 10 + n3;

  //Error checking
  if (departmentCheck(d1, d2, d3) == 0) {
    fprintf(stderr, "There was a problem with the department format!\n");
    return;
  }

  //Error checking
  if (courseNumberCheck(n1, n2, n3) == 0) {
    fprintf(stderr, "There was a problem with the course number format!\n");
    return;
  }

  //Check if the pointer is null OR if
  //the first element is the match OR
  //execute the lines in the else block.
  //the else block takes care of the case
  //in which the list is not empty and the
  //first node was not the match
  if (*ary == NULL) {
    fprintf(stderr, "There are no courses in the list.\n");
    return;
  } else if ((*ary)->cStruct.dept1 * 100000 
	     + (*ary)->cStruct.dept2 * 10000 
	     + (*ary)->cStruct.dept3 * 1000 
	     + (*ary)->cStruct.class1 * 100 
	     + (*ary)->cStruct.class2 * 10 
	     + (*ary)->cStruct.class3 == baseVal) {
    oldhead = *ary;
    newhead = (oldhead)->next;
    *ary = newhead;
    free(oldhead);
  } else {
    current = *ary;
    current2 = *ary;

    //Keep searching through the list until a match is found.
    while ((current != NULL) && (((current->cStruct.dept1) * 100000) 
				 + (current->cStruct.dept2) * 10000 
				 + ((current->cStruct.dept3) * 1000) 
				 + (current->cStruct.class1) * 100 
				 + (current->cStruct.class2) * 10 
				 + (current->cStruct.class3) != baseVal)) {
      current = current->next;
      count++;
    }

    //When the list has been exhausted and no match was found.
    if (current == NULL) {
      fprintf(stderr, "There is no corresponding course in the list.\n");
      return;
    }

    for (int i = 0; i < count - 1; i++) {
      current2 = current2->next;
    }

    current2->next = current->next;

    free(current);

  } //end if-else

} //end removeC()

/**
 * Choice 9
 * This function takes in a semester's linked list
 * and prints out all the courses in order.
 */
void displaySemester(Node* const ary) {

  Node* current;

  //check if the list is empty
  if (ary == NULL) {
    fprintf(stderr, "No courses this semester.\n");
    return;
  } else {
    current = ary;
    while (current != NULL) { //keep printing until the end
      printf("EN.%c%c%c.%c%c%c %c.%c %s %c%c\n", 
	     current->cStruct.dept1, current->cStruct.dept2, current->cStruct.dept3, 
	     current->cStruct.class1, current->cStruct.class2, current->cStruct.class3, 
	     current->cStruct.wCredit, current->cStruct.dCredit, current->cStruct.className, 
	     current->cStruct.letterGrade, current->cStruct.gradeSign);
      current = current->next;
    } //end while

  } //end if-else

} //end displaySemester()

/**
 * Choice 10
 * This function takes in the whole data structure of 
 * all 10 semesters' linked lists and creates a long 
 * list of courses in a sorted fashion.
 * Once it's looked at all the values, it prints the list.
 */
void displayAll(Node** const ary) {

  Node* temp;
  int pos = 0;
  Node* copiedList;
  int initialSize = 20;
  copiedList = malloc(initialSize * sizeof(Node));

  //checks all semesters
  for (int i = 0; i < 10; i++) {
    if (*(ary + i) != NULL) {
      temp = *(ary + i);

      while (temp != NULL) {

	//go through all the lists and save the course information
	//in an array of node structs
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

  //now we have an unsorted array of all the courses in the 10 lists

  Node a;

  int valI = 0;
  int valJ = 0;

  //simple sorting algorithm with O(N^2)
  for (int i = 0; i < pos; i++) {

    for (int j = i + 1; j < pos; j++) {

      valI = copiedList[i].cStruct.dept1 * 100000 
	+ copiedList[i].cStruct.dept2 * 10000 
	+ copiedList[i].cStruct.dept3 * 1000 
	+ copiedList[i].cStruct.class1 * 100 
	+ copiedList[i].cStruct.class2 * 10 
	+ copiedList[i].cStruct.class3;

      valJ = copiedList[j].cStruct.dept1 * 100000 
	+ copiedList[j].cStruct.dept2 * 10000 
	+ copiedList[j].cStruct.dept3 * 1000 
	+ copiedList[j].cStruct.class1 * 100 
	+ copiedList[j].cStruct.class2 * 10 
	+ copiedList[j].cStruct.class3;

      if (valI > valJ) {
	a = copiedList[i];
	copiedList[i] = copiedList[j];
	copiedList[j] = a;
      } else if (valI == valJ) { //ignore duplicates
	copiedList[j] = copiedList[pos - 1];
	pos--;
      }

    }

  } //end for sorting

  //print the list
  for (int i = 0; i < pos; i++) {
    printf("EN.%c%c%c.%c%c%c %c.%c %s %c%c\n", copiedList[i].cStruct.dept1, 
	   copiedList[i].cStruct.dept2, copiedList[i].cStruct.dept3, 
	   copiedList[i].cStruct.class1, copiedList[i].cStruct.class2, 
	   copiedList[i].cStruct.class3, copiedList[i].cStruct.wCredit, 
	   copiedList[i].cStruct.dCredit, copiedList[i].cStruct.className, 
	   copiedList[i].cStruct.letterGrade, copiedList[i].cStruct.gradeSign);
  }
 
  //if there is no element to display
  if (pos == 0) {
    fprintf(stderr, "There are no courses in any of the semesters.\n");
  }

  free(copiedList);

} //end displayAll()

/**
 * Takes in the components of a department code and checks for errors.
 */
int departmentCheck(char d1, char d2, char d3) {

  if(((d1 - 48) * 100 + (d2 - 48) * 10 + (d3 - 48)) < 0 
     || ((d1 - 48) * 100 + (d2 - 48) * 10 + (d3 - 48)) > 700) {
	
    return 0;
  }
  return 1;
} //end departmentCheck()

/**
 * Takes in the components of a course number code and checks for errors.
 */
int courseNumberCheck(char n1, char n2, char n3) {

  if (((n1 - 48) * 100 + (n2 - 48) * 10 + (n3 - 48)) < 0 
      || ((n1 - 48) * 100 + (n2 - 48) * 10 + (n3 - 48)) > 899) {
    return 0;
	
  }
  return 1;
} //end courseNumberCheck()

/**
 * Takes in a semester's list and the database file
 * and computes the GPA for that semester.
 * Returns the resultant GPA.
 * Ignores all classes with grades of I, S, U.
 */
/*
  double getGPA(Node* const ary) {

  int size = 2;
  int i = 0;
  double* gradeGPA = malloc(size * sizeof(double));
  double* credits = malloc(size * sizeof(double));
  char letGrade = '\0';
  char subGrade = '\0';
  Node* current;
  int count = 0;
  int count2 = 0;
  double gpa = 0;
  char c1 = '\0';
  char c2 = '\0';

  if (ary == NULL) {
  printf("No courses to display in this list.\n");
  return 0;
  } else {
  current = ary;
  while (current != NULL) {

  int gGPA = 0;

  if (i >= size) {
  size *= 2;
  gradeGPA = realloc(gradeGPA, size * sizeof(double));
  credits = realloc(credits, size * sizeof(double));
  }

  letGrade = current->cStruct.letterGrade;
  subGrade = current->cStruct.gradeSign;

  c1 = current->cStruct.wCredit;
  c2 = current->cStruct.dCredit;

  if (letGrade == 'A') {
  gGPA += 4;
  count++;
  } else if (letGrade == 'B') {
  gGPA += 3;
  count++;
  } else if (letGrade == 'C') {
  gGPA += 2;
  count++;
  } else if (letGrade == 'D') {
  gGPA += 1;
  count++;
  } else if (letGrade == 'F'){
  gGPA += 0;
  count++;
  }

  if (letGrade != 'A' && letGrade != 'F' && letGrade != 'I' 
  && letGrade != 'S' && letGrade != 'U' && subGrade == '+') {
  gGPA += 0.3;
  } else if (letGrade != 'F' && letGrade != 'I' && letGrade != 'S' 
  && letGrade != 'U' && subGrade == '-') {
  gGPA -= 0.3;
  }
  gradeGPA[count2] = gGPA;

  double dWCredit = c1 - 48.0;
  double dDCredit = c2 - 48.0;

  credits[count2] = dWCredit + dDCredit;

  count2++;

  current = current->next;

  double cumulative = 0;

  //add the gpa up
  for (int j = 0; j < count2; j++) {
  cumulative = cumulative + (gradeGPA[j] * credits[j]);
  } //end for

  double allCredits = 0;

  for (int k = 0; k < count2; k++) {
  allCredits += credits[k];
  }

  gpa = cumulative / allCredits;
   
  free(gradeGPA);
  free(credits);
 
  return gpa;

  } //end getGPA
*/
