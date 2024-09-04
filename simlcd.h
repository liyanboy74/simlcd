#ifndef __simlcd_h__
#define __simlcd_h__

#include <stdint.h>
#include <SDL2/SDL_scancode.h>

#ifdef __cplusplus
extern "C" {
#endif

void simlcd_init(uint16_t height,uint16_t width,uint8_t scale);
void simlcd_set_color(uint8_t r,uint8_t g,uint8_t b);
void simlcd_set_background_color(uint8_t r,uint8_t g,uint8_t b);
void simlcd_draw_point(int x,int y);
void simlcd_draw_rect(int x,int y,int w,int h);
void simlcd_update();
void simlcd_delay(uint32_t ms);

void simlcd_play();

extern void loop(SDL_Scancode key);

#ifdef __cplusplus
}
#endif

#endif