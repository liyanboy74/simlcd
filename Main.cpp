#include <iostream>
#include <SDL2/SDL.h>

const int WIDTH = 250,HEIGHT=250;

int main(int argc,char *argv[])
{
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window *window=SDL_CreateWindow("App",SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,
    SDL_WINDOW_ALLOW_HIGHDPI);

  SDL_Event windowEvent;

  while(true)
  {
    if(SDL_PollEvent(&windowEvent))
    {
      if(SDL_QUIT==windowEvent.type)
      {
        break;
      }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
