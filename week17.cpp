#include <stdio.h>
#include <stdlib.h>

#define MAX 8 

// Danh sách kề
int graph[MAX][MAX] = {
    {0, 1, 0, 1, 0, 0, 1, 1}, // a
    {0, 0, 1, 1, 0, 0, 0, 1}, // b
    {0, 0, 0, 1, 0, 1, 1, 1}, // c
    {1, 0, 0, 0, 1, 0, 1, 0}, // d
    {0, 0, 1, 0, 0, 0, 1, 1}, // e
    {1, 1, 0, 0, 0, 0, 0, 1}, // f
    {1, 1, 1, 1, 0, 0, 0, 0}, // g
    {0, 1, 1, 0, 0, 0, 1, 0}  // h
};

int visited[MAX]; 

void bfs(int start) {
    int queue[MAX], front = 0, rear = 0;
    for (int i = 0; i < MAX; i++) visited[i] = 0;

    queue[rear++] = start;
    visited[start] = 1;

    printf("Thứ tự duyệt BFS: ");
    while (front < rear) {
        int vertex = queue[front++];
        printf("%c ", vertex + 'a');

        for (int i = 0; i < MAX; i++) {
            if (graph[vertex][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

void dfs(int vertex) {
    visited[vertex] = 1;
    printf("%c ", vertex + 'a');

    for (int i = 0; i < MAX; i++) {
        if (graph[vertex][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    bfs(0); 

    // DFS
    for (int i = 0; i < MAX; i++) visited[i] = 0; 
    printf("Thứ tự duyệt DFS: ");
    dfs(0); 
    printf("\n");

    return 0;
}
