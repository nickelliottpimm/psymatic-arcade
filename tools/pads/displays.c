/* Lists displays as SDL numbers them (the value for Video.Display). */
#include <SDL.h>
#include <stdio.h>
int main(void){ if(SDL_Init(SDL_INIT_VIDEO)){printf("%s\n",SDL_GetError());return 1;}
  for(int i=0;i<SDL_GetNumVideoDisplays();i++){SDL_Rect r;SDL_DisplayMode m;SDL_GetDisplayBounds(i,&r);SDL_GetCurrentDisplayMode(i,&m);
    printf("display %d: \"%s\"  %dx%d at (%d,%d)  %d Hz\n",i,SDL_GetDisplayName(i),m.w,m.h,r.x,r.y,m.refresh_rate);} SDL_Quit(); return 0;}
