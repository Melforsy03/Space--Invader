#include <stdio.h>
#ifndef PANTALLA_H
#define PANTALLA_H
extern char screen[][80];
extern char scoreScreen[][40];
extern int score ;
extern int highScore ;
extern int fin ;
void clear_screen();
void draw_to_screen();
void draw_bullet(int x, int y);
void displayScores(int score, int highScore);
void draw_score_screen();
void drawGameOver();
#endif 
