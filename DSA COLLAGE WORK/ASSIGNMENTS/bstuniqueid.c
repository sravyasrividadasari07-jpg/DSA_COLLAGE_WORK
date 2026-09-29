#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int id;
    struct Node *left, *right;
} Node;

Node *createNode(int id) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) { printf("Memory allocation failed\n"); exit(1); }
    n->id = id;
    n->left = n->right = NULL;
    return n;
}

Node *insert(Node *root, int id) {
    if (root == NULL) return createNode(id);
    if (id < root->id)
        root->left = insert(root->left, id);
    else if (id > root->id)
        root->right = insert(root->right, id);
    else
        printf("ID %d already exists, skipped.\n", id);
    return root;
}

void inorder(Node *root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->id);
    inorder(root->right);
}

void preorder(Node *root) {
    if (!root) return;
    printf("%d ", root->id);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->id);
}

int search(Node *root, int key) {
    while (root) {
        if (key == root->id) return 1;
        root = (key < root->id) ? root->left : root->right;
    }
    return 0;
}

void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    Node *root = NULL;
    int n, id, key;

    printf("Enter number of IDs to insert: ");
    scanf("%d", &n);

    printf("Enter %d ID numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &id);
        root = insert(root, id);
    }

    printf("\nInorder   : "); inorder(root);
    printf("\nPreorder  : "); preorder(root);
    printf("\nPostorder : "); postorder(root);
    printf("\n");

    printf("\nEnter ID to search: ");
    scanf("%d", &key);
    if (search(root, key))
        printf("ID %d exists in the tree.\n", key);
    else
        printf("ID %d does not exist in the tree.\n", key);

    freeTree(root);
    return 0;
}