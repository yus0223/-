#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 7
#define HEIGHT 10

char stairs[HEIGHT][WIDTH];
int playerX, playerY;

void initStairs() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            stairs[i][j] = ' ';
        }
    }
    for (int i = 0; i < HEIGHT; i++) {
        int stairPos = rand() % WIDTH;
        stairs[i][stairPos] = '#';
    }
}

void draw() {
    system("cls");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == playerY && j == playerX) {
                printf("@");
            } else {
                printf("%c", stairs[i][j]);
            }
        }
        printf("\n");
    }
}

int playGame() {
    initStairs();

    playerY = 0;
    for (playerX = 0; playerX < WIDTH; playerX++) {
        if (stairs[0][playerX] == '#') break;
    }

    draw();
    printf("遊戲開始！用 'a' 向左，'d' 向右。按任意鍵繼續...\n");
    getch();

    while (1) {
        // 讀鍵盤輸入 (非阻塞)
        if (kbhit()) {
            char ch = getch();
            if (ch == 'a' && playerX > 0) playerX--;
            else if (ch == 'd' && playerX < WIDTH - 1) playerX++;
        }

        playerY++;
        if (playerY >= HEIGHT) {
            draw();
            printf("恭喜！你安全下到樓梯底部！\n");
            return 1;
        }

        if (stairs[playerY][playerX] != '#') {
            draw();
            printf("踩空了，遊戲結束！\n");
            return 0;
        }

        draw();
        Sleep(400);
    }
}

int main() {
    srand((unsigned int)time(NULL));
    char choice;

    do {
        playGame();

        printf("想再玩一次嗎？(y/n): ");
        // 使用getch()避免輸入緩衝問題
        choice = getch();
        printf("%c\n", choice);

        // 清除可能的多餘輸入（換行）
        while (kbhit()) getch();

    } while (choice == 'y' || choice == 'Y');

    printf("謝謝遊玩！再見！\n");
    return 0;
}
