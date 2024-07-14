
#include "enemigo.h"
#ifndef BULLETS_H
#define BULLETS_H
typedef struct {
    int x, y;
    int size;
    int active;
} Bullet;
extern Bullet bullets[];
extern int shipX;
extern int shipY;
extern char screenBuffer[][80];
extern int shoot_flag ;
void fireBullet(Bullet bullets[], int numBullets, int shipX, int shipY, int* bulletX, int* bulletY);
void updateBullets(Bullet bullets[], int numBullets);
void drawBullets(Bullet bullets[], int numBullets);
void* updateAndDrawBulletsThread(void* arg);
void initBullets(Bullet bullets[], int numBullets);
void* shoot_bullets(void* arg);
void checkCollisions(Enemy enemies[], int numEnemies, Bullet bullets[], int numBullets);
#endif 
