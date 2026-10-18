#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int adj[MAX][MAX];
int visited[MAX];
int n;

int queue[MAX];
int front = 0, rear = 0;

void enqueue(int v) { queue[rear++] = v; }
int  dequeue(void)  { return queue[front++]; }
int  isEmpty(void)  { return front == rear; }

void bfs(int start) {
    int i, v;
    int count = 0;

    visited[start] = 1;
    enqueue(start);

    printf("Visit order: ");
    while (!isEmpty()) {
        v = dequeue();
        printf("%d ", v);
        count++;

        for (i = 0; i < n; i++) {
            if (adj[v][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(i);
            }
        }
    }
    printf("\n");

    if (count == n) {
        printf("Graph is CONNECTED (all %d vertices reached).\n", n);
    } else {
        printf("Graph is PARTIALLY CONNECTED. Unreachable vertices: ");
        for (i = 0; i < n; i++)
            if (!visited[i]) printf("%d ", i);
        printf("\n");
    }
}

int main(void) {
    int i, j, start;

    printf("Enter number of locations (max %d): ", MAX);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter adjacency matrix (%d x %d), 0/1 values:\n", n, n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (scanf("%d", &adj[i][j]) != 1) {
                printf("Invalid input.\n");
                return 1;
            }

    printf("Enter starting vertex (0 to %d): ", n - 1);
    if (scanf("%d", &start) != 1 || start < 0 || start >= n) {
        printf("Invalid starting vertex.\n");
        return 1;
    }

    for (i = 0; i < n; i++) visited[i] = 0;

    bfs(start);
    return 0;
}
