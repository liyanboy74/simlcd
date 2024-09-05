#ifndef __simlcd_h__
#define __simlcd_h__

#include <stdint.h>
//#include <SDL2/SDL_scancode.h>

#define SIMLCD_USE_TOUCH

#ifdef __cplusplus
extern "C" {
#endif

void simlcd_init(uint16_t height,uint16_t width,uint8_t scale);
void simlcd_set_color(uint8_t r,uint8_t g,uint8_t b);
void simlcd_draw_point(int x,int y);
void simlcd_draw_rect(int x,int y,int w,int h);
void simlcd_update();
void simlcd_delay(uint32_t ms);

void simlcd_play();

// extern int loop(SDL_Scancode key);
extern int loop(int key);

#ifdef SIMLCD_USE_TOUCH
extern int simlcd_touch_event(uint32_t x,uint32_t y);
#endif

#ifdef __cplusplus
}
#endif

#endif
