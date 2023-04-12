#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK_SIZE      100
#define MAZE_SIZE           10

typedef struct  StackObjectRec {
    short r;
    short c;
} StackObject;

StackObject  stack[MAX_STACK_SIZE];
int top = -1;
StackObject here = { 1,0 }, entry = { 1,0 };

// �̷��� �ʱ����
char maze[MAZE_SIZE][MAZE_SIZE] = {

        {'1','1','1','1','1','1','1','1','1','1'},

        {'e','1','0','1','0','0','0','1','0','1'},

        {'0','0','0','1','0','0','0','1','0','1'},

        {'0','1','0','0','0','1','1','0','0','1'},

        {'1','0','0','0','1','0','0','0','0','1'},

        {'1','0','0','0','1','0','0','0','0','1'},

        {'1','0','0','0','0','0','1','0','1','1'},

        {'1','0','1','1','1','0','1','1','0','1'},

        {'1','1','0','0','0','0','0','0','0','x'},

        {'1','1','1','1','1','1','1','1','1','1'}

};

void initialize()
{
    top = -1;
}

int isEmpty()
{
    return (top == -1);
}

int isFull()
{
    return (top == (MAX_STACK_SIZE - 1));
}

void push(StackObject item)
{
    if (isFull()) {
        printf("stack is full\n");
        exit(-1);
    }
    else
        stack[++top] = item;
}

StackObject pop()
{
    if (isEmpty()) {
        printf("stack is empty\n");
        exit(-1);
    }
    else
        return stack[top--];
}


void pushLoc(int r, int c)
{
    // r,c�� 0���� ������ push ����
    if (r < 0 || c < 0)
        return;

    // �̷��� r,1�� 1�� �ƴϰ� .�� �ƴ� ��쿡�� ���ÿ� ������ ����
    if (maze[r][c] != '1' && maze[r][c] != '.') {
        StackObject tmp;
        tmp.r = r;
        tmp.c = c;
        push(tmp);
    }
}

void printMaze(char m[MAZE_SIZE][MAZE_SIZE])
{
    int r, c;
    printf("\n\n");
    for (r = 0; r < MAZE_SIZE; r++) {
        for (c = 0; c < MAZE_SIZE; c++) {
            if (c == here.c && r == here.r)
                printf("m ");
            else {
                if (m[r][c] == 0) printf("0 ");
                else printf("%c ", m[r][c]);
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

int main()
{
    int r, c;
    here = entry;
    printMaze(maze);

    while (maze[here.r][here.c] != 'x') {
        printMaze(maze);    // �̷��� ���� ���
        r = here.r;
        c = here.c;
        maze[r][c] = '.';
        pushLoc(r - 1, c);
        pushLoc(r + 1, c);
        pushLoc(r, c - 1);
        pushLoc(r, c + 1);

        // ���ÿ��� ���� ������ ������ ����
        if (isEmpty()) {
            printf("����\n");
            return -1;
        }
        else
            here = pop();

        printMaze(maze);

    }
    printf("Success!\n");
    printf("Back count :%d", maze[r][c]);

    return 0;
}