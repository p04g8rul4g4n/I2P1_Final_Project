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
    wall_count=0;
    character_init();
    background = al_load_bitmap("./image/background.jpg");
    //Load Background


    for(int i=0;i<20;i++)
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
    fclose(input);//Load coor of walls

    al_draw_bitmap(background, 0, 0, 0);
    for(int i=0;i<wall_count;i++)
        al_draw_bitmap(wall[i].img, wall[i].x, wall[i].y, 0);
    al_draw_bitmap(exit_img,1750,100,0);
    al_draw_rectangle(20,350,550,20,al_map_rgb(255, 22, 25),3);
    al_draw_bitmap(img_trap[0],1500,400,0);
    al_draw_bitmap(img_trap[1],650,640,0);
    al_draw_bitmap(img_tool[0],330,750,0);
    al_draw_bitmap(img_tool[3],400,430,0);
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
    al_draw_bitmap(img_trap[0],1550,350,0);
    al_draw_bitmap(img_trap[0],1600,800,0);
    al_draw_bitmap(img_trap[1],650,640,0);
    al_draw_bitmap(img_trap[1],1450,590,0);
    al_draw_bitmap(img_trap[2],930,740,0);
    al_draw_bitmap(img_tool[0],330,750,0);
    al_draw_bitmap(img_tool[1],990,75,0);
    al_draw_bitmap(img_tool[2],1240,875,0);
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
    al_draw_bitmap(img_tool[0],330,750,0);
    al_draw_bitmap(img_trap[0],730,200,0);
    al_draw_bitmap(img_trap[2],650,640,0);
    al_draw_bitmap(img_trap[0],920,750,0);
    al_draw_bitmap(img_trap[1],990,30,0);
    al_draw_bitmap(img_trap[1],1050,400,0);
    al_draw_bitmap(img_trap[2],1240,880,0);
    al_draw_bitmap(img_trap[0],1240,200,0);
    al_draw_bitmap(img_trap[1],1450,570,0);
    al_draw_bitmap(img_trap[2],1570,330,0);
    al_draw_bitmap(img_trap[2],1620,780,0);


    character_draw();
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