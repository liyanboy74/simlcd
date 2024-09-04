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
  SDL_CreateWindowAndRenderer(WIDTH*SCALE,HEIGHT*SCALE,0,&window,&renderer);
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

void simlcd_play()
{
  while(true)
  {
    if(SDL_PollEvent(&windowEvent))
    {
      if(SDL_QUIT==windowEvent.type)
      {
        break;
      }
      else if( windowEvent.type == SDL_KEYDOWN )
      {
        loop(windowEvent.key.keysym.scancode);
      }
    }
    loop(SDL_SCANCODE_UNKNOWN);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}

void simlcd_set_background_color(uint8_t r,uint8_t g,uint8_t b)
{
  int i,j;
  simlcd_set_color(r,g,b);
  for(i=0;i<HEIGHT;i++)
    for(j=0;j<WIDTH;j++)
      simlcd_draw_point(j,i);
  simlcd_update();

  simlcd_set_color(~r,~g,~b);
}


