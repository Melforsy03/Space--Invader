#include <stdio.h>
#include <unistd.h>
#include "game.h"
#include "pantalla.h"
#include "bullets.h"
int player_x = 80 / 2;
int player_y = 24 / 2;
int moving_left = 0, moving_right = 0, moving_up = 0, moving_down = 0;
pthread_mutex_t mutex;
void* move_player(void) {
    while (1) {
        pthread_mutex_lock(&mutex);
      
        if (moving_left && player_x > 0) {
            player_x--;
            moving_left = 0; // Reiniciar la bandera de movimiento
        }
        if (moving_right && player_x < 80 - 1) {
            player_x++;
            moving_right = 0; // Reiniciar la bandera de movimiento
        }
        if (moving_up && player_y > 0) {
            player_y--;
            moving_up = 0; // Reiniciar la bandera de movimiento
        }
        if (moving_down && player_y < 23) {
            player_y++;
            moving_down = 0; // Reiniciar la bandera de movimiento
        }
        pthread_mutex_unlock(&mutex);
        struct timespec ts = {0, 20}; // 20 milisegundos
        nanosleep(&ts, NULL);
    }
    return NULL;
}
void draw_player(int x, int y) {
    // Borrar la nave en su posición actual
    clear_screen();
    for (int i = 0; i < 3; i++) {
        if (player_y + i >= 0 && player_y + i < 24 && player_x - 1 >= 0 && player_x - 1 < 80) {
            screen[player_y + i][player_x - 1] = ' ';
        }
        if (player_y + i >= 0 && player_y + i < 24 && player_x >= 0 && player_x < 80) {
            screen[player_y + i][player_x] = ' ';
        }
        if (player_y + i >= 0 && player_y + i < 24 && player_x + 1 >= 0 && player_x + 1 < 80) {
            screen[player_y + i][player_x + 1] = ' ';
        }
    }
    // Ajustar la posición de la nave para que se dibuje completamente dentro de la pantalla
    int adjusted_x = x;
    int adjusted_y = y;
    if (x - 1 < 0) {
        adjusted_x = 1;
    } else if (x + 1 >= 80) {
        adjusted_x = 78;
    }
    if (y < 0) {
        adjusted_y = 0;
    } else if (y + 2 >= 24) {
        adjusted_y = 21;
    }
    // Dibujar la nave en la nueva posición
    if (adjusted_y >= 0 && adjusted_y < 24 && adjusted_x - 1 >= 0 && adjusted_x - 1 < 80) {
        screen[adjusted_y][adjusted_x - 1] = '/';
    }
    if (adjusted_y >= 0 && adjusted_y < 24 && adjusted_x >= 0 && adjusted_x < 80) {
        screen[adjusted_y][adjusted_x] = '-';
    }
    if (adjusted_y >= 0 && adjusted_y < 24 && adjusted_x + 1 >= 0 && adjusted_x + 1 < 80) {
        screen[adjusted_y][adjusted_x + 1] = '\\';
    }
    if (adjusted_y + 1 >= 0 && adjusted_y + 1 < 24 && adjusted_x - 1 >= 0 && adjusted_x - 1 < 80) {
        screen[adjusted_y + 1][adjusted_x - 1] = '|';
    }
    if (adjusted_y + 1 >= 0 && adjusted_y + 1 < 24 && adjusted_x >= 0 && adjusted_x < 80) {
        screen[adjusted_y + 1][adjusted_x] = ' ';
    }
    if (adjusted_y + 1 >= 0 && adjusted_y + 1 < 24 && adjusted_x + 1 >= 0 && adjusted_x + 1 < 80) {
        screen[adjusted_y + 1][adjusted_x + 1] = '|';
    }
    if (adjusted_y + 2 >= 0 && adjusted_y + 2 < 24 && adjusted_x - 1 >= 0 && adjusted_x - 1 < 80) {
        screen[adjusted_y + 2][adjusted_x - 1] = '\\';
    }
    if (adjusted_y + 2 >= 0 && adjusted_y + 2 < 24 && adjusted_x >= 0 && adjusted_x < 80) {
        screen[adjusted_y + 2][adjusted_x] = '-';
    }
    if (adjusted_y + 2 >= 0 && adjusted_y + 2 < 24 && adjusted_x + 1 >= 0 && adjusted_x + 1 < 80) {
        screen[adjusted_y + 2][adjusted_x + 1] = '/';
    }
}
void *input_thread(void *arg){
    while (1) {
        int ch = getchar();
        pthread_mutex_lock(&mutex);
        if (ch == 'a' || ch == 'A' || ch == 'D') { // Izquierda
            moving_left = 1;
            moving_right = 0;
        } else if (ch == 'd' || ch == 'D' || ch == 'C') { // Derecha
            moving_right = 1;
            moving_left = 0;
        } else if (ch == 'w' || ch == 'W' || ch == 'A') { // Arriba
            moving_up = 1;
            moving_down = 0;
        } else if (ch == 's' || ch == 'S' || ch == 'B') { // Abajo
            moving_down = 1;
            moving_up = 0;
        } else if (ch == ' ') {
             shoot_flag = 1;
        } else if (ch == 'q') {
            break;
        } else {
            moving_left = moving_right = moving_up = moving_down = 0;
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
