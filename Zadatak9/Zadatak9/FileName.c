/*9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u čvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraća
pokazivač na korijen stabla.
b) Napisati funkciju replace koja će svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat će se u stablo na
slici Slika 2.
c) Prepraviti program na način da umjesto predefiniranog cjelobrojnog polja korištenjem
funkcije rand() generira slučajne brojeve u rasponu <10, 90>. Također, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
dijela zadatka.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct _node;
typedef struct _node* Position;

typedef struct _node {
    int element;
    Position left;
    Position right;
} Node;

Position createNode(int value);
Position insert(Position root, int value);
void inorderToFile(Position root, FILE* filePointer);
void inorderToConsole(Position root); // function for testing
int replace(Position root);
int getRandomValue();

int main() {
    Position root = NULL;
    Position rootRand = NULL;
    FILE* filePointer = fopen("inorder.txt", "w");
    srand(time(0));

    root = insert(root, 2);
    insert(root, 5);
    insert(root, 7);
    insert(root, 8);
    insert(root, 11);
    insert(root, 1);
    insert(root, 4);
    insert(root, 2);
    insert(root, 3);
    insert(root, 7);

    fprintf(filePointer, "a) binary tree: ");
    inorderToFile(root, filePointer);
    fprintf(filePointer, "\n");

    replace(root);
    fprintf(filePointer, "b) binary tree: ");
    inorderToFile(root, filePointer);
    fprintf(filePointer, "\n");

    rootRand = insert(rootRand, getRandomValue());
    for (int i = 0; i < 10; i++) {
        insert(rootRand, getRandomValue());
    }
    fprintf(filePointer, "c) binary tree: ");
    inorderToFile(rootRand, filePointer);

    fclose(filePointer);
    return 0;
}

Position createNode(int value) {
    Position newNode = (Position)malloc(sizeof(Node));
    if (!newNode) {
        printf("Can't allocate memory!\n");
        return NULL;
    }

    newNode->element = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Position insert(Position root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value >= root->element)
        root->left = insert(root->left, value);
    else if (value < root->element)
        root->right = insert(root->right, value);

    return root;
}

void inorderToFile(Position root, FILE* filePointer) {
    if (root != NULL) {
        inorderToFile(root->left, filePointer);
        fprintf(filePointer, "%d ", root->element);
        inorderToFile(root->right, filePointer);
    }
}

void inorderToConsole(Position root) {
    if (root != NULL) {
        inorderToConsole(root->left);
        printf("%d ", root->element);
        inorderToConsole(root->right);
    }
}

int replace(Position root) {
    int leftElement = 0;
    int rightElement = 0;
    int originalElement = 0;

    if (root == NULL) {
        return 0;
    }

    leftElement = replace(root->left);
    rightElement = replace(root->right);
    originalElement = root->element;

    root->element = leftElement + rightElement;
    return originalElement + root->element;
}

int getRandomValue() {
    return rand() % 81 + 10;
}