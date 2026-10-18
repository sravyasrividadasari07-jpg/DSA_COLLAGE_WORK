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

Node *findMin(Node *root) {
    while (root && root->left) root = root->left;
    return root;
}

int search(Node *root, int key) {
    while (root) {
        if (key == root->id) return 1;
        root = (key < root->id) ? root->left : root->right;
    }
    return 0;
}

Node *deleteNode(Node *root, int key) {
    if (root == NULL) return NULL;

    if (key < root->id) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->id) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL && root->right == NULL) {
            printf("Case 1: node %d is a leaf (0 children).\n", key);
            free(root);
            return NULL;
        }
        if (root->left == NULL) {
            printf("Case 2: node %d has one child (right: %d).\n", key, root->right->id);
            Node *temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            printf("Case 2: node %d has one child (left: %d).\n", key, root->left->id);
            Node *temp = root->left;
            free(root);
            return temp;
        }
        Node *succ = findMin(root->right);
        printf("Case 3: node %d has two children; replaced by inorder successor %d.\n",
               key, succ->id);
        root->id = succ->id;
        root->right = deleteNode(root->right, succ->id);
    }
    return root;
}

void inorder(Node *root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->id);
    inorder(root->right);
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

    printf("\nInorder before deletion: ");
    inorder(root);
    printf("\n");

    printf("\nEnter ID to delete: ");
    scanf("%d", &key);

    if (!search(root, key)) {
        printf("ID %d not found; nothing deleted.\n", key);
    } else {
        root = deleteNode(root, key);
        printf("ID %d deleted.\n", key);
    }

    printf("\nInorder after deletion : ");
    inorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}
