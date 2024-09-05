#include "simlcd.h"
#include "dispcolor.h"
#include "font.h"
#include "color.h"

void loop(SDL_Scancode key)
{
    static int i=0,j=0;
    static char buf[64];

    if(key)
    {
        sprintf(buf,"KEY CODE IS %d  ",key);
        dispcolor_DrawString_Bg(1,1,FONTID_6X8M,buf,WHITE,BLUE);
        dispcolor_Update();
    }

    sprintf(buf,"%02d:%02d ",i/60,i%60);
    dispcolor_DrawString_Bg(45,20,FONTID_16F,buf,color_24_to_16(COLOR_RED),BLUE);

    dispcolor_Update();

    simlcd_delay(20);

    j++;
    if(j%25==0)i++;
}

int main(int argc,char *argv[])
{
    dispcolor_Init(128,64);
    dispcolor_FillScreen(BLUE);

    dispcolor_DrawString(20,40,FONTID_16F,"Hello World!",color_24_to_16(COLOR_YELLOW));
    dispcolor_Update();

    simlcd_play();
    return 0;
}

