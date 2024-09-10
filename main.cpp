#include "simlcd.h"
#include "dispcolor.h"
#include "font.h"
#include "color.h"

simlcd_buffer_t LCD_BUFFER;
bool btn_info=true,update_flag=true;

void draw_box();
void draw_continus_line(int x,int y,uint16_t color);
void clear_screen();

int simlcd_touch_event(uint32_t x,uint32_t y,uint16_t event)
{
    static char buf[64];
    static bool clicked=false;

    switch(event)
    {
        case SDL_MOUSEBUTTONDOWN:clicked=true;break;
        case SDL_MOUSEBUTTONUP:clicked=false;break;
    }

    if(clicked)
    {
        if(btn_info==false&&y>10)
        {
            draw_continus_line(x,y,color_24_to_16(COLOR_AQUA));
            update_flag=true;
        }

        if(y<=10)
        {
            // X
            if(x>=117) return -1;
            // C
            else if(x>107)
            {
                clear_screen();
                update_flag=true;
            }
            // i
            else if(x>=98)
            {
                if(btn_info)btn_info=false;
                else btn_info=true;
                clear_screen();
                update_flag=true;
            }
        }

        if(btn_info)
        {
            sprintf(buf,"[%03d,%03d] ",x,y);
            dispcolor_DrawString_Bg(2,12,FONTID_6X8M,buf,WHITE,BLUE);
            update_flag=true;
        }
    }
    else
    {
        // clear pen
        draw_continus_line(-1,-1,0);
    }
    return 0;
}

int loop(int key)
{
    static int i=50,j=0;
    static char buf[64];

    if(key)
    {
        if(btn_info)
        {
            sprintf(buf,"KEY CODE IS %d  ",key);
            dispcolor_DrawString_Bg(2,2,FONTID_6X8M,buf,WHITE,BLUE);
            update_flag=true;
            // dispcolor_Update();
        }
        if(key==41)return -1;
    }

    if(i>=50)
    {
        i=0;
        if(btn_info)
        {
            sprintf(buf,"%02d:%02d ",j/60,j%60);
            dispcolor_DrawString_Bg(45,20,FONTID_16F,buf,color_24_to_16(COLOR_RED),BLUE);
            update_flag=true;
        }
        j++;
    }

    if(update_flag)
    {
        dispcolor_Update();
        update_flag=false;
    }

    simlcd_delay(20);
    i++;
    return 0;
}

void simlcd_exit()
{

}

int main(int argc,char *argv[])
{
    dispcolor_Init(128,64);
    dispcolor_FillScreen(BLUE);
    dispcolor_DrawString(20,40,FONTID_16F,(char*)&"Hello World!",color_24_to_16(COLOR_YELLOW));
    dispcolor_Update();
    draw_box();
    simlcd_play();
    return 0;
}

void draw_box()
{
    dispcolor_DrawRectangle(0,0,127,63,WHITE);
    dispcolor_DrawLine(0,10,127,10,WHITE);
    dispcolor_DrawLine(127-10,0,127-10,10,WHITE);
    dispcolor_DrawLine(127-8,0+2,127-2,10-2,WHITE);
    dispcolor_DrawLine(127-8,10-2,127-2,0+2,WHITE);

    dispcolor_DrawString(110,2,FONTID_6X8M,(char*)&"C",WHITE);
    dispcolor_DrawLine(107,0,107,10,WHITE);

    if(btn_info) dispcolor_DrawString(100,2,FONTID_6X8M,(char*)&"!",RED);
    else dispcolor_DrawString(100,2,FONTID_6X8M,(char*)&"!",WHITE);
    dispcolor_DrawLine(98,0,98,10,WHITE);
}

void draw_continus_line(int x,int y,uint16_t color)
{
    static int ox=-1,oy=-1;
    if(ox==-1 && oy==-1)
    {
        ox=x;
        oy=y;
    }
    // Reset
    if(x>=0 && y>=0)dispcolor_DrawLine(ox,oy,x,y,color);
    ox=x;
    oy=y;
}

void clear_screen()
{
    dispcolor_FillScreen(BLUE);
    draw_box();
    //Reset mem
    draw_continus_line(-1,-1,0);
}

