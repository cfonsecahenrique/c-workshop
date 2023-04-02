/* 
 * File:  part3.c
 * Author:  cfonsecahenrique
 * Created on:  Fri Mar 30 2022
 * Example of Linked List and associated 
 * functions built in/for the C Workshop
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#define MAXNAMESIZE 101

typedef struct student {
    char name[MAXNAMESIZE];
    int nota;
    struct student *next;
} Student;

void printStudent(Student *s) {
    printf("[Nome: %s; Nota: %d]\n", s->name, s->nota);
    fflush(stdout);
    return;
}

Student* bestInClass(Student *head) {
    /* Finds the (first) student with the highest grade,
        returns its pointer */
    Student* best = head;
    if(head==NULL) {
        printf("[bestInClass Error]: List is empty!\n");
        return head;
    }
    while(head) {
        if(head->nota > best->nota)
            best=head;
        head = head->next;
    }
    return best;
}

int isInList(Student *head, char name[MAXNAMESIZE]) {
    /* Returns 1 if the a student (by name) is in
    the llist headed by *head, 0 otherwise.*/
    while(head) {
        if(strcmp(head->name, name)==0)
            return 1;
        head = head->next;
    }
    return 0;
}

Student* addStudent(Student *head, char name[MAXNAMESIZE], int grade) {
    /* Adds a new student to the llist headed by *head */
    Student* temp = head;

    /* First check if it's a duplicate */
    if(isInList(head, name)) {
        printf("[addStudent Error]: Student %s already in!\n", name);
        fflush(stdout);
        return head;
    }

    if(head==NULL) {    /* First case */
        head = malloc(sizeof(Student));
        head->nota = grade;
        strcpy(head->name, name);
        head->next = NULL;
    }
    else { /* All other cases */
        /* Cycle to get to the end of the llist */
        /* (would be more efficient to have a *tail) */
        while(temp->next)
            temp = temp->next;
        temp->next = malloc(sizeof(Student));
        temp->next->nota = grade;
        strcpy(temp->next->name, name);
        temp->next->next = NULL;
    }

    return head;
}

Student* removeStudent(Student* head, char name[MAXNAMESIZE]) {
    /* Receives a Student's name, removes it from the llist,
    returns head of llist*/
    Student* anterior=NULL;
    Student* temp = head;

    if(head==NULL) {
        printf("[Remove Error]: List is empty!\n");
        return head;
    }

    /*What if the searched student is the list's head?*/
    if(strcmp(head->name, name)==0) {
        head = head->next;
        free(temp);
        return head;
    }

    /*Search through the linked list*/
    while(temp) {
        if(strcmp(temp->name, name)==0) {
            break;
        }
        anterior = temp;
        temp = temp->next;
    }

    /*If we didn't find anyone with such name,
    temp will be null (because we're out of the while loop)*/
    if(temp==NULL) {
        printf("Student %s not found.\n", name);
        return head;
    }

    /*Re-link the structures without the removed link*/
    anterior->next = temp->next;
    free(temp);
    printf("Student %s removed from list.\n", name);
    return head;
}

int findNstudents(Student* head) {
    /* Counts how many elements exist in the llist */
    int count = 0;
    while(head) {
        count++;
        head = head->next;
    }
    return count;
}

void listStudents(Student* head) {
    /* Prints to the stdout the whole llist */
    if(head==NULL) {
        printf("list: List is empty!\n");
        return;
    }
    while(head) {
        putchar('\t');
        printStudent(head);
        if(head->next != NULL) {
            printf("  \t\t|\n");
            printf("  \t\tv\n");
        }
        head = head->next;
    }
    printf("   \t\t|\n");
    printf("   \t\tv\n");
    printf("\t\tNULL\n");
    return;
}

void destroy(Student* first) {
    /* Receives the head of a llist
    frees all of its respective memory */
    Student* aux;
    while(first) {
        aux = first;
        first = first->next;
        free(aux);
    }
}

int main() {
    int val, nstudents;
    char name[MAXNAMESIZE], c, toSearch[MAXNAMESIZE];
    /* Initialize a llist head */
    Student *head = NULL;

    while((c=getchar())!='q' || c==EOF) {
        if(isspace(c)) continue;
        else if(c=='b') { /*b: find best student*/
            printStudent(bestInClass(head));
        }
        else if(c=='a') { /*a: add student <name, val>*/
            scanf("%s%d", name, &val);
            head = addStudent(head, name, val);
        }
        else if(c=='c') { /*c: count number of students*/
            nstudents = findNstudents(head);
            printf("Total n of students = %d\n", nstudents);
            fflush(stdout);
        }
        else if(c=='r') { /*r: remove student <name>*/
            scanf("%s", toSearch);
            head = removeStudent(head, toSearch);
        }
        else if(c=='l') { /*l: list all students visually*/
            listStudents(head);
        }
    }

    destroy(head);
    return 0;
}
