#include <pthread.h>
#include<stdio.h>
#ifndef ENEMIGOS
#define ENEMIGOS
typedef struct {
    int x, y;
    int health;
    int health2;
    int active;
    int direction;
    pthread_t thread;
} Enemy;
extern Enemy enemies[];
extern int  enemiesEliminated ;
extern int score ;
void* enemyThread(void* arg);
void initEnemies(Enemy enemies[], int numEnemies);
void* enemiesThread(void* arg) ;
void reinitializeEnemies(Enemy enemies[], int numEnemies);
void drawEnemies(Enemy enemies[], int numEnemies);
#endif 