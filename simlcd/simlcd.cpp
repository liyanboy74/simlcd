#include <iostream>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "simlcd.h"

static uint16_t HEIGHT=64, WIDTH=128;
static uint8_t SCALE=1;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event windowEvent;
SDL_TextInputEvent textEvent;

void simlcd_init(uint16_t height,uint16_t width,uint8_t scale)
{
  if(window!=NULL)return;
  HEIGHT=height;
  WIDTH=width;
  SCALE=scale+1;
  SDL_Init(SDL_INIT_EVERYTHING);

  //SDL_CreateWindowAndRenderer(WIDTH*SCALE,HEIGHT*SCALE,0,&window,&renderer);
  window=SDL_CreateWindow("SIMLCD",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH*SCALE,HEIGHT*SCALE,0);
  renderer=SDL_CreateRenderer(window,0,0);
}

void simlcd_set_color(uint8_t r,uint8_t g,uint8_t b)
{
  SDL_SetRenderDrawColor(renderer,r,g,b,SDL_ALPHA_OPAQUE);
}

void simlcd_draw_point(int x,int y)
{
  if(SCALE>1)
  {
    SDL_Rect rect;

    rect.x=x*SCALE;
    rect.y=y*SCALE;

    rect.h=SCALE;
    rect.w=SCALE;

    SDL_RenderFillRect(renderer,&rect);
  }
  else
    SDL_RenderDrawPoint(renderer, x, y);
}

void simlcd_draw_rect(int x,int y,int w,int h)
{
  SDL_Rect rect;

  rect.x=x*SCALE;
  rect.y=y*SCALE;

  rect.h=SCALE*h;
  rect.w=SCALE*w;

  SDL_RenderFillRect(renderer,&rect);
}

void simlcd_update()
{
  SDL_RenderPresent(renderer);
}

void simlcd_delay(uint32_t ms)
{
  SDL_Delay(ms);
}

#ifdef SIMLCD_USE_TOUCH
int simlcd_send_touch(uint32_t x,uint32_t y)
{
  static uint32_t ox,oy;

  x=x/SCALE;
  y=y/SCALE;

  if(x>=WIDTH||x<0||y>=HEIGHT||y<0) return 0;

  if(ox!=x || oy!=y)
  {
    ox=x;
    oy=y;
    return simlcd_touch_event(x,y);
  }
  else return 0;
}
#endif

void simlcd_play()
{
  int ret=0;
  bool mosePushed=false;
  while(true)
  {
    if(SDL_PollEvent(&windowEvent))
    {
      if(windowEvent.type==SDL_QUIT)
      {
        ret=-1;
      }
      else if( windowEvent.type == SDL_KEYDOWN )
      {
        ret=loop((int)windowEvent.key.keysym.scancode);
      }
      else if(windowEvent.type>=SDL_MOUSEMOTION && windowEvent.type<=SDL_MOUSEWHEEL)
      {
        #ifdef SIMLCD_USE_TOUCH
        if(windowEvent.type==SDL_MOUSEBUTTONDOWN)
        {
          mosePushed=true;
          ret=simlcd_send_touch(windowEvent.button.x,windowEvent.button.y);
        }
        else if(windowEvent.type==SDL_MOUSEBUTTONUP)mosePushed=false;
        else if(windowEvent.type==SDL_MOUSEMOTION)
        {
          if(mosePushed)ret=simlcd_send_touch(windowEvent.button.x,windowEvent.button.y);
        }
        #endif
      }
    }
    else ret=loop((int)SDL_SCANCODE_UNKNOWN);

    if(ret!=0)break;
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}

