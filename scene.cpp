#include "scene.h"

ALLEGRO_FONT *Titlefont = NULL;
ALLEGRO_FONT *Menufont = NULL;
ALLEGRO_BITMAP *menu = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *exit_img = NULL;


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
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = true;
}

void menu_draw(){
    // 畫面顏色 // 要改主畫面
    al_draw_bitmap(menu, 0, 0, 0);
    // al_clear_to_color(al_map_rgb(100,100,100));
    // 顯示主選單的字 => 這邊可以考慮說要全部大寫還是說要有小寫?
    al_draw_text(Titlefont, al_map_rgb(255,255,255), WIDTH/2-300, HEIGHT/2-400 , ALLEGRO_ALIGN_CENTRE, "The  Rat's  NIGHTMARE");
    al_draw_text(Menufont, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-140 , ALLEGRO_ALIGN_CENTRE, "GUIDENCE");
    al_draw_text(Menufont, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-70 , ALLEGRO_ALIGN_CENTRE, "START");
    al_draw_text(Menufont, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2 , ALLEGRO_ALIGN_CENTRE, "LEVEL");
    al_draw_text(Menufont, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+70 , ALLEGRO_ALIGN_CENTRE, "INFINITE MODE");
    al_draw_text(Menufont, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+140 , ALLEGRO_ALIGN_CENTRE, "EXIT");
}

void menu_destroy(){
    al_destroy_font(Menufont);
    al_destroy_font(Titlefont);
    // Release the memory of font
}


// function of game_scene
void game_scene_init()
{

    character_init();
    background = al_load_bitmap("./image/background.jpg");


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
    fclose(input);

    for(int i=0;i<wall_count;i++)
    {
        wall[i].img=al_load_bitmap("./image/wall3.jpg");
        wall[i].width = al_get_bitmap_width(wall[i].img);
        wall[i].height = al_get_bitmap_height(wall[i].img);
    }
    exit_img=al_load_bitmap("./image/exit.png");

}
void game_scene_draw(){

    al_draw_bitmap(background, 0, 0, 0);

    for(int i=0;i<wall_count;i++){
        al_draw_bitmap(wall[i].img, wall[i].x, wall[i].y, 0);
    }
    al_draw_bitmap(exit_img,1750,100,0);
    character_draw();
}
void game_scene_destroy(){
    al_destroy_bitmap(background);
    al_destroy_bitmap(exit_img);
    for(int i=0;i<wall_count;i++)
        al_destroy_bitmap(wall[i].img);
    character_destory();
}