/*
 * Homework4, 600.120 Spring 2015
 * hw4.c
 * Name: Joon Hyuck Choi
 * Date: Mar 11, 2015
 * Assignment 4
 * Phone: 667-239-0288
 * BB login: jchoi100
 * email: jchoi100@jhu.edu
 * Updated: 20:07 03/11/2015
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>
#include <ctype.h>
 
/**
 * The main driver function for hw4.
 * The arugments are void for now.
 */
int main(int argc, char* argv[]) {

  //Usage error check
  if (argc == 1) {
    printf("Usage error: type the name of the database file!\n");
    return 1;
  } //end if

  //Variables to be used in the option operations.
  short addSem = -1;
  char addLG = '\0', addSG = '\0';
  short remSem = -1;
  short disSem  = -1;
  //  short gpaSem = -1;

  //Create 10 semesters' worth of node pointers.
  Node* head0 = NULL;
  Node* head1 = NULL;
  Node* head2 = NULL;
  Node* head3 = NULL;
  Node* head4 = NULL;
  Node* head5 = NULL;
  Node* head6 = NULL;
  Node* head7 = NULL;
  Node* head8 = NULL;
  Node* head9 = NULL;

  //An array that keeps all the addresses of the semester lists.
  Node* listptr[10] = {head0, head1, head2, head3, head4,
                       head5, head6, head7, head8, head9};

  //open the database file for reading and writing
  FILE* dataBase = fopen(argv[1], "r+b");

  //if the database doesn't exist beforehand
  if (dataBase == NULL) {
    fprintf(stderr, "%s doesn't exist, creating.....\n", argv[1]);

    //create a new database for writing
    dataBase = fopen(argv[1], "w+b");

    //if there was an error in making a new .dat file
    if (dataBase == NULL) {
      fprintf(stderr, "There was an error making the database file.\n");
      return 1; //end the program
    }

    //writes a new database with 56000 blank entries
    writeNewDataBase(dataBase);
  } //creating a new .dat file

  //check if there is still an error in opening a file
  if (dataBase == NULL) {
    printf("There was an error with moving the file pointer.\n");
    return 1; //exit program
  }

  //close database for now
  fclose(dataBase);
 
  //User interface
  int choice = -1; 
  do {
    printf(" 1. Create a new course from a text file.\n");
    printf(" 2. Add a single course to the database.\n");
    printf(" 3. Disply details of a particular course.\n");
    printf(" 4. Display all courses on the screen.\n");
    printf(" 5. Change the name of a course.\n");
    printf(" 6. Delete a course from the database.\n");
    printf(" 7. Add a course to a semester course listing\n");
    printf(" 8. Remove a course from a semester course listing.\n");
    printf(" 9. Display a course listing on the screen.\n");
    printf("10. Display a merged listing of all courses in all semesters.\n");
    //    printf("11. Display the GPA for a particular semester.\n");

    //take user input
    printf("Enter choice or 0 to quit: ");
    scanf("%d", &choice);
    char buffer = fgetc(stdin); 
    buffer += 1;

    //used for option1    
    int initialCTextSize = 6;
    char* courseText = NULL;
    char ch = '\0';
    int count = 0;

    //interpret the user's choice
    switch (choice) {

      //Used to open the database file several times for each option
      FILE* dataBase2 = NULL;
      FILE* dataBase3 = NULL;
      FILE* dataBase4 = NULL;
      FILE* dataBase5 = NULL;
      FILE* dataBase6 = NULL;
      FILE* dataBase7 = NULL;
      FILE* dataBase8 = NULL;

    case 1: //create new courses from a text file

      dataBase2 = fopen(argv[1], "r+b");
      courseText = malloc(initialCTextSize * sizeof(char));
      printf("Enter the name of the text file containing the new account data: ");

      //scan the name of the text file
      while(!isspace(ch)) {
	if (count >= initialCTextSize) {
	  initialCTextSize *= 2;
	  courseText = realloc(courseText, initialCTextSize * sizeof(char));
	} //end if
	ch = fgetc(stdin);
	if (ch == '\n') {
	  break;
	} //end if
	courseText[count] = ch;
	count++;
      } //end while

      courseText[count] = '\0';

      //open the file with the name that the user entered
      FILE* textFile = fopen(courseText, "r");

      //check if the text file can be opened
      if (textFile == NULL) {
	fprintf(stderr, "There was an error with opening the text file!\n");
	break;
      } //end if

      //pass in the textfile and database to function
      createNewCourse(textFile, dataBase2);

      fclose(textFile);
      fclose(dataBase2);

      //free the malloced string
      if (courseText != NULL) {
	free(courseText);
      } //end if

      break;

    case 2: //add a single course

      dataBase3 = fopen(argv[1], "r+b");
      printf("Enter a course (ex: EN.001.100 3.5 Spanish I): ");
      char c4 = 0, c5 = 0;
      char d21 = 0, d22 = 0, d23 = 0;
      char n21 = 0, n22 = 0, n23 = 0;
      char div2[3], title2[LENGTH];
      int count2 = 0;
      int c6 = ' ';

      //scan a single line of stdin entry
      fscanf(stdin, "%2s.%c%c%c.%c%c%c %c.%c ", div2, &d21, &d22, &d23, 
	     &n21, &n22, &n23, &c4, &c5);
      while (count2 < LENGTH - 1 && (c6 = fgetc(stdin)) != '\n') {
	title2[count2++] = (char) c6;
      }

      title2[count2] = '\0';
      while (c6 != '\n') c6 = fgetc(stdin); //skip to end of line

      //pass in all course-related information to the function
      createOneCourse(dataBase3, d21, d22, d23, n21, n22, n23, c4, c5, title2);
      fclose(dataBase3);

      break;

    case 3: //display details of a particular course

      dataBase4 = fopen(argv[1], "r+b");
      printf("Type the course number(ddd.nnn): "); 
      char d31 = 0, d32 = 0, d33 = 0;
      char n31 = 0, n32 = 0, n33 = 0;

      //scan a single line of stdin entry
      fscanf(stdin, "%c%c%c.%c%c%c", &d31, &d32, &d33, &n31, &n32, &n33);

      //pass in all information to the function
      displayDetail(dataBase4, d31, d32, d33, n31, n32, n33);
      fclose(dataBase4);

      break;

    case 4: //display all non-empty courses in the database on the screen
      //This action cannot fail
      dataBase5 = fopen(argv[1], "r+b");
      displayDataBase(dataBase5);
      fclose(dataBase5);

      break;

    case 5: //change a course name

      dataBase6 = fopen(argv[1], "r+b");
      printf("Type in the course number(ddd.nnn) and the new name: ");

      //scan a single line of stdin entry
      char d51 = 0, d52 = 0, d53 = 0;
      char n51 = 0, n52 = 0, n53 = 0;
      char title5[LENGTH];
      int count5 = 0;
      int c56 = ' ';

      //scan for course code
      fscanf(stdin, "%c%c%c.%c%c%c ", &d51, &d52, &d53, &n51, &n52, &n53);

      //scan for new course name
      while (count5 < LENGTH - 1 && (c56 = fgetc(stdin)) != '\n') {
	title5[count5++] = (char) c56;
      }

      title5[count5] = '\0';
      while (c56 != '\n') c56 = fgetc(stdin);

      //pass in all the relevant information in the function
      changeCourseName(dataBase6, d51, d52, d53, n51, n52, n53, title5);
      fclose(dataBase6);

      break;

    case 6: //remove a course

      //open the database file
      dataBase7 = fopen(argv[1], "r+b");
      printf("Enter course number(ddd.nnn): ");
      char d61 = 0, d62 = 0, d63 = 0;
      char n61 = 0, n62 = 0, n63 = 0;

      //scan for course code
      fscanf(stdin, "%c%c%c.%c%c%c", &d61, &d62, &d63, &n61, &n62, &n63);

      //pass in course information in the function
      deleteCourse(dataBase7, d61, d62, d63, n61, n62, n63);
      fclose(dataBase7);

      break;

    case 7: //add a single course in a semester's listing

      printf("Enter the semester (0 - 9): ");

      //scan the semester
      scanf("%hd", &addSem);
      buffer = fgetc(stdin);

      //check for semester format error
      if (addSem < 0 || addSem > 9) {
	fprintf(stderr, "Invalid semester!\n");
	break;
      }
      char d71 = 0, d72 = 0, d73 = 0;
      char n71 = 0, n72 = 0, n73 = 0;

      //scan for a course number
      printf("Enter course number(ddd.nnn): ");
      scanf("%c%c%c.%c%c%c", &d71, &d72, &d73, &n71, &n72, &n73);
      buffer = fgetc(stdin);

      //scan for the grade
      printf("Enter a letter grade(e.g. A/): ");
      scanf("%c%c", &addLG, &addSG);
      buffer = fgetc(stdin);
      char upperLG = toupper(addLG);

      //check for letter grade combination errors
      if ((upperLG == 'F' || upperLG == 'I' || upperLG == 'S' 
	   || upperLG == 'U') && (addSG == '+' || addSG == '-')) {
	fprintf(stderr, "Invalid letter grade.\n");
	break;
      }

      dataBase8 = fopen(argv[1], "r+b");

      //new node that will hold the new course in the list
      Node* newNode = NULL;
      newNode = malloc(sizeof(Node));

      //pass data into the function
      add(&listptr[addSem], d71, d72, d73, n71, n72, n73, upperLG, addSG, &newNode, dataBase8);
      fclose(dataBase8);

      break;
      
    case 8: //remove a course from a semester listing

      printf("Enter the semester (0 - 9): ");

      //scan for the semseter
      scanf("%1hd", &remSem);
      buffer = fgetc(stdin);

      //check for semester format error
      if (remSem < 0 || remSem > 9) {
	fprintf(stderr, "Invalid semester!\n");
	break;
      }
      
      char d81 = 0, d82 = 0, d83 = 0;
      char n81 = 0, n82 = 0, n83 = 0;

      //scan for course number
      printf("Enter course number(ddd.nnn): ");
      scanf("%c%c%c.%c%c%c", &d81, &d82, &d83, &n81, &n82, &n83);
      buffer = fgetc(stdin);

      //pass in relevant information
      removeC(&listptr[remSem], d81, d82, d83, n81, n82, n83);

      break;
      
    case 9: //display a semester course listing in course number order

      printf("Enter the semester (0 - 9): ");

      //scan for semester
      scanf("%1hd", &disSem);
      buffer = fgetc(stdin);

      //check for semester format error
      if (disSem < 0 || disSem > 9) {
	fprintf(stderr, "Invalid semester!\n");
	break;
      }

      displaySemester(listptr[disSem]);

      break;

      
    case 10: //create and display a merged ordered 
      //listing of all courses in all sems
      //remove any repeats, no duplicates

      displayAll(listptr);

      break;
   
      /*The code below for calculating GPA for a semester 
	works only when there are three or less courses
	in the list. Otherwise, the program crashes.
      */
      /*   
	   case 11: //compute and display GPA for a particular semester
   
	   printf("Enter the semester (0 - 9): ");
	   scanf("%1hd", &gpaSem);
	   buffer = fgetc(stdin);
	   if (gpaSem < 0 || gpaSem > 9) {
	   fprintf(stderr, "Invalid semester!\n");
	   break;
	   }
	   double gpa = 0;
	   gpa = getGPA(listptr[gpaSem]);

	   printf("GPA for Semseter %hd: %.2f\n", gpaSem, gpa);

	   break;
      */

    default:
      break;
    } //end switch

    printf("\n");
      
  } while (choice != 0);

  //Free all nodes
  Node* tmp;
  for (int i = 0; i < 10; i++) {
    while (listptr[i] != NULL) {
      tmp = listptr[i];
      listptr[i] = listptr[i]->next;
      free(tmp);
    }
  }  //end for

  return 0;
} //end main
