#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL 100

struct Page {
    char url[MAX_URL];
    struct Page *prev;
    struct Page *next;
};

struct Page *head = NULL;
struct Page *tail = NULL;
struct Page *current = NULL;

struct Page *createPage(const char *url) {
    struct Page *p = (struct Page *)malloc(sizeof(struct Page));
    if (p == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strncpy(p->url, url, MAX_URL - 1);
    p->url[MAX_URL - 1] = '\0';
    p->prev = NULL;
    p->next = NULL;
    return p;
}

void showCurrent(void) {
    if (current == NULL)
        printf("Current page: (none)\n");
    else
        printf("Current page: %s\n", current->url);
}

void displayForward(void) {
    struct Page *temp = head;
    if (temp == NULL) {
        printf("History (first to last): (empty)\n");
        return;
    }
    printf("History (first to last):\n");
    while (temp != NULL) {
        printf("  %s%s\n", temp->url, (temp == current) ? "   <-- current" : "");
        temp = temp->next;
    }
}

void displayBackward(void) {
    struct Page *temp = tail;
    if (temp == NULL) {
        printf("History (last to first): (empty)\n");
        return;
    }
    printf("History (last to first):\n");
    while (temp != NULL) {
        printf("  %s%s\n", temp->url, (temp == current) ? "   <-- current" : "");
        temp = temp->prev;
    }
}

void visitPage(const char *url) {
    struct Page *p = createPage(url);

    if (head == NULL) {
        head = p;
        tail = p;
    } else {
        tail->next = p;
        p->prev = tail;
        tail = p;
    }
    current = p;
    printf("Visited: %s\n", url);
    showCurrent();
}

void goBack(void) {
    if (current == NULL) {
        printf("No pages in history.\n");
        return;
    }
    if (current->prev == NULL) {
        printf("Already at the FIRST page. Cannot go back.\n");
    } else {
        current = current->prev;
        printf("Moved back.\n");
    }
    showCurrent();
}

void goForward(void) {
    if (current == NULL) {
        printf("No pages in history.\n");
        return;
    }
    if (current->next == NULL) {
        printf("Already at the LAST page. Cannot go forward.\n");
    } else {
        current = current->next;
        printf("Moved forward.\n");
    }
    showCurrent();
}

void deletePage(const char *url) {
    struct Page *temp = head;

    if (head == NULL) {
        printf("History is empty. Nothing to delete.\n");
        return;
    }

    while (temp != NULL && strcmp(temp->url, url) != 0)
        temp = temp->next;

    if (temp == NULL) {
        printf("Page \"%s\" not found. Deletion failed.\n", url);
        showCurrent();
        return;
    }

    if (temp == current) {
        if (temp->next != NULL)
            current = temp->next;
        else
            current = temp->prev;
    }

    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;
    else
        tail = temp->prev;

    free(temp);
    printf("Page \"%s\" deleted.\n", url);
    showCurrent();
}

void freeAll(void) {
    struct Page *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
    current = NULL;
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
    int choice;
    char url[MAX_URL];

    do {
        printf("\n===== Web Browser History =====\n");
        printf("1. Visit a new page\n");
        printf("2. Go back\n");
        printf("3. Go forward\n");
        printf("4. Delete a page\n");
        printf("5. Display first to last\n");
        printf("6. Display last to first\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (!readInt(&choice)) {
            printf("Invalid input! Please enter a number.\n");
            choice = 0;
            continue;
        }

        switch (choice) {
        case 1:
            printf("Enter page URL: ");
            scanf("%99s", url);
            clearBuffer();
            visitPage(url);
            break;

        case 2:
            goBack();
            break;

        case 3:
            goForward();
            break;

        case 4:
            printf("Enter page URL to delete: ");
            scanf("%99s", url);
            clearBuffer();
            deletePage(url);
            break;

        case 5:
            displayForward();
            break;

        case 6:
            displayBackward();
            break;

        case 7:
            printf("Exiting program.\n");
            break;

        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 7);

    freeAll();
    return 0;
}