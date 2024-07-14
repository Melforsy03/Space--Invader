#ifndef GAME_H
#define GAME_H
#include <pthread.h>
extern int player_x;
extern int player_y;
extern int moving_left;
extern int moving_right;
extern int moving_up;
extern int moving_down;
extern pthread_mutex_t mutex;

void move_cursor(int x, int y);
void clear_screen();
void draw_player(int x, int y);
void* move_player(void);
void *input_thread(void *arg);

#endif // GAME_H
