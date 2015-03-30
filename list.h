/*
 * Homework4, 600.120 Spring 2015
 * list.h
 * Name: Joon Hyuck Choi
 * Date: Mar 11, 2015
 * Assignment 4
 * Phone: 667-239-0288
 * BB login: jchoi100
 * email: jchoi100@jhu.edu
 * Updated: 20:07 03/11/2015
 */
#define LENGTH 31
#include <stdio.h>

/**
 * Struct that contains information about
 * a course. This will be nested in a Node.
 */
struct course {
  char division[3];
  char dept1;
  char dept2;
  char dept3;
  char class1;
  char class2;
  char class3;
  char wCredit;
  char dCredit;
  char className[31];
  char letterGrade;
  char gradeSign;
};
typedef struct course Course;

/**
 * Node for the linked list implementation of
 * a semester's course list.
 */
struct node {
  Course cStruct;
  struct node* next;
};
typedef struct node Node;

/**
 * Writes a new databaes with 560000 empty entries.
 */
void writeNewDataBase(FILE* dataBase);

/**
 * No duplicates in the same semester. 
 * Must be inserted in a sorted fashion.
 */
void add(Node** ary, char d1, char d2, char d3, char n1, char n2, char n3, char cGrade, char sGrade, Node** newNode, FILE* dataBase8);

/**
 * Remove a course from a semester's listing
 * without disrupting the course number ordering.
 */
void removeC(Node** ary, char d1, char d2, char d3, char n1, char n2, char n3);

/**
 * Display a semester's course listing in order.
 */
void displaySemester(Node* const ary);

/**
 * Display all the courses in the 10 semesters, and remove any duplicates.
 */
void displayAll(Node** const ary);

/**
 * Takes in a semester and reference to the database and 
 * returns the semester's GPA.
 */
//double getGPA(Node* const ary);

/**
 * Takes in a text file to creat new courses in the database.
 * A course number should not already be in use.
 * Check for invalid inputs in the textfile, but ignore
 * erroenous inputs and keep processing until the end.
 */
void createNewCourse(FILE* textfile, FILE* dataBase2);

/**
 * Takes in one line of course specification and adds it in the database.
 */
void createOneCourse(FILE* dataBase3, char d21, char d22, char d23, char n21, char n22, char n23, char c4, char c5, char* title2);

/**
 * Takes in a department code and course code and displays details.
 * Hnadles exceptions. (Course is blank, input error, etc.)
 */
void displayDetail(FILE* dataBase4, char d31, char d32, char d33, char n31, char n32, char n33);

/**
 * Not sure on what to pass into this function yet.
 * Don't show blank courses.
 * This function call can have NO exceptions.
 */
void displayDataBase(FILE* dataBase5);

/**
 * Takes in a department code, course code, and the new name.
 * Changes the corresponding course's name as user input.
 * Handles exceptions. (Course is blank, input error, etc.)
 */
void changeCourseName(FILE* dataBase6, char d51, char d52, char d53, char n51, char n52, char n53, char* title5);

/**
 * Takes in a deparment code and a course code.
 * Finds the matching course and deletes it from the database.
 * The old spot is replaced with a blank record.
 * Handles exceptions. (Course is blank, input error, etc.)
 */
void deleteCourse(FILE* dataBase7, char d61, char d62, char d63, char n61, char n62, char n63);

/**
 * Helper function to detect input errors.
 */
int departmentCheck(char, char, char);

/**
 * Helper function to detect input errors.
 */
int courseNumberCheck(char, char, char);
