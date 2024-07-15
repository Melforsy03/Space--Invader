#include <stdio.h>
#include <time.h>
#include "bullets.h"
#include "game.h"
#include "enemigo.h"
#include <ncurses.h>
#include <string.h>
Bullet bullets[100];
int shipX = 20, shipY = 20;
int shoot_flag = 0;
void initBullets(Bullet bullets[], int numBullets) {
    for (int i = 0; i < numBullets; i++) {
        bullets[i].x = -100;
        bullets[i].y = -100;
        bullets[i].active = 0;
    }
}
void fireBullet(Bullet bullets[], int numBullets, int shipX, int shipY, int* bulletX, int* bulletY) {
    // Buscar la primera bala inactiva o la primera bala fuera de la pantalla
    for (int i = 0; i < numBullets; i++) {
        if (bullets[i].y < 0 || !bullets[i].active) {
            bullets[i].x = shipX;
            bullets[i].y = shipY - 1;
            bullets[i].active = 1;
            *bulletX = bullets[i].x;
            *bulletY = bullets[i].y;
            return;
        }
    }
}
void updateBullets(Bullet bullets[], int numBullets) {
    for (int i = 0; i < numBullets; i++) {
        if (bullets[i].active) {
            bullets[i].y -= 1; // Mover la bala 1 píxel hacia arriba
            if (bullets[i].y < 0) { // Si la bala sale de la pantalla
                bullets[i].active = 0; // Establecer la bala como inactiva
            }
        }
    }
}
void drawBullets(Bullet bullets[], int numBullets) {
    for (int i = 0; i < numBullets; i++) {
        if (bullets[i].active) {
            draw_bullet(bullets[i].x, bullets[i].y);
        }
    }
}
void *updateAndDrawBulletsThread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        updateBullets(bullets, 100);
        drawBullets(bullets, 100);
        pthread_mutex_unlock(&mutex);
        usleep(50000); // Esperar 50 milisegundos
    }
    return NULL;
}
void* shoot_bullets(void* arg) {
    while (1) {
        if (shoot_flag) {
            int bulletX, bulletY;
            fireBullet(bullets, 100, player_x, player_y, &bulletX, &bulletY);
            shoot_flag = 0;
        }
        usleep(50000); // Esperar 50 milisegundos
    }
    return NULL;
}
void checkCollisions(Enemy enemies[], int numEnemies, Bullet bullets[], int numBullets){
    for (int i = 0; i < numEnemies; i++) {
        if (enemies[i].active) {
            for (int j = 0; j < numBullets; j++) {
                if (bullets[j].active && enemies[i].x - 1 <= bullets[j].x && bullets[j].x <= enemies[i].x + 1 && enemies[i].y - 1 <= bullets[j].y && bullets[j].y <= enemies[i].y + 1) {
                    enemies[i].health--;
                    bullets[j].active = 0;
                }
            }
        }
    }
    for (int i = 0; i < numEnemies; i++) {
        if (enemies[i].active && enemies[i].health > 0) {
            if (enemies[i].x >= player_x && enemies[i].x <= player_x + 3 && enemies[i].y == player_y) {
                // La nave ha chocado con un enemigo
                drawGameOver();
              
            }
        }
    }
    
}
