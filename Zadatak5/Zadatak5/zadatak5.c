#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH (1024)

struct Element;
typedef struct Element* Position;
typedef struct Element {
    double number;
    Position next;
} element;

int calculatePostfixFromFILE(Position head, char* fileName, double* result);
int readFILE(char* fileName, char* buffer);
int stringIntoPostfix(Position head, char* buffer, double* result);
int performOperation(Position head, char operation, double* result);
int pop(Position head, double* result);
int push(Position head, Position newElement);
int printStack(Position first);
Position createElement(double number);
int extractResult(Position head, double* result);

// main
int main() {
    element head = { .number = 0, .next = NULL };
    double result = 0;

    if (calculatePostfixFromFILE(&head, "postfix.txt", &result) == EXIT_SUCCESS) {
        printf("Result is: %lf\n", result);
    }
    else {
        printf("Error calculating result.\n");
    }

    return EXIT_SUCCESS;
}

// functions

// function for calculating the postfix
int calculatePostfixFromFILE(Position head, char* fileName, double* result) {
    char buffer[MAX_LENGTH] = { 0 };

    if (readFILE(fileName, buffer) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    return stringIntoPostfix(head, buffer, result);
}

// read file function so we can calculate postfix
int readFILE(char* fileName, char* buffer) {
    FILE* filepointer = fopen(fileName, "r");
    if (!filepointer) {
        printf("ERROR WHILE OPENING FILE\n");
        return EXIT_FAILURE;
    }

    fgets(buffer, MAX_LENGTH, filepointer);
    fclose(filepointer);

    return EXIT_SUCCESS;
}

// transform string into postfix
int stringIntoPostfix(Position head, char* buffer, double* result) {
    char* currentBuffer = buffer;
    int numofbytes = 0;
    char operation;
    double number;
    Position newElement;

    while (*currentBuffer != '\0') {
        int current = sscanf(currentBuffer, "%lf %n", &number, &numofbytes);
        if (current != 1) {
            sscanf(currentBuffer, " %c %n", &operation, &numofbytes);
            current = performOperation(head, operation, result);
        }

        if (current != EXIT_SUCCESS) {
            printf("Error in processing input.\n");
            return EXIT_FAILURE;
        }

        newElement = createElement(number);
        if (!newElement) {
            printf("Error creating new element.\n");
            return EXIT_FAILURE;
        }
        currentBuffer += numofbytes;
        push(head, newElement);
    }

    return extractResult(head, result);
}

// function for operations
int performOperation(Position head, char operation, double* result) {
    double member1 = 0;
    double member2 = 0;
    int status1 = 0;
    int status2 = 0;

    status1 = pop(head, &member1);
    if (status1 != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    status2 = pop(head, &member2);
    if (status2 != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    // switch case for possible operations
    switch (operation) {
    case '+':
        *result = member1 + member2;
        break;
    case '-':
        *result = member2 - member1; 
        break;
    case '*':
        *result = member1 * member2;
        break;
    case '/':
        if (member1 == 0) {
            printf("Error: Division by zero.\n");
            return EXIT_FAILURE;
        }
        *result = member2 / member1; 
        break;
    default:
        printf("Operation does not exist or is not supported\n");
        return EXIT_FAILURE;
    }

    return push(head, createElement(*result));
}

// pops (removes element from top of stack)
int pop(Position head, double* result) {
    Position forDeleting = head->next;
    if (!forDeleting) {
        printf("Error: Stack is empty\n");
        return EXIT_FAILURE;
    }

    head->next = forDeleting->next;
    *result = forDeleting->number;
    free(forDeleting);

    return EXIT_SUCCESS;
}

// pushes (adds new element on top)
int push(Position head, Position newElement) {
    newElement->next = head->next;
    head->next = newElement;


    return EXIT_SUCCESS;
}

int printStack(Position first) {
    Position current = first;

    while (current) {
        printf(" %lf", current->number);
        current = current->next;
    }

    printf("\n");

    return EXIT_SUCCESS;
}

Position createElement(double number) {
    Position newElement = (Position)malloc(sizeof(element));
    if (!newElement) {
        printf("ERROR WHILE ALLOCATING\n");
        return NULL;
    }

    newElement->number = number;
    newElement->next = NULL;

    return newElement;
}

int extractResult(Position head, double* result) {
    int status = pop(head, result);
    if (status != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
