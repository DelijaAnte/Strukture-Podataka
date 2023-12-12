/*7. Napisati program koji pomoću vezanih listi(stabala) predstavlja strukturu direktorija.
Omogućiti unos novih direktorija i pod - direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij.Točnije program treba preko menija simulirati
korištenje DOS naredbi : 1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE 50

typedef struct node {
	char name[MAX_LINE];
	struct node* down;
	struct node* next;
}node_;

typedef node_* node;

//prototipi
int menu(node current);
int makedirectory(node root);
node changedirectory(node current);
node goback(node root, node current);
int print(node root);


int main() {

	int x = 1, r;
	char buffer[MAX_LINE];

	node root;								//postavlja početni element
	root = malloc(sizeof(node_));

	strcpy(root->name, "C:");
	root->down = NULL;
	root->next = NULL;

	node current = root;

	do {									//menu s funkcijama
		r = menu(current);

		switch (r)
		{
		case 1:
			makedirectory(current);
			break;
		case 2:
			current = changedirectory(root);
			break;
		case 3:
			current = goback(root, current);
			break;
		case 4:
			print(root);
			break;
		case 0:
			return 0;
			break;
		}

	} while (x);
}
int menu(node current) {

	int num;
	char c;

	do {
		printf("Nalazite se u \"%s\" direktoriju\n", current->name);
		printf("Pritisnite \"1\" za izradu novog direktorija\n");
		printf("Pritisnite \"2\" za promjenu direktorija\n");
		printf("Pritisnite \"3\" za vracanje na prethodni direktorij\n");
		printf("Pritisnite \"4\" za ispis direktorija\n");
		printf("Pritisnite \"0\" za izlaz iz programa\n");
		printf("Unesite:\n");

		scanf("%d", &num);

		if (num > -1 || num < 5)
		{
			return num;
		}

	} while (1);
}
int makedirectory(node root)				//izrada novog direktorija,spajanje s root-om
{
	node ptr = malloc(sizeof(node_));

	printf("Nalazite se u \"%s\" direktoriju\n", root->name);
	printf("Unesite ime datoteke koju zelite napraviti:\n");
	scanf("%s", ptr->name);

	ptr->next = root->down;
	ptr->down = NULL;
	root->down = ptr;
}
node changedirectory(node current) {																				

	node temp = current;
	char buffer[MAX_LINE];

	printf("Gdje se zelite prebaciti\n");
	scanf("%s", buffer);

	current = current->down;

	while (current != NULL && strcmp(current->name, buffer) != 0)   //traži taj direktorij
	{
		current = current->next;
	}
	if (current == NULL)
	{
		printf("Ne postoji file!", temp->name);
		return temp;
	}
	return current;

}
int print(node root)				//koristeći rekurziju printa sve članove stabla
{
	if (root == NULL)
	{
		return 0;
	}

	printf("%s\n", root->name);

	print(root->down);
	print(root->next);
}

/*Provjerava se postoji li sljedeći čvor u horizontalnom smjeru (root->next != NULL).

Ako ne postoji, provjerava se je li trenutni čvor (root) jednak čvoru koji se traži (current). Ako je, vraća taj čvor.

Ako trenutni čvor nije čvor koji se traži, pohranjuje trenutni čvor u privremenu varijablu temp i prelazi na donji čvor (root->down). Ovo je korak unazad u vertikalnom smjeru.

Ako postoji sljedeći čvor u horizontalnom smjeru, ponovno se provjerava je li to čvor koji se traži. Ako je, vraća taj čvor.

Ako nije, ponovno se kreće u horizontalnom smjeru (root->next).*/


node goback(node root, node current){								

	if (root == current)
	{
		printf("Nalazite se u %s direktoriju", root->name);
	}

	node temp = root;

	while (root->next != NULL)
	{
		if (root->next == NULL)
		{
			if (root == current)
			{
				return current;
			}
			temp = root;
			root = root->down;
		}
		else
		{
			if (root == current)
			{
				return current;
			}
			root = root->next;
		}
	}






}








