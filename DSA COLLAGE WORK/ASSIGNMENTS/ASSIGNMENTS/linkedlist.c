#include <stdio.h>
#include <stdlib.h>

struct Node {
    int roll;
    struct Node *next;
};

struct Node *head = NULL;

struct Node *createNode(int roll) {
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    if (n == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    n->roll = roll;
    n->next = NULL;
    return n;
}

void display(void) {
    struct Node *temp = head;
    if (temp == NULL) {
        printf("Current list: (empty)\n");
        return;
    }
    printf("Current list: ");
    while (temp != NULL) {
        printf("%d", temp->roll);
        if (temp->next != NULL)
            printf(" -> ");
        temp = temp->next;
    }
    printf(" -> NULL\n");
}

int exists(int roll) {
    struct Node *temp = head;
    while (temp != NULL) {
        if (temp->roll == roll)
            return 1;
        temp = temp->next;
    }
    return 0;
}

void insertBegin(int roll) {
    struct Node *n = createNode(roll);
    n->next = head;
    head = n;
    printf("Roll number %d inserted at the beginning.\n", roll);
    display();
}

void insertEnd(int roll) {
    struct Node *n = createNode(roll);
    if (head == NULL) {
        head = n;
    } else {
        struct Node *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = n;
    }
    printf("Roll number %d inserted at the end.\n", roll);
    display();
}

void search(int roll) {
    struct Node *temp = head;
    int pos = 1;
    while (temp != NULL) {
        if (temp->roll == roll) {
            printf("Roll number %d FOUND at position %d.\n", roll, pos);
            display();
            return;
        }
        temp = temp->next;
        pos++;
    }
    printf("Roll number %d is NOT available in the list.\n", roll);
    display();
}

void deleteRoll(int roll) {
    struct Node *curr = head, *prev = NULL;

    if (head == NULL) {
        printf("List is empty. Cannot delete roll number %d.\n", roll);
        display();
        return;
    }

    while (curr != NULL && curr->roll != roll) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Roll number %d is NOT available. Deletion failed.\n", roll);
        display();
        return;
    }

    if (prev == NULL)
        head = curr->next;
    else
        prev->next = curr->next;

    free(curr);
    printf("Roll number %d deleted successfully.\n", roll);
    display();
}

void freeList(void) {
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int readInt(int *value) {
    if (scanf("%d", value) != 1) {
        clearBuffer();
        return 0;
    }
    return 1;
}

int main(void) {
    int choice, roll;

    do {
        printf("\n===== Student Roll Number Management =====\n");
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Search roll number\n");
        printf("4. Delete roll number\n");
        printf("5. Display list\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (!readInt(&choice)) {
            printf("Invalid input! Please enter a number.\n");
            choice = 0;
            continue;
        }

        switch (choice) {
        case 1:
            printf("Enter roll number: ");
            if (!readInt(&roll)) {
                printf("Invalid roll number!\n");
                break;
            }
            if (exists(roll)) {
                printf("Roll number %d already exists!\n", roll);
                display();
                break;
            }
            insertBegin(roll);
            break;

        case 2:
            printf("Enter roll number: ");
            if (!readInt(&roll)) {
                printf("Invalid roll number!\n");
                break;
            }
            if (exists(roll)) {
                printf("Roll number %d already exists!\n", roll);
                display();
                break;
            }
            insertEnd(roll);
            break;

        case 3:
            printf("Enter roll number to search: ");
            if (!readInt(&roll)) {
                printf("Invalid roll number!\n");
                break;
            }
            search(roll);
            break;

        case 4:
            printf("Enter roll number to delete: ");
            if (!readInt(&roll)) {
                printf("Invalid roll number!\n");
                break;
            }
            deleteRoll(roll);
            break;

        case 5:
            display();
            break;

        case 6:
            printf("Exiting program.\n");
            break;

        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    freeList();
    return 0;
}