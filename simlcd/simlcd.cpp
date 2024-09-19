
#include "simlcd.h"

SDL_Event windowEvent;

simlcd_buffer_t simlcd_init(uint16_t height,uint16_t width,uint8_t scale)
{
  simlcd_buffer_t buf;
  buf.h=height;
  buf.w=width;
  buf.scale=scale+1;
  buf.buf=(uint32_t*)calloc(sizeof(uint32_t),buf.h*buf.w);
  buf.displayed=false;
  return buf;
}

void simlcd_deinit(simlcd_buffer_t *buf)
{
  free(buf->buf);
  if(buf->displayed)SDL_DestroyWindow(buf->window);
}

void simlcd_set_color(simlcd_buffer_t *buf,uint8_t r,uint8_t g,uint8_t b)
{
  buf->selected_color=(uint32_t)((r<<16)|(g<<8)|b);
  // SDL_SetRenderDrawColor(renderer,r,g,b,SDL_ALPHA_OPAQUE);
}

void simlcd_draw_point(simlcd_buffer_t *buf,int x,int y)
{
  buf->buf[(y*buf->w)+x]=buf->selected_color;
}

uint32_t simlcd_get_point(simlcd_buffer_t *buf,int x,int y)
{
  return buf->buf[(y*buf->w)+x];
}

void simlcd_draw_rect(simlcd_buffer_t *buf,int x,int y,int w,int h)
{
  static SDL_Rect rect;
  static int i,j;

  rect.x=x;
  rect.y=y;

  rect.h=h;
  rect.w=w;

  for(i=rect.x;i<rect.x+rect.w;i++)
      for(j=rect.y;j<rect.y+rect.h;j++)
        buf->buf[(j*buf->w)+i]=buf->selected_color;

}

void simlcd_display(simlcd_buffer_t *buf)
{
  int i,j;
  uint32_t color;
  SDL_Rect rect;
  static uint32_t wxp=50;

  if(buf->displayed==false)
  {
    // SDL_CreateWindowAndRenderer(WIDTH*SCALE,HEIGHT*SCALE,0,&window,&renderer);
    buf->window=SDL_CreateWindow("",wxp,50,buf->w*buf->scale,buf->h*buf->scale,0);
    buf->renderer=SDL_CreateRenderer(buf->window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //SDL_Init(SDL_INIT_EVERYTHING);
    buf->displayed=true;
    wxp+=(buf->w*buf->scale);
  }

  SDL_RenderClear(buf->renderer);
  for(i=0;i<buf->h;i++)
  {
    for(j=0;j<buf->w;j++)
    {
      color=buf->buf[(i*buf->w)+j];
      SDL_SetRenderDrawColor(buf->renderer,(color>>16)&0xff,(color>>8)&0xff,(color>>0)&0xff,SDL_ALPHA_OPAQUE);

      // SDL_RenderDrawPoint(renderer, j, i);
      rect.x=j*buf->scale;
      rect.y=i*buf->scale;
      rect.h=buf->scale;
      rect.w=buf->scale;
      SDL_RenderFillRect(buf->renderer,&rect);
    }
  }
  SDL_RenderPresent(buf->renderer);
}

void simlcd_delay(uint32_t ms)
{
  SDL_Delay(ms);
}

#ifdef SIMLCD_USE_TOUCH
int simlcd_send_touch(uint32_t x,uint32_t y,uint16_t event)
{
  static uint32_t ox,oy;
  x=x/LCD_BUFFER.scale;
  y=y/LCD_BUFFER.scale;
  if(x>=LCD_BUFFER.w||x<0||y>=LCD_BUFFER.h||y<0) return 0;
  return simlcd_touch_event(x,y,event);
}
#endif

void simlcd_play()
{
  int ret=0;
  while(true)
  {
    if(SDL_PollEvent(&windowEvent))
    {
      if(windowEvent.window.event == SDL_WINDOWEVENT_CLOSE)
      {
        ret=-1;
      }
      else if(windowEvent.type==SDL_QUIT)
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
        ret=simlcd_send_touch(windowEvent.button.x,windowEvent.button.y,(uint16_t)windowEvent.type);
        #endif
      }
    }
    else ret=loop((int)SDL_SCANCODE_UNKNOWN);

    if(ret!=0)break;
  }

  simlcd_deinit(&LCD_BUFFER);
  simlcd_exit();
  SDL_Quit();
}
