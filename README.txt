/*
 * Homework4, 600.120 Spring 2015
 * README.txt
 * Name: Joon Hyuck Choi
 * Date: Mar 11, 2015
 * Assignment 4
 * Phone: 667-239-0288
 * BB login: jchoi100
 * email: jchoi100@jhu.edu
 * Updated: 20:11 03/11/2015
 */
===========================================================================================
The .zip file includes:

     1) list.h
     2) list.c
     3) hw4.c
     4) testList.c
     5) Makefile
     6) README.txt
     7) jhu.dat   //a database file that I created for testing.
     8) real.txt  //a textfile with a few course entries saved.

===========================================================================================

How to compile testList:

       (Using Makefile): make testList
       (On command line): gcc -std=c99 -Wall -Wextra -pedantic -o testList -O testList.c

===========================================================================================

How to run testList:

       (Using Makefile): make test
       (On command line): ./testList

===========================================================================================

How to compile hw4:

       (Using Makefile): make list.o
       	      		 make hw4.o
			 make hw4 (or typing make hw4 from the beginning will work as well)
       (On command line): gcc -std=c99 -Wall -Wextra -pedantic -o hw4 -O list.h list.c hw4.c

===========================================================================================

How to run hw4:

       (On command line): ./hw4 <data_base_file_name>.dat

===========================================================================================

Comments:

   list.c
	For a few functions that print results on the screen,
	I copied and pasted the same function in my test driver
	and changed the printf statements to fprintf statements.
	So the copied over functions actually do test the original
	functions. This was to make use of the function fileeq();	

	Extra Credit 1:
	I attempted and succeeded in getting the first extra credit
	portion (merging and displaying all the courses in order)
	and implemented it in the user interface. (Option 10)

	Extra Credit 2:
	In writing the function that calculates the gpa for a 
	given semester, I was able to make it work for a semester
	with 3 (sometimes 4) courses in the list, but the program
	would crash for semesters with more than that number of 
	courses listed. So I commented out all the parts related
	with the GPA calculation.
	But if the grader could take a look at that function 
	and see any places where I can be given partial credit, 
	I would really appreciate it.
	      -> Related code is both in list.c and hw4.c.

   jhu.dat
	I included a sample data base file that I used to test.

   real.txt
	real.txt is a short list of courses that I used in testing.

===========================================================================================

===========================================================================================
