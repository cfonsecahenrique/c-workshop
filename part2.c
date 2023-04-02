/* 
 * File:  part2.c
 * Author:  cfonsecahenrique
 * Created on:  Fri Mar 30 2022
 * Example of Implementation of double pointer array of Structs
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAXNAMESIZE 101

typedef struct student {
    char name[MAXNAMESIZE];
    int nota;
} Student;

void printStudent(Student *s) {
    printf("\tNome: %s; Nota: %d\n", s->name, s->nota);
    return;
}

Student *bestInClass(Student **cl, int size) {
    int i, max=0, ix=0;
    for(i=0; i<size; i++) {
        if(cl[i]->nota > max) {
            max = cl[i]->nota;
            ix = i;
        }
    }
    return cl[ix];
}

void destroy(Student **cl, int size) {
    int i=0;
    for(i=0; i<size; i++)
        free(cl[i]);
    free(cl);
    return;
}

int main() {
    char str[MAXNAMESIZE];
    int val, nstudents = 0;
    Student *s;
    /*Initialize the 'set' with one element*/
    Student **class = malloc(sizeof(Student));

    while(scanf("%s%d", str, &val)==2) {
        s = malloc(sizeof(Student));
        /*Check if memory was correctly allocated*/
        assert(s!=NULL);
        strcpy(s->name, str);
        s->nota = val;
        class = realloc(class, sizeof(Student)*(nstudents+1));
        class[nstudents] = s;
        nstudents++;
    }

    printf("Found best student:\n");
    printStudent(bestInClass(class, nstudents));

    destroy(class, nstudents);
    
    return 0;
}