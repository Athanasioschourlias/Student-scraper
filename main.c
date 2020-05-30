//
// Created by thanos chourlias on 25/4/20.
//
#include "student.h"

int main(int argv, char **argc){
//    IMPORTING THE STUDENTS FROM THE FILE IF THERE ARE ANY.//TODO CHEKING IF THE USER ENTERED THE RIGHT FILE FORMAT(maybe)!
    if(argc[1] == NULL){
        printf("YOU FORGOT THE FILE NAME!\n");
        abort();
    }
    list l = list_create();//Creating an empty list
    node n;//Creating a node for reference
    int numstudents;
    FILE *fp;
    fp = fopen( argc[1],"a+");
    if (  fp == NULL ){
        printf("file could not be accessed\n");
        return 0;
    }

    long filesize = ftell(fp);

    numstudents = filesize / sizeof(student);
    student st;

    student *s = load(argc[1]);
    int  i;
    char answer;
    for(i = 0;i < numstudents;i++){
//        student st = s[i];///TODO POSSIBLE BUG
//        printf("name: %s\n", s[i].name);
//        printf("id: %d\n", s[i].id);
        list_insertfirst(l,list_newnode(s[i]));

    }
//    node current = list_first(l);
//    while(current != NULL){
//        printf("name %s \n", current->st.name);
//        printf("id %d \n", current->st.id);
//        current = current->next;
//    }
    if(filesize == 0){
        printf("This file is empty!!\n");
        printf("Registration of a new student?(y/n):");
        scanf("%c", &answer);

        while (answer != 'y' && answer != 'n') {
            printf("try to enter a valaid value(y for yes and n for no): ");
            scanf("%c", &answer);
        }

        if(answer == 'y') {
            printf("Give the name of the student you want to add: ");
            scanf("%s", st.name);
            printf("Give the id of the student you want to add: ");
            scanf("%d", &st.id);
            //CHECKING IF THE ID IS UNIC SO WE DONT CREATE TWO STUDENTS WITH THE SAME ID
            while (id_check(st.id, l) == 1) {
                printf("I found a student with the same id!give an other id: ");
                scanf("%d\n", &st.id);
            }
            addStudent(st, l);
            printf("New student's info are successfully added to the list\n");
        }else {
            printf("Sorry but the are no options to choose from when the file of srudents is empty!!try to add at least one student!\n");
            return 0; /* optional */
        }
    }
    free(s);//freeing up the memory we "took" in order to make the new list

    //Printing the menu so the user can see his options
    int choice,id,student_id_user,test,option;
    char name[MAXSTRING];
    s = (student *) malloc(sizeof(student));
    if (s == NULL) {
        printf("I need more memory!!");//TODO CHANGE THE abort() to somthing more responsive
        abort();
    }
    do {
        printMenu();
        printf("The file has %d students in it\n", l->size);
        printf("From the menu above choose the number of the function you wish to execute and press the enter button on your keyboard: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Give the name of the student you want to add: ");
                scanf("%s", st.name);
                printf("Give the id of the student you want to add: ");
                scanf("%d", &st.id);
                //CHECKING IF THE ID IS UNIC SO WE DONT CREATE TWO STUDENTS WITH THE SAME ID
                while (id_check(st.id, l) == 1) {
                    printf("I found a student with the same id!give an other id: ");
                    scanf("%d", &st.id);
                }
                addStudent(st, l);
                printf("New student's info are successfully added to the list\n");
                break;
            case 2:
                printf("Please give the id of the student you want to delete from the list: ");
                scanf("%d", &student_id_user);
//                s = (student *) malloc(sizeof(student));
//                if (s == NULL) {
//                    printf("I need more memory!!\n");
//                    abort();
//                }
                s = findStudent(student_id_user, l);
                if (s == NULL) {
                    printf("I didn't fount the student you are looking for\n");
                    break;
                }
                st = s[0];//TODO CHECK FOR A POSSIBLE BUG
                test = deleteStudent(st, l);
                if(test == 1) {
                    printf("The student was successfully deleted from the list\n");
                }else {
                    printf("the student STILL ON THE LIST YOU ARE A CUNT AND YOU DO NOT KONW HOW TO WRITE CODE");
                }
                break;
            case 3:
                printf("Please give the id of the student you want to research from the list: ");
                scanf("%d", &student_id_user);
//                s = (student *) malloc(sizeof(student));
//                if (s == NULL) {
//                    printf("I need more memory!!");
//                    abort();
//                }
                s = findStudent(student_id_user, l);
                if (s == NULL) {
                    printf("I didn't fount the student you are looking for\n");
                    break;
                }
                st = s[0];//TODO CHECK FOR A POSSIBLE BUG
                printf("I have found the student you where looking for!!\n");
                break;
            case 4:
                printf("Please give the id of the student you want to make changes to from the list: ");
                scanf("%d", &student_id_user);
//                s = (student *) malloc(sizeof(student));
//                if (s == NULL) {
//                    printf("I need more memory!!\n");
//                    abort();
//                }
                s = findStudent(student_id_user, l);
                if (s == NULL) {
                    printf("I didn't fount the student you are looking for\n");
                    break;
                }
                st = s[0];//TODO CHECK FOR A POSSIBLE BUG
                updateStudent(st, l);
                break;
            case 5:
                student_id_user = 0;
                printf("Give the id of the student you want to see!: ");
                scanf("%d", &student_id_user);
                if (st.id == student_id_user) {
                    printf("the student's name is: %s\n", st.name);
                    printf("the student's id is: %d\n", st.id);
                } else {
                    s = findStudent(student_id_user, l);
                    if (s == NULL) {
                        printf("I didn't fount the student you are looking for\n");
                        break;
                    }
                    printf("the student's name is: %s\n", s->name);
                    printf("the student's id is: %d\n", s->id);
//                    s = (student *) malloc(sizeof(student));
//                    if (s == NULL) {
//                        printf("I need more memory!!\n");
//                        abort();
//                    }

                }
                break;

            case 6:
                printstudents(l);
                break;

                // operator doesn't match any case choice 1,2,3,4,5,6 /
            default:
                printf("Error! Try to enter a valid value!!\n");
                break;
        }

        printf("Do you want to see the main menu again?press 1(for yes) and 0(for no): ");
        scanf("%d", &option);

         while (option != 1 && option != 0) {

            printf("try to enter a valaid value(1 for yes and 0 for no): ");
            scanf("%d", &option);

        }
    }while(option == 1);
    printf("Ok, im wrapping it up!!");

    save(argc[1], l);
    list_destroy(l);
    fclose(fp);
}

