#include "charater.h"
#define ADD_JUMP_HEIGHT 10
#define ADD_TIME 30

// the state of character
int cnt=0,tmp;
enum {STOP = 0, MOVE, JUMP,USE};
typedef struct character
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    int chance; // 命
    int blood; // HP 血量
    int time; // 時間
    int point; // 得分
    int on_stage;
    int jump_speed,jump_time,init_y;
    int tool[2]={0};

    ALLEGRO_BITMAP *img_move[7];

    ALLEGRO_SAMPLE_INSTANCE *move_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation

}Character;


Character chara;
ALLEGRO_SAMPLE *sample = NULL;
void character_init(){
    // load character images
    for(int i = 1 ; i <= 6 ; i++){
        char temp[50];
        sprintf( temp, "./image/chara7_%d.png", i );
        chara.img_move[i-1] = al_load_bitmap(temp);
        // 載入圖片
    }

    // load effective sound
    sample = al_load_sample("./sound/atk_sound.wav");
    chara.move_Sound  = al_create_sample_instance(sample);

    al_set_sample_instance_playmode(chara.move_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(chara.move_Sound, al_get_default_mixer());

    // initial the geometric information of character
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);
    chara.x = 0;
    chara.y = HEIGHT-wall[0].height-chara.height;
    chara.dir = false;

    // initial the animation component
    chara.state = STOP;
    chara.anime = 0;
    chara.anime_time = 30;

    chara.chance = 1;
    chara.blood = 10;
    chara.time = 60*FPS;
    chara.point = 0;
    chara.jump_speed=20;
    chara.jump_time = 0;
    chara.on_stage=0;
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
        chara.time--;
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
                    return k+1;
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
void use(int tool_num){
    if(tool_num==1){ //knife
        //TBA
    }
    else if(tool_num==2){ //life
        chara.chance++;
    }
    else if(tool_num==3){ //add jump height
        chara.jump_speed+=ADD_JUMP_HEIGHT;
    }
    else if(tool_num==4){ //add time
        chara.time+=ADD_TIME*FPS;
    }
}
void trigger(int trap_num){
    if(trap_num==1){ //monster
        chara.blood-=5;
    }
    else if(trap_num==2){ //bomb
        chara.blood-=5;
    }
    else if(trap_num==3){ //sub time
        chara.time-=ADD_TIME*FPS;
    }
}
void pick(int tool_num){
    int flag=1;
    for(int i=0;i<2;++i){
        if(chara.tool[i]==0){
            chara.tool[i]=tool_num;
            flag=0;
            break;
        }
    }
    if(flag){
        chara.tool[0]=chara.tool[1];
        chara.tool[1]=tool_num;
    }
}
int check_trap(int on_stage){
    int res;
    if(next_window==2&&level1_trap[on_stage]!=-1){
        res=level1_trap[on_stage];
        level1_trap[on_stage]=-1;
        return res;
    }else if(next_window==3&&level2_trap[on_stage]!=-1){
        res=level2_trap[on_stage];
        level2_trap[on_stage]=-1;
        return res;
    }else if(next_window==4&&level3_trap[on_stage]!=-1){
        res=level3_trap[on_stage];
        level3_trap[on_stage]=-1;
        return res;
    }
    return -1;
}
int check_tool(int on_stage){
    int res;
    if(next_window==2&&level1_tool[on_stage]!=-1){
        res=level1_tool[on_stage];
        level1_tool[on_stage]=-1;
        return res;
    }else if(next_window==3&&level2_tool[on_stage]!=-1){
        res=level2_tool[on_stage];
        level2_tool[on_stage]=-1;
        return res;
    }else if(next_window==4&&level3_tool[on_stage]!=-1){
        res=level3_tool[on_stage];
        level3_tool[on_stage]=-1;
        return res;
    }
    return -1;
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
                int res;
                chara.y+=dy;
                chara.state=STOP;
                chara.jump_time=0;
                chara.on_stage=tmp-1;
                if(chara.on_stage==wall_count-1){
                    //change level
                    printf("jizz\n");
                    if(next_window==2||next_window==3){
                        next_window++;
                        judge_next_window=true;
                    }
                    //exit
                }
                res=check_trap(chara.on_stage);
                if(res!=-1){
                    trigger(res+1);
                }
                res=check_tool(chara.on_stage);
                if(res!=-1){
                    pick(res+1);
                }
            }
            dx=(chara.dir?1:-1)*step;
            chara.x+=dx;
            tmp=check_collision(&chara);
            if(tmp||chara.x<0||chara.x+chara.width>WIDTH){
                chara.x-=dx;
                step=0;
            }
        }
    }
    else if( key_state[ALLEGRO_KEY_A] ){
        chara.dir = false;
        chara.x -= 5;
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_D] ){
        chara.dir = true;
        chara.x += 5;
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_S] ){
        chara.y += 5;
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_W] ){
        chara.y -= 5;
        chara.state = MOVE;
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
    if(key_state[ALLEGRO_KEY_R]){
        chara.state=USE;
        use(chara.tool[0]);
        chara.tool[0]=0;
    }
    else if(key_state[ALLEGRO_KEY_T]){
        chara.state=USE;
        use(chara.tool[1]);
        chara.tool[1]=0;
    }
    if(chara.chance==0){
        //exit
    }
    else if(chara.blood<=0){
        chara.chance--;
    }else if(chara.time<=0){
        //exit;
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
            if( chara.anime < chara.anime_time/3 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else if(chara.anime<chara.anime_time*2/3&&chara.anime>chara.anime_time/3){
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else if(chara.anime>chara.anime_time*2/3){
                al_draw_bitmap(chara.img_move[2], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);            
            }
        }else{
            if( chara.anime < chara.anime_time/3 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
            }else if(chara.anime<chara.anime_time*2/3&&chara.anime>chara.anime_time/3){
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, 0);
            }else if(chara.anime>chara.anime_time*2/3){
                al_draw_bitmap(chara.img_move[2], chara.x, chara.y, 0);
            }
        }
    }else if( chara.state == JUMP ){
        if( chara.dir ){
            if( chara.anime < chara.anime_time/3 ){
                al_draw_bitmap(chara.img_move[3], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else if(chara.anime<chara.anime_time*2/3&&chara.anime>chara.anime_time/3){
                al_draw_bitmap(chara.img_move[4], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);
            }else if(chara.anime>chara.anime_time*2/3){
                al_draw_bitmap(chara.img_move[5], chara.x, chara.y, ALLEGRO_FLIP_HORIZONTAL);            
            }
        }else{
            if( chara.anime < chara.anime_time/3 ){
                al_draw_bitmap(chara.img_move[3], chara.x, chara.y, 0);
            }else if(chara.anime<chara.anime_time*2/3&&chara.anime>chara.anime_time/3){
                al_draw_bitmap(chara.img_move[4], chara.x, chara.y, 0);
            }else if(chara.anime>chara.anime_time*2/3)
                al_draw_bitmap(chara.img_move[5], chara.x, chara.y, 0);
        }
    }
}
void character_attr_draw(int level,ALLEGRO_FONT *GUIDANCEcontextfont){
    char level_s[10];
    sprintf(level_s,"Level %d",level);
    al_draw_text(GUIDANCEcontextfont, al_map_rgb(255,255,255), WIDTH/2-850, HEIGHT/2-500 , ALLEGRO_ALIGN_CENTRE, level_s);
    char chance[2];
    sprintf(chance, "%d", chara.chance);
    al_draw_text(GUIDANCEcontextfont, al_map_rgb(255,255,255), WIDTH/2-850, HEIGHT/2-450 , ALLEGRO_ALIGN_CENTRE, "Life : ");
    al_draw_text(GUIDANCEcontextfont, al_map_rgb(255,255,255), WIDTH/2-720, HEIGHT/2-450 , ALLEGRO_ALIGN_CENTRE, chance);
    char blood[3];
    sprintf(blood, "%d", chara.blood);
    al_draw_text(GUIDANCEcontextfont, al_map_rgb(255,255,255), WIDTH/2-850, HEIGHT/2-400 , ALLEGRO_ALIGN_CENTRE, "HP : ");
    al_draw_text(GUIDANCEcontextfont, al_map_rgb(255,255,255), WIDTH/2-720, HEIGHT/2-400 , ALLEGRO_ALIGN_CENTRE, blood);
    char time[3];
    sprintf(time, "%d", chara.time);
    al_draw_text(GUIDANCEcontextfont, al_map_rgb(255,255,255), WIDTH/2-850, HEIGHT/2-350 , ALLEGRO_ALIGN_CENTRE, "Time : ");
    al_draw_text(GUIDANCEcontextfont, al_map_rgb(255,255,255), WIDTH/2-720, HEIGHT/2-350 , ALLEGRO_ALIGN_CENTRE, time);
    al_draw_text(GUIDANCEcontextfont, al_map_rgb(255,255,255), WIDTH/2-850, HEIGHT/2-300 , ALLEGRO_ALIGN_CENTRE, "Weapon: ");
}
void character_destroy(){
    for(int i = 0; i < 6; i++)
        al_destroy_bitmap(chara.img_move[i]);
    al_destroy_sample_instance(chara.move_Sound);
}
