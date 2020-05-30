//
// Created by thanos chourlias on 25/4/20.
//
#include "student.h"

void printMenu(){
    char out[100] = {0};
    memset(out, '#', 99);
    printf("%s\n", out);
    printf("1.Registration of a new student\n");
    printf("2.Delete an existing student, based on their id\n");
    printf("3.Search an existing student, based on their id\n");
    printf("4.Customize an existing student's information, based on their id\n");
    printf("5.Print a specific student's information\n");
    printf("6.Print the information from every student in the file\n");
    printf("%s\n", out);
    return;
}
student* load(char *filename){
    FILE *fp;
    fp = fopen( filename,"r+");
    if (  fp == NULL ){
        printf("file could not be accessed");
        return NULL;
    }
    fseek(fp, 0,SEEK_END);
    long filesize = ftell(fp);
    int numstudents = filesize / sizeof(student);
    student *s = (student *)malloc(sizeof(student)*numstudents);
    if(s == NULL){
        printf("I need more memory!!");
        abort();
    }
    fseek(fp,0,SEEK_SET);
    fread(s , sizeof(student),numstudents,fp);
    fclose(fp);

    return s;



}//ανάκτηση λίστας φοιτητών από αρχείο

//student creatStudent(){
//    student st;
//    int id;
//    char name[MAXSTRING];
//    printf("Give the name of the student you want to add: ");
//    scanf("%s", st.name);
//    printf("Give the id of the student you want to add: ");
//    scanf("%d", &st.id);
//
//    return st;
//}

int addStudent(student st, list l){
    printf("Im adding the new student's info to the list......\n");
    list_insertfirst(l,list_newnode(st));
    return 0;
}//προσθήκη νέου student

void save(char *filename, list l){
    FILE *fp;
    fp = fopen( filename,"w+");
    if (  fp == NULL ){
        printf("file could not be accessed");
        return;
    }
    node current = list_first(l);
    while(current != NULL){
        fwrite(&current->st,sizeof(student),1,fp);
        current = current->next;
    }
    fclose(fp);
    return;

} //αποθήκευση λίστας φοιτητών σε αρχείο

void printstudents(list l){
    node current = list_first(l);
    int num_of_student = 1;
    while(current != NULL){
        if(num_of_student == 1){
            printf("the name of the %dst student is: %s\n",num_of_student, current->st.name);
            printf("the id of the %dst student is: %d\n",num_of_student,  current->st.id);
        }else if(num_of_student == 2){
            printf("the name of the %dnd student is: %s\n",num_of_student, current->st.name);
            printf("the id of the %dnd student is: %d\n",num_of_student,  current->st.id);
        }else if(num_of_student == 3){
            printf("the name of the %drd student is: %s\n",num_of_student, current->st.name);
            printf("the id of the %drd student is: %d\n",num_of_student,  current->st.id);
        }else {
            printf("the name of the %dth student is: %s\n",num_of_student, current->st.name);
            printf("the id of the %dth student is: %d\n",num_of_student,  current->st.id);
        }
        current = current->next;
        num_of_student++;
    }
    return;
}

void print(student st){
    //We ask the user in to the main to give us the id of the student we want to find for him and we call the findStudent function where we check if the student exists
    printf("the name of the student is: %s\n",st.name);
    printf("the id of the student is: %d\n",st.id);

    return;
}

student* findStudent(int id, list l){
    student *s = (student *)malloc(sizeof(student));
    if(s == NULL){
        printf("I need more memory!!\n");
        abort();
    }
    s = NULL;///IN CASE THE ID IS NOT FOUND IT RETURNS NULL SO YOU KNOW THAT THE STUDENT IS NOT IN THE LIST
    node current = list_first(l);
    while(current != NULL){
        if(current->st.id == id){
            printf("I found the student you are looking for!\n");
            s = &current->st;
            return s;
        }
        current = current->next;
    }

    return s;
} //αναζήτηση του student από το linked-list με βάση το id 

///The function returns 1 if the student was deleted and 0 otherwise
int deleteStudent(student st, list l){
    node current = list_first(l);
    node nextn = current->next;
    while(nextn != NULL){
        if(nextn->st.id == st.id){
            current->next = nextn->next;
            nextn->next = NULL;
            l->size--;
            return 1;
        }
        current = nextn;
        nextn = nextn->next;
    }
    return 0;
}//διαγραφή με βάση το st.id

int updateStudent(student st, list l){
    int choice,id_usr;
    char name_usr[MAXSTRING];
    node current = list_first(l);
    while(current != NULL){
        if(current->st.id == st.id){
            printf("Do you want to change the name of the student, the id of the student, or both?please type a number respectively(1,2,3): ");
            fscanf(stdin, "%d",&choice);
            while(choice != 1 && choice != 2 && choice != 3){
                printf("Error! Try to enter a valid value!!: ");
                fscanf(stdin, "%d",&choice);
            }
            if(choice == 1){
                /*IF THE USER WANTS TO CHANGE ONLY THE NAME OF THE STUDENT*/
                printf("Give the new name that you want to store at this student(with id: %d): ",current->st.id);
                scanf("%s",name_usr);
                strcpy(current->st.name, name_usr);
                printf("The student's name was successfully changed to %s\n",name_usr);

            }else if(choice == 2){
                /*IF THE USER WANTS TO CHANGE ONLY THE ID OF THE STUDENT*/
                printf("Give the new name that you want to store at this student(with id: %d): ",current->st.id);
                scanf("%d",&id_usr);
                while(id_check(id_usr, l) == 1) {
                    printf("I found a student with the same id!give an other id: ");
                    scanf("%d",&id_usr);
                }
                current->st.id = id_usr;
                printf("The student's id was successfully changed to %d\n",id_usr);

            }else {
                /*IF THE USER WANTS TO CHANGE BOTH ID AND NAME OF THE STUDENT, CHECK IS NOT NECESSARY BECAUSE OF THE WHILE */
                printf("Give the new name that you want to store at this student(with id: %d): ",current->st.id);
                scanf("%s",name_usr);
                printf("Give the new id that you want to store at this student(with id: %d): ",current->st.id);
                scanf("%d",&id_usr);
                while(id_check(id_usr, l) == 1) {
                    printf("I found a student with the same id!give an other id: ");
                    scanf("%d",&id_usr);
                }
                strcpy(current->st.name, name_usr);
                current->st.id = id_usr;

            }
        }
        current = current->next;
    }
    return 1;//IF THE USER SUCCESFULLY CHANGED SOMTHING IN A STUDENT
}//ανανέωση με βάση το st.id

int id_check(int id, list l){
    node current = list_first(l);
    while(current != NULL){
        if(current->st.id == id){
            return 1;
        }
        current = current->next;
    }
    return 0;///THE FUNCTION RETURN 0 IF IT DOES'S FOUND AN OTHER STUSDENT WITH THE SAME ID.OTHERWISE IT RETURNS ONE.
}//checking if the id is unic or there is an other object/student on the list with the same id

///Code for the linked lists and the declaration's for the functions

list list_create() {
    list l = (list) malloc(sizeof(struct _list));
    assert(l);
    l->head = NULL;
    l->size = 0;
    return l;
}

void list_insertfirst(list l , node n){
    assert(l && n);
    n->next = l->head;
    l->head = n;
    l->size++;
}

node list_newnode(student st){
    node n = (node) malloc(sizeof(struct _node));
    assert(n);
    n->st = st;///TODO POSSIBLE BUG
    n->next = NULL;
    return n;
}

/* destroy list and free memory */
void list_destroy(list l) {
    while (!list_empty(l)){
        list_freenode(list_deletefirst(l));
    }
    free(l);
}

void list_freenode(node n) {
    assert(n);
    free(n);
}

int list_empty(list l) {
    assert(l);
    return l->head == NULL;
}

node list_deletefirst(list l){
    assert(l);
    node ret = l->head;
    l->head = ret->next;
    l->size--;
    ret->next = NULL;
    return ret;
}

node list_first(list l) {
    assert(l);
    return l->head;
}

int list_studentsinfo(node n) {
    assert(n);
    printf("the name of the student is: %s", n->st.name);
    printf("the id of the student is: %d", n->st.id);
    return 0;
}