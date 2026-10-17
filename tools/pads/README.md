# Pad and display tools

Small SDL2 programs used to diagnose the N64-style USB pads (clones that
report as a Switch Pro, `057e:2009`). Build against an SDL2.framework,
for example the 2.32.10 one in `~/PsymaticArcade-Apps/deps/sdl2-2.32.10`:

```
F=~/PsymaticArcade-Apps/deps/sdl2-2.32.10
clang -include stdarg.h -o padtest padtest.c -I$F/SDL2.framework/Headers -F$F -framework SDL2 -Wl,-rpath,$F
```

| Tool | What it does | Log |
|---|---|---|
| `padtest` | Guided: asks for each N64 button per pad and prints the SDL name | `~/PsymaticArcade-Apps/logs/padtest.log` |
| `padmon` | 45 s: rest ranges, C-button press/release timing | `.../logs/padmon.log` |
| `padrest` | Rest values per pad and driver (try with `SDL_JOYSTICK_*` env) | stdout |
| `padraw` | Raw joystick view without the gamecontroller mapping | `.../logs/padraw.log` |
| `displays` | SDL display indices (the value for PD `Video.Display`) | stdout |
| `pd_n64pads.py` | Rewrites a PD `pd.ini` for these pads (N64 layout, C on right stick) | in place |

Findings from these tools are in `docs/findings.md` under "Controllers".
