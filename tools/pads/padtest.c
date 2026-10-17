/* Guided pad tester: asks for each N64 button in turn on each pad and records what SDL
 * reports. Skips a step after 15 s of no input. Results also go to the log file. */
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
static FILE *lg;
static void out(const char *s){ fputs(s,stdout); fflush(stdout); if(lg){fputs(s,lg);fflush(lg);} }
static const char *steps[]={"A","B","Z (trigger under the pad)","START","L","R",
  "C-UP","C-DOWN","C-LEFT","C-RIGHT","D-PAD UP","D-PAD DOWN","D-PAD LEFT","D-PAD RIGHT",
  "STICK UP","STICK DOWN","STICK LEFT","STICK RIGHT"};
int main(void){
  char buf[512]; const char *home=getenv("HOME");
  snprintf(buf,sizeof buf,"%s/PsymaticArcade-Apps/logs/padtest.log",home); lg=fopen(buf,"w");
  SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,"1");
  if(SDL_Init(SDL_INIT_GAMECONTROLLER|SDL_INIT_JOYSTICK|SDL_INIT_EVENTS)!=0){snprintf(buf,sizeof buf,"init: %s\n",SDL_GetError());out(buf);return 1;}
  SDL_Delay(1000); SDL_GameController *pad[4]={0}; int n=0; SDL_Event e;
  while(SDL_PollEvent(&e)){}
  for(int i=0;i<SDL_NumJoysticks()&&n<4;i++) if(SDL_IsGameController(i)&&(pad[n]=SDL_GameControllerOpen(i))){
    snprintf(buf,sizeof buf,"pad %d = SDL instance %d, %s, path %s\n",n+1,SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(pad[n])),SDL_GameControllerName(pad[n]),SDL_JoystickPathForIndex(i));out(buf);n++;}
  snprintf(buf,sizeof buf,"%d pad(s) found\n\n",n); out(buf);
  for(int p=0;p<n;p++){
    snprintf(buf,sizeof buf,"===== Now use the pad you think is PAD %d. Let go of everything between prompts. =====\n",p+1); out(buf);
    for(unsigned s=0;s<sizeof steps/sizeof*steps;s++){
      snprintf(buf,sizeof buf,"Pad %d: press %s ... ",p+1,steps[s]); out(buf);
      SDL_Delay(400); while(SDL_PollEvent(&e)){}
      Uint32 end=SDL_GetTicks()+15000; int got=0;
      while(!got&&SDL_GetTicks()<end){
        while(SDL_PollEvent(&e)){
          if(e.type==SDL_CONTROLLERBUTTONDOWN){snprintf(buf,sizeof buf,"got BUTTON %s from instance %d\n",SDL_GameControllerGetStringForButton(e.cbutton.button),e.cbutton.which);out(buf);got=1;break;}
          if(e.type==SDL_CONTROLLERAXISMOTION&&abs(e.caxis.value)>20000){snprintf(buf,sizeof buf,"got AXIS %s%s from instance %d\n",SDL_GameControllerGetStringForAxis(e.caxis.axis),e.caxis.value>0?"+":"-",e.caxis.which);out(buf);got=1;break;}
        }
        SDL_Delay(5);
      }
      if(!got) out("nothing in 15 s, skipped\n");
    }
  }
  out("\nDone. Results saved to ~/PsymaticArcade-Apps/logs/padtest.log\n");
  SDL_Quit(); if(lg) fclose(lg); return 0;}
