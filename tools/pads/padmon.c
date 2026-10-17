/* Records raw SDL axis values from every pad: 15 s hands-off, 15 s of C-up taps, 15 s hands-off.
 * Reports rest range per axis and every C-axis release (time to return under 6553 (20%)).
 * Output: ~/PsymaticArcade-Apps/logs/padmon.log */
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
static FILE *lg;
static void out(const char *f, ...) { char b[512]; va_list a; va_start(a,f); vsnprintf(b,sizeof b,f,a); va_end(a); fputs(b,stdout); fflush(stdout); if(lg){fputs(b,lg);fflush(lg);} }
static const char *AX[6]={"leftx","lefty","rightx","righty","ltrig","rtrig"};
int main(void){
  char p[512]; snprintf(p,sizeof p,"%s/PsymaticArcade-Apps/logs/padmon.log",getenv("HOME")); lg=fopen(p,"w");
  SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,"1");
  if(SDL_Init(SDL_INIT_GAMECONTROLLER|SDL_INIT_EVENTS)){out("init %s\n",SDL_GetError());return 1;}
  SDL_Delay(800); SDL_GameController *c[4]={0}; int n=0;
  for(int i=0;i<SDL_NumJoysticks()&&n<4;i++) if(SDL_IsGameController(i)) c[n++]=SDL_GameControllerOpen(i);
  out("%d pads\n",n);
  const char *phase[3]={"HANDS OFF both pads (15 s)","Tap C-UP about 5 times on EACH pad, then let go (15 s)","HANDS OFF again (15 s)"};
  for(int ph=0;ph<3;ph++){
    int mn[4][6],mx[4][6]; long sum[4][6]; long cnt=0; for(int i=0;i<4;i++)for(int a=0;a<6;a++){mn[i][a]=99999;mx[i][a]=-99999;sum[i][a]=0;}
    int held[4][6]={{0}}; Uint32 rel[4][6]={{0}};
    out("\n== %s ==\n",phase[ph]);
    Uint32 t0=SDL_GetTicks(), end=t0+15000, lastprint=t0;
    while(SDL_GetTicks()<end){
      SDL_GameControllerUpdate(); Uint32 now=SDL_GetTicks(); cnt++;
      for(int i=0;i<n;i++) for(int a=0;a<6;a++){
        int v=SDL_GameControllerGetAxis(c[i],(SDL_GameControllerAxis)a);
        if(v<mn[i][a])mn[i][a]=v; if(v>mx[i][a])mx[i][a]=v; sum[i][a]+=v;
        if(a==2||a==3){ /* C-buttons */
          if(abs(v)>16000 && !held[i][a]){held[i][a]=1; out("  %5.2fs pad%d %s pressed (%d)\n",(now-t0)/1000.0,i+1,AX[a],v);}
          if(held[i][a]==1 && abs(v)<16000){held[i][a]=2; rel[i][a]=now; out("  %5.2fs pad%d %s released, value %d\n",(now-t0)/1000.0,i+1,AX[a],v);}
          if(held[i][a]==2 && abs(v)<6553){held[i][a]=0; out("  %5.2fs pad%d %s back to centre after %u ms (%d)\n",(now-t0)/1000.0,i+1,AX[a],now-rel[i][a],v);}
        } else if(ph!=1 && abs(v)>3000 && a<2 && now-lastprint>250){ lastprint=now; out("  %5.2fs pad%d %s off-centre: %d\n",(now-t0)/1000.0,i+1,AX[a],v); }
      }
      SDL_Delay(2);
    }
    for(int i=0;i<n;i++){ out(" pad%d:",i+1); for(int a=0;a<4;a++) out("  %s[min %d max %d avg %ld]",AX[a],mn[i][a],mx[i][a],sum[i][a]/(cnt?cnt:1)); out("\n"); }
  }
  out("\nDone. Saved to ~/PsymaticArcade-Apps/logs/padmon.log\n"); SDL_Quit(); return 0; }
