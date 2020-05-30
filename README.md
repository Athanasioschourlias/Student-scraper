# Student-scraper
With this program you can locally store information, to a binary file, for a number of students.You can also add students, delete students and even customise the information of a student based on their id.Finally you can print the information of a specific student based on their id or the information from every student in the file.
===================================Technical============================================
This program is writen exclusively in C. Also the information until the user quits is stored in linked-lists, when the user decides that he/she is done with the program and chooses to quit then a function designed to go through the linked list stores all the student structs in a binary file.In order to have a linked list to work with when the program opens a binary file that has already students in it we have the load function which read's the objects(structs) from the binary file and is making a brand new linked list.
=====================================Notes==============================================
1.In order to declare the name of the file you want to work on you have to add it on the commdan line with the line of code you start the program(NAME OF THE EXECUTABLE FILE), ./student <name of the file>.dat

2.It is recommended to use the ending .dat
