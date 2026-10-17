/* Raw joystick view (no gamecontroller mapping). Rest dump, or guided per-button when
 * run with "guided". Run with SDL_JOYSTICK_HIDAPI=0 SDL_JOYSTICK_MFI=0 for the plain HID
 * backend. Output also to ~/PsymaticArcade-Apps/logs/padraw.log */
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
static FILE *lg;
static void out(const char *f, ...) { char b[1024]; va_list a; va_start(a,f); vsnprintf(b,sizeof b,f,a); va_end(a); fputs(b,stdout); fflush(stdout); if(lg){fputs(b,lg);fflush(lg);} }
static const char *steps[]={"A","B","Z","START","L","R","C-UP","C-DOWN","C-LEFT","C-RIGHT","D-PAD UP","D-PAD DOWN","D-PAD LEFT","D-PAD RIGHT","STICK UP","STICK DOWN","STICK LEFT","STICK RIGHT"};
int main(int argc,char**argv){
  char p[512]; snprintf(p,sizeof p,"%s/PsymaticArcade-Apps/logs/padraw.log",getenv("HOME")); lg=fopen(p,argc>1?"w":"a");
  if(SDL_Init(SDL_INIT_JOYSTICK)){out("init %s\n",SDL_GetError());return 1;}
  SDL_Delay(1200); SDL_JoystickUpdate();
  int n=SDL_NumJoysticks(); SDL_Joystick *j[4]={0};
  for(int i=0;i<n&&i<4;i++){ j[i]=SDL_JoystickOpen(i); char g[64]; SDL_JoystickGetGUIDString(SDL_JoystickGetGUID(j[i]),g,64);
    out("joy %d: %s guid=%s axes=%d buttons=%d hats=%d\n",i,SDL_JoystickName(j[i]),g,SDL_JoystickNumAxes(j[i]),SDL_JoystickNumButtons(j[i]),SDL_JoystickNumHats(j[i])); }
  SDL_Delay(300); SDL_JoystickUpdate();
  for(int i=0;i<n&&i<4;i++){ out(" rest joy%d axes:",i); for(int a=0;a<SDL_JoystickNumAxes(j[i]);a++) out(" a%d=%d",a,SDL_JoystickGetAxis(j[i],a));
    out("  buttons down:"); for(int b=0;b<SDL_JoystickNumButtons(j[i]);b++) if(SDL_JoystickGetButton(j[i],b)) out(" b%d",b);
    for(int h=0;h<SDL_JoystickNumHats(j[i]);h++) out("  h%d=%d",h,SDL_JoystickGetHat(j[i],h)); out("\n"); }
  if(argc<2||strcmp(argv[1],"guided")){ SDL_Quit(); return 0; }
  Sint16 rest[4][16]; for(int i=0;i<n&&i<4;i++) for(int a=0;a<SDL_JoystickNumAxes(j[i])&&a<16;a++) rest[i][a]=SDL_JoystickGetAxis(j[i],a);
  for(int pd=0;pd<n&&pd<2;pd++){ out("\n===== PAD %d (let go between prompts) =====\n",pd+1);
    for(unsigned s=0;s<sizeof steps/sizeof*steps;s++){ out("Pad %d: press %s ... ",pd+1,steps[s]); SDL_Delay(500); SDL_Event e; while(SDL_PollEvent(&e)){}
      Uint32 end=SDL_GetTicks()+15000; int got=0;
      while(!got&&SDL_GetTicks()<end){ while(SDL_PollEvent(&e)){
          if(e.type==SDL_JOYBUTTONDOWN){out("button b%d (joy %d)\n",e.jbutton.button,e.jbutton.which);got=1;break;}
          if(e.type==SDL_JOYHATMOTION&&e.jhat.value){out("hat h%d=%d (joy %d)\n",e.jhat.hat,e.jhat.value,e.jhat.which);got=1;break;}
          if(e.type==SDL_JOYAXISMOTION){int w=e.jaxis.which,a=e.jaxis.axis; if(w<4&&a<16&&abs(e.jaxis.value-rest[w][a])>16000){out("axis a%d %d (rest %d) (joy %d)\n",a,e.jaxis.value,rest[w][a],w);got=1;break;}}
        } SDL_Delay(5);} if(!got) out("nothing, skipped\n"); } }
  out("\nDone.\n"); SDL_Quit(); return 0; }
