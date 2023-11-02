/*1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj.koliko ima studenata
zapisanih u datoteci.Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata(ime, prezime, bodovi) i učitati iz datoteke sve zapise.Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova / max_br_bodova * 100 */


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 128
#define MAXRED 1024
#define MAXBOD 50

typedef struct {
    char name[MAXNAME];
    char surname[MAXNAME];
    int points;
}Student;

int numberOfRows(char imeDatoteke[MAXNAME]) {
    int counter = 0;
    FILE* fp = NULL;

    fp = fopen(imeDatoteke, "r");
    if (fp == NULL) {
        printf("\nFile failed to open!");
    }
    else {
        printf("\nFile opened!");
    }

    char buffer[MAXRED] = { 0 };

    while (!feof(fp)) {
        fgets(buffer, MAXRED, fp);
        if (strcmp("\n", buffer) != 0) {
            counter++;
        }
    }

    fclose(fp);
    return counter;
}

void loadStud(Student* stud, int brStud, char imeDatoteke[MAXNAME]) {
    FILE* fp = NULL;
    int i = 0;

    fp = fopen(imeDatoteke, "r");

    if (fp == NULL) {
        printf("\nFile failed to open!");
    }
    else {
        printf("\nFile opened!");
    }

    for (i = 0; i < brStud; i++) {
        fscanf(fp, "%s %s %d\n", (stud + i)->name, (stud + i)->surname, &((stud + i)->points));
    }

    fclose(fp);
    return;
}

void printStud(Student* stud, int brStud) {
    double prosjek = 0;
    int i = 0;

    for (i = 0; i < brStud; i++) {
        prosjek = (double)(stud + i)->points / MAXBOD;
        printf("\nStudent %s %s has %d points,  %.2lf percent (relative points).", (stud + i)->name, (stud + i)->surname, (stud + i)->points, prosjek * 100);
    }
}

int main() {

    char imeDatoteke[MAXNAME] = { 0 };

    FILE* test = NULL;

    while (test == NULL) {
        printf("\nEnter file name with list od students:\n");
        scanf("%s", imeDatoteke);

        test = fopen(imeDatoteke, "r");

        if (test == NULL) {
            printf("\nFile failed to open!");
        }
        else {
            printf("\nFile opened!");
            fclose(test);  // zatvori otvorenu datoteku
        }

        getchar();
    }

    int numberStud = 0;
    numberStud = numberOfRows(imeDatoteke);

    Student* stud = NULL;
    stud = (Student*)malloc(numberStud * sizeof(Student));

    if (stud == NULL) {
        printf("Aloccation failed.\n");
    }
    else {
        printf("Aloccation succesfull.\n");
    }

    loadStud(stud, numberStud, imeDatoteke);

    printStud(stud, numberStud);

    free(stud);

    return 0;
}