//
// Created by thanos chourlias on 25/4/20.
//

#ifndef ASSIGNMENT_STUDENT_H
#define ASSIGNMENT_STUDENT_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTRING 50
///Code for the linked lists and the declaration's for the functions
typedef struct{
    char name[MAXSTRING];
    int id;
}student;

typedef struct _node* node;
struct _node {
    student st;
    node next;
};

typedef struct _list* list;
struct _list {
    node head;
    int size;
};

list list_create();

void list_insertfirst(list l , node n);

node list_newnode(student st);

void list_destroy(list l);

void list_freenode(node n);

int list_empty(list l);

node list_deletefirst(list l);

node list_first(list l);

int list_studentsinfo(node n);

///Decleration of the main's functions

void printMenu();

void print(student st);

void printstudents(list l);

student* load(char *filename);

void save(char *filename, list l);

int addStudent(student st, list l);

//student creatStudent();

student* findStudent(int id, list l);

int deleteStudent(student st, list l);

int updateStudent(student st, list l);

int id_check(int id, list l);

#endif //ASSIGNMENT_STUDENT_H
