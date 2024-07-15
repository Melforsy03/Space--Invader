#include "pantalla.h"
#include <stdio.h>

char screen[24][80];
int fin = 0;
int highScore = 0;
char scoreScreen[3][40];
void clear_screen(){
    for (int y = 0; y < 24; y++) {
        for (int x = 0; x < 80; x++) {
            screen[y][x] = ' ';
        }
    }
}
void draw_to_screen() {
    printf("\033[H"); // Mover el cursor al inicio de la pantalla

    // Dibujar la matriz "screen"
    for (int y = 0; y < 24; y++) {
        for (int x = 0; x < 80; x++) {
            printf("%c", screen[y][x]);
        }
        printf("  "); // Dejar un espacio entre las dos matrices
        
        // Dibujar la matriz "scoreScreen"
        for (int x = 0; x < 40; x++) {
            printf("%c", scoreScreen[y][x]);
        }
        printf("\n");
    }
}

void draw_bullet(int x, int y) {
    screen[y][x] = '*';
}
void displayScores( int score, int highScore) {
    // Limpiar la pantalla del puntaje
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 40; x++) {
            scoreScreen[y][x] = ' ';
        }
    }

    // Dibujar el puntaje actual
    char scoreStr[10];
    sprintf(scoreStr, "Score: %d", score);
    for (int i = 0; scoreStr[i]; i++) {
        scoreScreen[1][i] = scoreStr[i];
    }

    // Dibujar el mejor puntaje
    char highScoreStr[15];
    sprintf(highScoreStr, "High Score: %d", highScore);
    for (int i = 0; highScoreStr[i]; i++) {
        scoreScreen[2][i] = highScoreStr[i];
    }
}
void drawGameOver() {
    clear_screen();
    char nombre[9];
    strcpy(nombre, "GAME OVER");
    int i = 12;
    int j = 40;
    for (int k = 0; k < 9; k++) {
        screen[i][j] = nombre[k];
        j++;
    }
    draw_to_screen();
    fin = 1;
}
int readHighScore() {
    FILE* file = fopen("highscore.txt", "r");
    int highScore = 0;
    if (file) {
        fscanf(file, "%d", &highScore);
        fclose(file);
    }
    return highScore;
}
void saveHighScore(int score) {
    FILE* file = fopen("highscore.txt", "w");
    if (file) {
        fprintf(file, "%d", score);
        fclose(file);
    }
}




