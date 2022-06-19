#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#define GAME_TERMINATE -1
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

typedef struct wall
{
    int x,y;
    int width, height;
    bool exist;
    ALLEGRO_BITMAP *img;
}w;

// note that you can't assign initial value here!
extern const float FPS;
extern const int WIDTH;
extern const int HEIGHT;
extern const int BOUND;
extern const int MAX_WALL;
extern bool key_state[ALLEGRO_KEY_MAX];
extern bool judge_next_window;
extern w wall[];
extern int wall_count;
extern ALLEGRO_BITMAP *img_tool[];
extern ALLEGRO_BITMAP *img_trap[];
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *fps;
#endif
