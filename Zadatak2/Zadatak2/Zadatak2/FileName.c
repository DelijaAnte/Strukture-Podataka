/*2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable*/

#define _CRT_SECURE_NO_WARNINGS
#define NAME_MAX 50
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {				//struktura

	char name[NAME_MAX];
	char surname[NAME_MAX];
	int birthYear;
	struct Person* next;
}Person;

Person* addToTopOfList(Person* head, char name[], char surname[], int birthYear) {			//dodavanje na početak
	Person* newPerson = (Person*)malloc(sizeof(Person));
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = head;
	return newPerson;
}
void printList(Person* head) {																//printanje liste
	Person* current = head;
	while (current != NULL) {
		printf("Ime: %s, Prezime: %s, Godina rodjenja: %d\n", current->name, current->surname, current->birthYear);
		 current = current->next;
	}
}
Person* addToEndOfList(Person* head, char name[], char surname[], int birthYear) {				//dodavanje na kraj
	Person* newPerson = (Person*)malloc(sizeof(Person));
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	if (head == NULL) {
		return newPerson;
	}

	Person* current = head;											//koristim za "šetanje po listi" da bi doša do kraja
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = newPerson;
	return head;
}
Person* findBySurname(Person* head, char surname[]) {			//traži dok se ne podudara
	Person* current = head;
	while (current != NULL) {
		if (strcmp(current->surname, surname) == 0) {				//string compare funkcija kao usporeduje a kad je 0 znaci da je isto
			return current;
		}
		current = current->next;
	}
	return NULL;
}
Person* deletePerson(Person* head, char surname[]) {				//kopira s interneta, proučit kasnije
	Person* prev = NULL;
	Person* current = head;

	while (current != NULL) {
		if (strcmp(current->surname, surname) == 0) {
			if (prev == NULL) {
				head = current->next;
			}
			else {
				prev->next = current->next;
			}
			free(current);
			return head;
		}
		prev = current;
		current = current->next;
	}

	return head;
}

int main() {

	Person* list = NULL;
	int option;

	do {																	//meni za odabir funcija
		printf("\nOdaberite opciju:\n");
		printf("1. Dodaj osobu na pocetak liste\n");
		printf("2. Ispisi listu\n");
		printf("3. Dodaj osobu na kraj liste\n");
		printf("4. Pronadi osobu po prezimenu\n");
		printf("5. Obrisi osobu iz liste\n");
		printf("0. Izlaz\n");
		scanf("%d", &option);



		switch (option) {

		case 1: {															//dodaj osobu na početak

			char name[NAME_MAX];
			char surname[NAME_MAX];
			int birthYear;
			printf("\nUnesite ime: ");
			scanf("%s", name);
			printf("\nUnesite prezime: ");
			scanf("%s", surname);
			printf("\nUnesite godinu rodjenja: ");
			scanf("%d", &birthYear);
			list = addToTopOfList(list, name, surname, birthYear);
			break;
		}
		case 2:																//ispiši listu
			printf("List:\n");
			printList(list);
			break;
		case 3: {															//dodaj osobu na kraj

			char name[NAME_MAX];
			char surname[NAME_MAX];
			int birthYear;
			printf("\nUnesite ime: ");
			scanf("%s", name);
			printf("\nUnesite prezime: ");
			scanf("%s", surname);
			printf("\nUnesite godinu rodjenja: ");
			scanf("%d", &birthYear);
			list = addToEndOfList(list, name, surname, birthYear);
			break;


		}
		case 4: {															//pronađi po prezimenu
			char surnameX[50];
			printf("Unesite prezime za pretragu: ");
			scanf("%s", surnameX);
			Person* personFound = findBySurname(list, surnameX);
			if (personFound != NULL) {
				printf("Pronadjena osoba: %s %s, godina rodjenja: %d\n", personFound->name, personFound->surname, personFound->birthYear);
			}
			else {
				printf("Osoba s prezimenom %s nije pronadjena.\n", surnameX);
			}
			break;
		}
		case 5: {															//obriši element
			char deleteSurname[50];
			printf("Unesite prezime osobe koju zelite izbrisati: ");
			scanf("%s", deleteSurname);
			list = deletePerson(list, deleteSurname);
			break;
		}
		}





	} while (option != 0);													//vrti dok ne kliknes 0

}