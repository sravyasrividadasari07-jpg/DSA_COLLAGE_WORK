#include <stdio.h>

#define MAX 20
#define INF 1000000000

int adj[MAX][MAX];
int dist[MAX];
int done[MAX];
int n;

int minVertex(void) {
    int i, best = -1;
    for (i = 0; i < n; i++) {
        if (!done[i] && dist[i] != INF && (best == -1 || dist[i] < dist[best]))
            best = i;
    }
    return best;
}

void dijkstra(int src) {
    int i, u, v;

    for (i = 0; i < n; i++) {
        dist[i] = INF;
        done[i] = 0;
    }
    dist[src] = 0;

    for (i = 0; i < n; i++) {
        u = minVertex();
        if (u == -1) break;
        done[u] = 1;

        for (v = 0; v < n; v++) {
            if (adj[u][v] > 0 && !done[v] && dist[u] + adj[u][v] < dist[v])
                dist[v] = dist[u] + adj[u][v];
        }
    }
}

int main(void) {
    int i, j, src;

    printf("Enter number of vertices (max %d): ", MAX);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter weighted adjacency matrix (%d x %d), 0 = no road:\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (scanf("%d", &adj[i][j]) != 1 || adj[i][j] < 0) {
                printf("Invalid input (weights must be non-negative integers).\n");
                return 1;
            }
        }
    }

    printf("Enter source vertex (0 to %d): ", n - 1);
    if (scanf("%d", &src) != 1 || src < 0 || src >= n) {
        printf("Invalid source vertex.\n");
        return 1;
    }

    dijkstra(src);

    printf("\nShortest distances from source %d:\n", src);
    printf("Destination   Distance\n");
    for (i = 0; i < n; i++) {
        if (dist[i] == INF)
            printf("%-14dINF (unreachable)\n", i);
        else
            printf("%-14d%d\n", i, dist[i]);
    }
    return 0;
}