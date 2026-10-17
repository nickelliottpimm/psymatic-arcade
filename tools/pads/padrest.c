/* Prints each pad's driver and resting axis values after 1.5 s. Hands off while it runs. */
#include <SDL.h>
#include <stdio.h>
int main(void){
  SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,"1");
  if(SDL_Init(SDL_INIT_GAMECONTROLLER)){printf("init %s\n",SDL_GetError());return 1;}
  SDL_Delay(1500); SDL_GameControllerUpdate();
  printf("%d joysticks\n",SDL_NumJoysticks());
  for(int i=0;i<SDL_NumJoysticks();i++){ if(!SDL_IsGameController(i)){printf(" [%d] %s (not a gamecontroller)\n",i,SDL_JoystickNameForIndex(i));continue;}
    SDL_GameController *c=SDL_GameControllerOpen(i); SDL_Delay(300); SDL_GameControllerUpdate();
    char g[64]; SDL_JoystickGetGUIDString(SDL_JoystickGetDeviceGUID(i),g,64);
    printf(" [%d] %s path=%s guid=%s\n     lx %d ly %d rx %d ry %d lt %d rt %d\n",i,SDL_GameControllerName(c),SDL_JoystickPathForIndex(i),g,
      SDL_GameControllerGetAxis(c,0),SDL_GameControllerGetAxis(c,1),SDL_GameControllerGetAxis(c,2),SDL_GameControllerGetAxis(c,3),SDL_GameControllerGetAxis(c,4),SDL_GameControllerGetAxis(c,5)); }
  SDL_Quit(); return 0;}
