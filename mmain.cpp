#include "simlcd.h"
#include "dispcolor.h"
#include "font.h"
#include "color.h"

void loop(SDL_Scancode key)
{
    char buf[64];
    if(key)
    {
        sprintf(buf,"%-03d",key);
        dispcolor_DrawString_Bg(0,0,FONTID_6X8M,buf,BLUE,BLACK);
        simlcd_update();
    }
}

int main(int argc,char *argv[])
{
    dispcolor_Init(128,64);

    dispcolor_DrawString(20,40,FONTID_16F,"Hello World!",0xf0f0);
    dispcolor_Update();

    simlcd_play();
    return 0;
}

