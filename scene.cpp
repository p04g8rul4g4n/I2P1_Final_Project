#include "scene.h"

ALLEGRO_FONT *Titlefont = NULL;
ALLEGRO_FONT *Menufont = NULL;
ALLEGRO_BITMAP *menu = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *exit_img = NULL;
ALLEGRO_FONT *GUIDANCEcontextfont = NULL;
ALLEGRO_BITMAP *GUIDANCEbackground = NULL;
ALLEGRO_FONT *GUIDANCEtitlefont = NULL;
ALLEGRO_BITMAP *Start = NULL;
ALLEGRO_BITMAP *BackMenu = NULL;
ALLEGRO_BITMAP *OVERbackground = NULL;
ALLEGRO_BITMAP *VICbackground = NULL;
ALLEGRO_BITMAP *VICrat = NULL;

typedef struct
{
    int x,y;  //coor
    int kind; // 1 for trap ;0 for tool
    int thing;
    int id;
}trap_tool;

trap_tool level1[4]={
    {x:330,y:750,kind:0,thing:0,id:1},
    {x:400,y:430,kind:0,thing:3,id:2},
    {x:650,y:640,kind:1,thing:1,id:3},
    {x:1500,y:400,kind:1,thing:0,id:7}
    };

trap_tool level2[8]={
    {x:1550,y:350,kind:1,thing:0,id:10},
    {x:1600,y:800,kind:1,thing:0,id:11},
    {x:650,y:640,kind:1,thing:1,id:3},
    {x:1450,y:590,kind:1,thing:1,id:9},
    {x:930,y:740,kind:1,thing:2,id:5},
    {x:330,y:750,kind:0,thing:0,id:1},
    {x:990,y:75,kind:0,thing:1,id:6},
    {x:1240,y:875,kind:0,thing:2,id:8},
    };
trap_tool level3[11]={
    {x:730,y:200,kind:1,thing:0,id:4},
    {x:650,y:640,kind:1,thing:2,id:3},
    {x:920,y:750,kind:1,thing:0,id:5},
    {x:990,y:30,kind:1,thing:1,id:6},
    {x:1050,y:400,kind:1,thing:1,id:7},
    {x:1240,y:880,kind:1,thing:2,id:8},
    {x:1240,y:200,kind:1,thing:0,id:9},
    {x:1450,y:570,kind:1,thing:1,id:10},
    {x:1570,y:330,kind:1,thing:2,id:11},
    {x:1620,y:780,kind:1,thing:2,id:12},
    {x:330,y:750,kind:0,thing:0,id:1}
    };



// function of menu
void menu_init(){ // 顯示字體
    // 要更改字體 // title font
    Titlefont = al_load_ttf_font("./font/SF-Gushing-Meadow-SC.ttf",88,0);
    // Menu font
    Menufont = al_load_ttf_font("./font/TrixiePlain.ttf",40,0);
    menu = al_load_bitmap("./image/Menu1.jpg");
    // al_load_ttf_font(path of the font file, size of font,  0);
}

void menu_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        if( event.keyboard.keycode == ALLEGRO_KEY_1 ){
            judge_next_window =true ;
            next_window = 1;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_2){
            judge_next_window = true;
             next_window = 2;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_3){
            judge_next_window = true;
             next_window = 3;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_4){
            judge_next_window = true;
            next_window = 4;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_5){
            judge_next_window = true;
             next_window = 5;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_6){
            judge_next_window = true;
             next_window = 6;
        }
    }
}


void menu_draw(){
    // 畫面顏色 // 要改主畫面
    al_draw_bitmap(menu, 0, 0, 0);
    // al_clear_to_color(al_map_rgb(100,100,100));
    // 顯示主選單的字 => 這邊可以考慮說要全部大寫還是說要有小寫?
    al_draw_text(Titlefont, al_map_rgb(255,255,255), WIDTH/2-300, HEIGHT/2-400 , ALLEGRO_ALIGN_CENTRE, "The  Rat's  NIGHTMARE");
    al_draw_text(Menufont, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-140 , ALLEGRO_ALIGN_CENTRE, "1. GUIDENCE");
    al_draw_text(Menufont, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-70 , ALLEGRO_ALIGN_CENTRE, "2. START");
    al_draw_text(Menufont, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2 , ALLEGRO_ALIGN_CENTRE, "3. LEVEL");
    al_draw_text(Menufont, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+70 , ALLEGRO_ALIGN_CENTRE, "4. INFINITE MODE");
    al_draw_text(Menufont, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+140 , ALLEGRO_ALIGN_CENTRE, "5 EXIT");
}

void menu_destroy(){
    al_destroy_font(Menufont);
    al_destroy_font(Titlefont);
    // Release the memory of font
}


// function of game_scene
void game_scene_init()
{   
    printf("JIZZ\n");
    wall_count=0;
    character_init();
    background = al_load_bitmap("./image/background.jpg");
    //Load Background


    for(int i=0;i<MAX_WALL;i++)
    {
        wall[i].img=al_load_bitmap("./image/wall3.jpg");
        wall[i].width=al_get_bitmap_width(wall[i].img);
        wall[i].height=al_get_bitmap_height(wall[i].img);
    }//Load wall image

   for(int i = 1 ; i <= 4 ; i++){
        char temp[50];
        sprintf( temp, "./image/tool%d.png", i );
        img_tool[i-1] = al_load_bitmap(temp);
        // 載入圖片
    }
    for(int i = 1 ; i <= 3 ; i++){
        char temp[50];
        sprintf( temp, "./image/trap%d.png", i );
        img_trap[i-1] = al_load_bitmap(temp);
        // 載入圖片
    }
    exit_img=al_load_bitmap("./image/exit.png");
    GUIDANCEcontextfont = al_load_ttf_font("./font/Scrawny-Kids.ttf",40,0);

}
void game_scene_init2(){ // 1. GUIDANCE 2. GameOver 3, Victory
    GUIDANCEbackground = al_load_bitmap("./image/GUIDANCEbackground.jpg");// Load Background
    GUIDANCEcontextfont = al_load_ttf_font("./font/Scrawny-Kids.ttf",40,0);
    GUIDANCEtitlefont = al_load_ttf_font("./font/SF-Gushing-Meadow-SC.ttf",88,0);
    Start = al_load_bitmap("./image/start.png");
    BackMenu = al_load_bitmap("./image/back2.png");

    OVERbackground = al_load_bitmap("./image/OVERbackground.jpg");
    VICbackground = al_load_bitmap("./image/VICbackground.jpg");
    VICrat = al_load_bitmap("./image/chara7_6.png");
}
void game_scene_draw1()
{
        FILE *input= fopen("./level.txt", "r+");
    if (input==NULL)
        printf("Error opening file");
    else
    {
        char buff[20];
        while(feof(input)==0)
        {
           for (wall_count=0; fgets( buff,sizeof buff,input ) != NULL;wall_count++)
                sscanf(buff,"%d %d",&wall[wall_count].x,&wall[wall_count].y);
        }
    }
    fclose(input); //Load coor of walls

    al_draw_bitmap(background, 0, 0, 0);
    for(int i=0;i<wall_count;i++)
        al_draw_bitmap(wall[i].img, wall[i].x, wall[i].y, 0);
    al_draw_bitmap(exit_img,1750,100,0);
    al_draw_rectangle(20,350,550,20,al_map_rgb(255, 22, 25),3);

    for(int j=0;j<wall_count;++j)
    {
        if(level1_tool[j]!=-1||level1_trap[j]!=-1)
        {
            for(int i=0;i<4;++i){
                if(level1[i].id==j){
                    if(level1[i].kind==1)
                        al_draw_bitmap(img_trap[level1[i].thing],level1[i].x,level1[i].y,0);
                    else
                        al_draw_bitmap(img_tool[level1[i].thing],level1[i].x,level1[i].y,0);
                }
            }
        }
    }
    character_attr_draw(1,GUIDANCEcontextfont);
    character_draw();
}
void game_scene_draw2()
{
    FILE *input= fopen("./level2.txt", "r+");
    if (input==NULL)
        printf("Error opening file");
    else
    {
        char buff[20];
        while(feof(input)==0)
        {
           for (wall_count=0; fgets( buff,sizeof buff,input ) != NULL;wall_count++)
                sscanf(buff,"%d %d",&wall[wall_count].x,&wall[wall_count].y);
        }
    }
    fclose(input);//Load coor of walls


    al_draw_bitmap(background, 0, 0, 0);
    for(int i=0;i<wall_count;i++)
        al_draw_bitmap(wall[i].img, wall[i].x, wall[i].y, 0);
    al_draw_bitmap(exit_img,1750,100,0);
    al_draw_rectangle(20,350,550,20,al_map_rgb(255, 22, 25),3);

    for(int j=0;j<wall_count;++j)
    {
        if(level2_tool[j]!=-1||level2_trap[j]!=-1)
        {
            for(int i=0;i<8;++i){
                if(level2[i].id==j){
                    if(level2[i].kind==1)
                        al_draw_bitmap(img_trap[level2[i].thing],level2[i].x,level2[i].y,0);
                    else
                        al_draw_bitmap(img_tool[level2[i].thing],level2[i].x,level2[i].y,0);
                }
            }
        }
    }
    character_attr_draw(2,GUIDANCEcontextfont);
    character_draw();
}
void game_scene_draw3()
{
    FILE *input= fopen("./level3.txt", "r+");
    if (input==NULL)
        printf("Error opening file");
    else
    {
        char buff[20];
        while(feof(input)==0)
        {
           for (wall_count=0; fgets( buff,sizeof buff,input ) != NULL;wall_count++)
                sscanf(buff,"%d %d",&wall[wall_count].x,&wall[wall_count].y);
        }
    }
    fclose(input);//Load coor of walls

    al_draw_bitmap(background, 0, 0, 0);
    for(int i=0;i<wall_count;i++)
        al_draw_bitmap(wall[i].img, wall[i].x, wall[i].y, 0);
    al_draw_bitmap(exit_img,1750,100,0);
    al_draw_rectangle(20,350,550,20,al_map_rgb(255, 22, 25),3);

    for(int j=0;j<wall_count;++j)
    {
        if(level3_tool[j]!=-1||level3_trap[j]!=-1)
        {
            for(int i=0;i<11;++i){
                if(level3[i].id==j){
                    if(level3[i].kind==1)
                        al_draw_bitmap(img_trap[level3[i].thing],level3[i].x,level3[i].y,0);
                    else
                        al_draw_bitmap(img_tool[level3[i].thing],level3[i].x,level3[i].y,0);
                }
            }
        }
    }
    character_attr_draw(3,GUIDANCEcontextfont);
    character_draw();
}
void game_scene_draw4(){
    al_draw_bitmap(GUIDANCEbackground, 0, 0, 0);
    al_draw_bitmap(Start, WIDTH/2-120, HEIGHT/2+200, 0);
    al_draw_bitmap(BackMenu, WIDTH/2-800, HEIGHT/2+250, 0);

    al_draw_text(GUIDANCEcontextfont, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-140 , ALLEGRO_ALIGN_CENTRE, "A rat is caught by a freak cat whose purpose isn'1t eating it for food, but forcing it");
    al_draw_text(GUIDANCEcontextfont, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-70 , ALLEGRO_ALIGN_CENTRE, "to play bloody games. The cat wants the rat to die tragically so he can have lots of");
    al_draw_text(GUIDANCEcontextfont, al_map_rgb(255,255,255), WIDTH/2-250, HEIGHT/2 , ALLEGRO_ALIGN_CENTRE, "fun. HELP the rat from being hurt and get out of there !!!");

    al_draw_text(GUIDANCEtitlefont, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-400 , ALLEGRO_ALIGN_CENTRE, "GUIDANCE");

}



void game_scene_draw5(){
    al_draw_bitmap(OVERbackground, 0, 0, 0);
    al_draw_text(GUIDANCEcontextfont, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-70 , ALLEGRO_ALIGN_CENTRE, "You Lose !!!!");    
    al_draw_text(GUIDANCEtitlefont, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2 , ALLEGRO_ALIGN_CENTRE, "Game Over");
}

void game_scene_draw6(){
    al_draw_bitmap(VICbackground, 0, 0, 0);
    al_draw_bitmap(VICrat, WIDTH/2+500, HEIGHT/2+100, 0);
}
void game_scene_destroy(){
    al_destroy_bitmap(background);

    for(int i=0;i<wall_count;i++)
        al_destroy_bitmap(wall[i].img);
    for(int i = 1 ; i <= 4 ; i++)
    {
        al_destroy_bitmap(img_tool[i-1]);
    }
    for(int i = 1 ; i <= 3 ; i++)
    {
        al_destroy_bitmap(img_trap[i-1]);
    }
    al_destroy_bitmap(exit_img);
    character_destroy();
}
void game_scene_destroy2(){
    al_destroy_bitmap(GUIDANCEbackground);
    al_destroy_font(GUIDANCEcontextfont);
    al_destroy_font(GUIDANCEtitlefont);
    al_destroy_bitmap(Start);
    al_destroy_bitmap(BackMenu);
    al_destroy_bitmap(OVERbackground);
    al_destroy_bitmap(VICbackground);
    al_destroy_bitmap(VICrat);
}
void init_next_level(){
    game_scene_destroy();
}