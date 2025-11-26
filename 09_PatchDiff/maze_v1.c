#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 6
#define H (2*N+1)
#define W (2*N+1)

static char maze[H][W+1];
static int used[N][N];

static void init_maze(void) {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++)
            maze[y][x] = '#';
        maze[y][W] = '\0';
    }
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            maze[2*y+1][2*x+1] = '.';
}

static void dfs(int y, int x) {
    static int dy[4] = {1,-1,0,0};
    static int dx[4] = {0,0,1,-1};
    used[y][x] = 1;

    int order[4] = {0,1,2,3};
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i+1);
        int t = order[i]; order[i] = order[j]; order[j] = t;
    }

    for (int i = 0; i < 4; i++) {
        int ny = y + dy[order[i]];
        int nx = x + dx[order[i]];
        if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
        if (used[ny][nx]) continue;

        maze[y + ny + 1][x + nx + 1] = '.';
        dfs(ny, nx);
    }
}

int main(void) {
    srand((unsigned)time(NULL));
    init_maze();
    dfs(0, 0);

    for (int i = 0; i < H; i++)
        puts(maze[i]);
    return 0;
}
