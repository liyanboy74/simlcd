#include "simlcd.h"
#include "dispcolor.h"
#include "font.h"
#include "color.h"

int simlcd_touch_event(uint32_t x,uint32_t y)
{
    static char buf[64];
    sprintf(buf,"[%03d,%03d] ",x,y);
    dispcolor_DrawString_Bg(2,12,FONTID_6X8M,buf,WHITE,BLUE);
    dispcolor_Update();

    if(x>=117&&y<=10) return -1;

    return 0;
}

void draw_box()
{
    dispcolor_DrawRectangle(0,0,127,63,WHITE);
    dispcolor_DrawLine(0,10,127,10,WHITE);
    dispcolor_DrawLine(127-10,0,127-10,10,WHITE);
    dispcolor_DrawLine(127-8,0+2,127-2,10-2,WHITE);
    dispcolor_DrawLine(127-8,10-2,127-2,0+2,WHITE);
}

int loop(SDL_Scancode key)
{
    static int i=0,j=0;
    static char buf[64];

    if(key)
    {
        sprintf(buf,"KEY CODE IS %d  ",key);
        dispcolor_DrawString_Bg(2,2,FONTID_6X8M,buf,WHITE,BLUE);
        dispcolor_Update();

        if(key==41)return -1;
    }

    sprintf(buf,"%02d:%02d ",i/60,i%60);
    dispcolor_DrawString_Bg(45,20,FONTID_16F,buf,color_24_to_16(COLOR_RED),BLUE);

    dispcolor_Update();

    simlcd_delay(20);

    j++;
    if(j%25==0)i++;

    return 0;
}

int main(int argc,char *argv[])
{
    dispcolor_Init(128,64);
    dispcolor_FillScreen(BLUE);

    dispcolor_DrawString(20,40,FONTID_16F,"Hello World!",color_24_to_16(COLOR_YELLOW));
    dispcolor_Update();

    draw_box();

    simlcd_play();
    return 0;
}

