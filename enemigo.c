#include  <stdio.h>
#include "enemigo.h"
#include "pantalla.h"
#include "game.h"
Enemy enemies [100];
int enemyMoveDelay = 100000; // Tiempo de espera entre movimientos de los enemigos (en microsegundos)
int score = 0;

void initEnemies(Enemy enemies[], int numEnemies) {
    int startX = 0; // Posición X inicial en la esquina superior izquierda
    int startY = 2; // Posición Y inicial en la primera fila
    //int enemiesPerRow = 10; // Número máximo de enemigos por fila
    
    for (int i = 0; i < numEnemies; i++) {
        // Verificar si hay espacio suficiente en la fila actual
        while (screen[startY][startX] != ' ' || screen[startY][startX + 1] != ' ' || screen[startY][startX + 2] != ' ' || screen[startY][startX + 3] != ' ') {
            startX += 4; // Avanzar 4 posiciones (ancho de cada enemigo más un espacio)
            
            // Si se llega al final de la pantalla, pasar a la siguiente fila
            if (startX + 3 >= 79) {
                startX = 0; // Reiniciar la posición X
                startY++; // Pasar a la siguiente fila
            }
        }
        
        enemies[i].x = startX;
        enemies[i].y = startY;
        enemies[i].health = (rand_r(&(unsigned int){time(NULL) ^ i}) % 3) + 1;
        enemies[i].health2 = enemies[i].health;
        enemies[i].active = 0; // Inicialmente, todos los enemigos están inactivos
        enemies[i].thread = (pthread_t)0;
        pthread_create(&enemies[i].thread, NULL, enemyThread, &enemies[i]);
        
        // Avanzar 4 posiciones (ancho de cada enemigo más un espacio) para el siguiente enemigo
        startX += 4;
        
        // Si se llega al final de la fila, pasar a la siguiente fila
        if (startX + 3 >= 79) {
            startX = 0; // Reiniciar la posición X
            startY++; // Pasar a la siguiente fila
        }
    }
}

void* enemyThread(void* arg) {

    Enemy* enemy = (Enemy*)arg;
    
    // Esperar hasta que la coordenada inicial del enemigo esté desocupada
    while (screen[enemy->y][enemy->x] != ' '&& screen[enemy->y][enemy->x -1 ] != ' ' && screen[enemy->y][enemy->x + 1] != ' ' && screen[enemy->y][enemy->x + 2] != ' ') {
        usleep(enemyMoveDelay); // Esperar el tiempo de movimiento de los enemigos
    }
    
    enemy->active = 1; // Activar al enemigo
    
    int direction = -1; // 1 = derecha, -1 = izquierda
    while (enemy->health > 0) {

         usleep(enemyMoveDelay); // Esperar el tiempo de movimiento de los enemigos
      
        // Mover al enemigo horizontalmente
        enemy->x += direction;
        
        // Verificar si el enemigo ha llegado al borde de la pantalla
        if (enemy->x <= 0) {
            direction = 1; // Cambiar a dirección derecha
            enemy->y++; // Establecer la posición Y del enemigo en la nueva fila
        } else if (enemy->x >= 79) {
            direction = -1; // Cambiar a dirección izquierda
            enemy->y++; // Establecer la posición Y del enemigo en la nueva fila
        }
        
    }
    enemy->active = 0;
    pthread_cancel(enemy->thread);
    score += enemy->health2;
    return NULL;
}
void drawEnemies(Enemy enemies[], int numEnemies) {
    for (int i = 0; i < numEnemies; i++) {
        if (!enemies[i].active) {
            // Buscar una posición libre para el enemigo
            int startX = 79;
            int startY = 0;
            while (screen[startY][startX] != ' ' || screen[startY][startX - 1] != ' ' || screen[startY][startX - 2] != ' ' || screen[startY][startX - 3] != ' ') {
                startX -= 4; // Retroceder 4 posiciones (ancho de cada enemigo más un espacio)
                
                // Si se llega al inicio de la pantalla, pasar a la siguiente fila
                if (startX <= 0) {
                    startX = 79; // Reiniciar la posición X
                    startY++; // Pasar a la siguiente fila
                }
            }
            enemies[i].x = startX;
            enemies[i].y = startY;
            enemies[i].active = 0;
            enemies[i].health = (rand_r(&(unsigned int){time(NULL) ^ i}) % 3) + 1;
            pthread_create(&enemies[i].thread, NULL, enemyThread, &enemies[i]);
        }
        
        if (enemies[i].active && enemies[i].health > 0) {
            char healthChar[2];
            sprintf(healthChar, "%d", enemies[i].health);
            screen[enemies[i].y][enemies[i].x] = healthChar[0];
            screen[enemies[i].y][enemies[i].x - 1] = '<';
            screen[enemies[i].y][enemies[i].x + 1] = '>';
        }
    }
}




