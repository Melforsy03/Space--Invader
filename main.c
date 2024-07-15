#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include "game.h"
#include "bullets.h"
#include <ncurses.h>
#include "enemigo.h"
#include "pantalla.h"

int main() {
    printf("\033[?25l");
    // Configurar el modo de entrada no bloqueante
    struct termios old_termios, new_termios;
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

     highScore = readHighScore();
    // Dibujar la nave del jugador en la posición inicial
    clear_screen();
    draw_player(player_x, player_y);
    int numEnemies = 50;
    pthread_t  input_thread_id , shootThread ,thread, updateAndDrawThread;
    initBullets(bullets,10);
     Enemy enemies[numEnemies];
     initEnemies(enemies, numEnemies);
   
    // Crear y ejecutar los hilos
    pthread_create(&thread, NULL, move_player, NULL);
    pthread_create(&input_thread_id, NULL, input_thread, NULL);
    pthread_create(&updateAndDrawThread, NULL, updateAndDrawBulletsThread, NULL);
    pthread_create(&shootThread, NULL, shoot_bullets, NULL);
    
  while (1) {
        // Actualizar y dibujar la pantalla
        pthread_mutex_lock(&mutex);
        clear_screen();
        draw_player(player_x, player_y);
        drawEnemies(enemies, numEnemies);
        displayScores(score, highScore);
        drawBullets(bullets, 10);
        checkCollisions(enemies, numEnemies, bullets , 10);
        if (fin)
        {
            break;
        }
        draw_to_screen();
        pthread_mutex_unlock(&mutex);
        struct timespec ts = {0, 50000000}; // 50 milisegundos
        nanosleep(&ts, NULL);
        int currentTime = time(NULL);
    }
     // Guardar el mejor score
    if (score > highScore) {
        highScore = score;
        saveHighScore(highScore);
    }
    pthread_cancel(thread);
    pthread_mutex_destroy(&mutex);
    pthread_cancel(updateAndDrawThread);
    pthread_cancel(shootThread);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios); // Restaurar la configuración original de la terminal
    //reiniciar_programa();
    return 0;
}

// void reiniciar_programa() {
//     printf("Presiona una tecla para reiniciar el programa...\n");
//     getchar(); // Espera a que el usuario presione una tecla
//     system("clear"); // Limpia la pantalla (en Ubuntu/Linux)
//     main(); // Llama a la función main() para reiniciar el programa
// }

