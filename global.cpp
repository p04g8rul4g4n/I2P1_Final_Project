#include "global.h"

// variables for global usage
const float FPS = 60.0;
const int WIDTH = 1920;
const int HEIGHT = 1080;
const int BOUND = 150;
const int MAX_WALL=30;
w wall[MAX_WALL];
int wall_count,next_window=0;
ALLEGRO_BITMAP *img_tool[7];
ALLEGRO_BITMAP *img_trap[5];
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool judge_next_window = false;
