#include "charater.h"

// the state of character
int cnt=0,tmp;
enum {STOP = 0, MOVE, JUMP};
typedef struct character
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    int jump_speed,jump_time,init_y;
    ALLEGRO_BITMAP *img_move[2];
    ALLEGRO_BITMAP *img_atk[2];
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
}Character;
Character chara;
ALLEGRO_SAMPLE *sample = NULL;
void character_init(){
    // load character images
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/char_move%d.png", i );
        chara.img_move[i-1] = al_load_bitmap(temp);
    }
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/char_atk%d.png", i );
        chara.img_atk[i-1] = al_load_bitmap(temp);
    }
    // load effective sound
    sample = al_load_sample("./sound/atk_sound.wav");
    chara.atk_Sound  = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(chara.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(chara.atk_Sound, al_get_default_mixer());
    // initial the geometric information of character
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    chara.x = WIDTH/2;
    chara.y = HEIGHT/2;
    chara.dir = false;
    chara.jump_speed=20;

    // initial the animation component
    chara.state = STOP;
    chara.anime = 0;
    chara.anime_time = 30;
    chara.jump_time = 0;
}
void charater_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara.anime++;
            chara.anime %= chara.anime_time;
        }
        if(event.timer.source==fps&&chara.state==JUMP){
            cnt++;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        chara.anime=0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode]=false;
    }
}
int in_range(int chara_x,int chara_y,w *t){
    if(chara_x>t->x&&chara_x<t->x+t->width&&chara_y>t->y&&chara_y<t->y+t->height)
        return 1;
    else
        return 0;
}
int check_collision(Character* ch){
    int dx=ch->width/2,dy=ch->height/2,res;
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            for(int k=0;k<wall_count;++k){
               res=in_range(ch->x+dx*j,ch->y+dy*i,&wall[k]);
                if(res){
                    return res;
                } 
            }
        }
    }
    return 0;
}
int jump(int jump_speed,int jump_time){
    int res=jump_speed-jump_time;
    return res;
}
void charater_update(){
    // use the idea of finite state machine to deal with different state
    if(chara.state==JUMP){
        if(cnt==2){
            int dx,dy,step=3;
            cnt=0;
            chara.jump_time++;
            dy=jump(chara.jump_speed,chara.jump_time);
            chara.y-=dy;
            tmp=check_collision(&chara);
            if((tmp&&dy>=0)||chara.y<0){
                chara.y+=dy;
            }
            else if((dy<0&&tmp)||chara.y+chara.height>HEIGHT){
                chara.y+=dy;
                chara.state=STOP;
                chara.jump_time=0;
            }
            dx=(chara.dir?1:-1)*step;
            chara.x+=dx;
            tmp=check_collision(&chara);
            if(tmp||chara.x<0||chara.x+chara.width>WIDTH){
                chara.x-=dx;
            }
        }
    }
    else if( key_state[ALLEGRO_KEY_A] ){
        chara.dir = false;
        chara.x -= 5;
        chara.state = MOVE;
        if(check_collision(&chara)){
            chara.x += 5;
        }
    }else if( key_state[ALLEGRO_KEY_D] ){
        chara.dir = true;
        chara.x += 5;
        chara.state = MOVE;
        if(check_collision(&chara)){
            chara.x -= 5;
        }
    }else if( key_state[ALLEGRO_KEY_S] ){
        chara.y += 5;
        chara.state = MOVE;
        if(check_collision(&chara)){
            chara.y -= 5;
        }
    }else if( key_state[ALLEGRO_KEY_W] ){
        chara.y -= 5;
        chara.state = MOVE;
        if(check_collision(&chara)){
            chara.y += 5;
        }
    }else if(key_state[ALLEGRO_KEY_SPACE]){
        cnt=0;
        chara.init_y=chara.y;
        chara.state = JUMP;
    }else if( chara.anime == chara.anime_time-1 ){
        chara.anime = 0;
        chara.state = STOP;
    }else if ( chara.anime == 0 ){
        chara.state = STOP;
    }
}
void character_draw(){
    // with the state, draw corresponding image
    if( chara.state == STOP ){
        if( chara.dir )
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
    }else if(chara.state == MOVE ){
        if(chara.dir ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }else{
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
            }else{
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, 0);
            }
        }
    }else if( chara.state == JUMP ){
        if( chara.dir ){
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_atk[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara.img_atk[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
                al_play_sample_instance(chara.atk_Sound);
            }
        }else{
            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_atk[0], chara.x, chara.y, 0);
            }else{
                al_draw_bitmap(chara.img_atk[1], chara.x, chara.y, 0);
                al_play_sample_instance(chara.atk_Sound);
            }
        }
    }
}
void character_destory(){
    al_destroy_bitmap(chara.img_atk[0]);
    al_destroy_bitmap(chara.img_atk[1]);
    al_destroy_bitmap(chara.img_move[0]);
    al_destroy_bitmap(chara.img_move[1]);
    al_destroy_sample_instance(chara.atk_Sound);
}
