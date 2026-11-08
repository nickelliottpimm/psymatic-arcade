# Handover: moving Psymatic Arcade to a Raspberry Pi

Written 2026-11-08 by the chat thread, for a separate Pi setup session.
Source of truth for everything the Mac session did: `docs/status.md`,
`docs/findings.md`, `docs/playtest-notes.md`. Read `CLAUDE.md` first.

Status of this doc: nothing on the Pi has been built or run. Every Pi
statement below is either read from a repo (with file:line) or marked
UNVERIFIED. Treat UNVERIFIED as a thing to test, not a fact.

## 1. Goal

Run the Psymatic Arcade games on a Raspberry Pi as a small, cheap event host,
driving the same wall: one 16:9 HDMI output, a 2x2 splitter, four RF
modulators, four 4:3 CRTs. Each quadrant must be a 4:3 image stretched
horizontally by 4/3 to 16:9 (see `CLAUDE.md`, "Output geometry").

The Pi is a **Raspberry Pi 4 Model B, 4 GB**, bare board (no case), 1.5 GHz
quad-core, dual micro-HDMI (confirmed by Zooey 2026-11-08).

Decision 0001 said lighter games (Mario Kart 64) go on a Pi and heavier
builds go on the M1 Max Mac Studio. That is still the plan unless the tests
below say otherwise. Do not assume all games will fit on the Pi.

## 2. What exists today (M1 MacBook, 2026-10-18)

All four games run and have been played on the wall. Details in
`docs/status.md`. Summary:

| Game | Port | Version on the Mac | License | Our changes |
|---|---|---|---|---|
| Mario Kart 64 | HarbourMasters/SpaghettiKart | 1.0.0 release (arm64 zip) | **none** | stretch via config only; CPU-racer patch kept as a patch file |
| GoldenEye 007 | seb-patron/goldeneye-native | built from source, `0a6572e` + our commits | MIT (port layer); decomp source has no license | fork, branch `psymatic/stretch43` |
| Perfect Dark | fgsfdsfgs/perfect_dark | built from source, `32a1cb9` + our commits | MIT | fork, branch `psymatic/stretch43` |
| GoldenEye X | Dab's Mod v3.14.0 on the PD port, GE-X 6a | built from source | see repo | fork, branch `psymatic/stretch43` |

Forks are git submodules under `ports/`. SpaghettiKart is not forked because
it has no license; its patch lives in `ports/pending-patches/spaghettikart/`.
Patch files for the other three are also in `ports/pending-patches/`.

Playtest summary (`docs/playtest-notes.md`): all four games work; GoldenEye X
is the better GoldenEye for the wall; Mario Kart 64 was very entertaining;
launching and quitting is too clunky for a public exhibition.

## 3. What each port says about Linux and ARM

Read from the repos on 2026-11-08. No Pi has been tested.

- **GoldenEye Native** (`ports/goldeneye-native/README.md:160`): "Linux
  (x86-64 and arm64), OpenGL. Builds. Verified on Debian 12 aarch64." But
  `README.md:383`: "Linux is unplayed. It builds and renders; nobody has
  played a mission through on it." Debian 12 is the base of the Bookworm
  Raspberry Pi OS, so this is the best lead, still unproven on a Pi GPU.
- **Perfect Dark port** (`ports/perfect_dark/README.md:40-42`): supported
  platforms are Linux i686 and x86_64, macOS x86_64 and arm64, Switch arm64.
  Linux arm64 is not listed. `README.md:200` says other platforms might
  work but are untested. Expect to build from source.
- **Dab's Mod** (`ports/perfect-dark-dabs-mod/README.md:40`): Linux release
  is `./pd.x86_64` only. Same source-build expectation. GoldenEye X depends
  on it.
- **SpaghettiKart**: no Linux ARM information in our repo. UNVERIFIED lead:
  a retrohandhelds.gg article titled "[Update: Now on PortMaster] You Haven't
  Played Mario Kart 64 Like This Before" suggests an ARM Linux build exists
  via PortMaster. I only saw the title. Check the SpaghettiKart repo and
  its `docs/BUILDING.md` for Linux.
- **No performance numbers for any of these on any Pi.** I searched and
  found none. That is the first thing to measure.

### What a Pi 4 with 4 GB means

- **GPU API is probably not the blocker.** The Perfect Dark port needs
  "OpenGL 3.0/ES3.0 or above" (`ports/perfect_dark/README.md:75`). Its window
  code tries GL 3.0 compatibility, then 4.1 core, 3.2 core, ES 3.0, then 2.1
  (`port/fast3d/gfx_sdl2.cpp:163-167`; Dab's Mod has the same list at
  `:208-212`). As far as I know the Pi 4's Mesa driver offers GLES 3.1 and GL
  3.x. UNVERIFIED: confirm with `eglinfo` or `glxinfo -B` and record it. Speed,
  not the API version, is the open question.
- **Expectation.** Mario Kart 64 is the only realistic first target. Four
  players on Perfect Dark, GoldenEye X or GoldenEye Native on a Pi 4 is a long
  shot. Run them as experiments, report the numbers, and do not promise them.
- **Building on 4 GB can run out of memory.** Use a low job count (for example
  `-j2`) and add swap if the compiler gets killed. The Mac builds cannot be
  reused: they are macOS arm64, not Linux.
- **Bare board.** Without a heatsink or fan a Pi 4 throttles under sustained
  load, and an under-spec power supply causes under-voltage. Record both
  (section 9).

## 4. Things that are Mac-only and must be replaced

- `tools/launchers/*.command` and Desktop shortcuts. Replace with shell
  scripts plus a `.desktop` file or a systemd user service.
- `tools/build-spaghettikart.sh` uses Homebrew. Linux needs the apt
  equivalent. Starship's apt list is a useful model:
  `HarbourMasters/Starship docs/BUILDING.md:89` (gcc/clang, cmake, ninja,
  libsdl2-dev, libpng, libsdl2-net, libzip, nlohmann-json, tinyxml2,
  spdlog, boost, libopengl-dev, libogg, libvorbis). SpaghettiKart's own
  list may differ; read its BUILDING.md.
- SDL2 framework swaps (PD and Dab's Mod) and `GETV_SDL_SRC` (GoldenEye).
  See section 6: on Linux the system SDL version decides this.
- Config paths. Mac: `~/Library/Application Support/...`. Perfect Dark on
  Linux reads `~/.local/share/perfectdark` (`ports/perfect_dark/README.md:71`).
  Check each game's Linux path before copying settings.
- `Video.Display=1` (SDL display index, our patch) was chosen for the Mac's
  laptop-plus-CRT layout. On a Pi with one HDMI output in use it is likely
  0. Check with `tools/pads/displays.c`.
- Keys for fullscreen: Mario Kart and GoldenEye F11, Perfect Dark and GE-X
  Alt+Enter. Portable, but launchers on the Pi should start fullscreen
  without a keypress.
- Gatekeeper, quarantine and `chmod +x` notes do not apply on Linux.

## 5. Display and output

- Output a 16:9 mode. 1920x1080 at 60 Hz is the safe choice for the
  splitter (decision 0001 says it takes 1080 or 4K). Do not output 4:3.
- Mario Kart: `CVars.gAdvancedResolution.IgnoreAspectCorrection = 1` in
  `spaghettify.cfg.json`, with resolution aspect forced to 4:3. Confirmed on
  the wall (Mac). LowResMode overrides it and always pillarboxes.
- GoldenEye Native: env `GETV_STRETCH43=1` (our patch).
- PD and Dab's Mod: `[Video] Stretch43=1` in `pd.ini` (our patch).
- On Linux, test fullscreen under whichever display server the Pi OS
  defaults to (Wayland or X11). UNVERIFIED: whether SDL fullscreen and the
  chosen mode behave the same on both. If a game ends up pillarboxed or
  letterboxed on the wall, say what you see and which server was running.
- Pi 4 and Pi 5 both have two micro-HDMI ports. Record which port feeds
  the splitter.

## 6. Controllers: the part most likely to bite

Two USB N64-style pads are clones that report as a Nintendo Switch Pro
controller (`057e:2009`), both with serial `000000000001`.

- Root cause of stick and C-button drift on the Mac was an SDL 2.30.9 bug in
  its HIDAPI Switch driver. SDL 2.32.10 fixes it. See `docs/findings.md`,
  "Controllers". Measured at rest: 2.30.9 gave rx 8478 / ry -8054; 2.32.10
  gave rx 2551 / ry -3659.
- **First check on the Pi: which SDL2 version does each game link?** If it is
  older than 2.32.10, build SDL 2.32.10 from source and point the game at
  it, as was done for GoldenEye on the Mac. Do not assume the distro's SDL is
  new enough. Raspberry Pi OS versions differ; check with `sdl2-config --version`.
- UNVERIFIED on Linux: the kernel's own Switch Pro driver may also claim
  these pads, and `hidraw` permissions (udev rules) may block SDL's HIDAPI
  path. If pads are not seen, check `/dev/hidraw*` permissions before
  changing anything else. Use `tools/pads/padtest.c` and `padmon.c` (build
  against the Linux SDL; the README gives the macOS command only).
- Known button mapping (SDL names): A=`a`, B=`b`, Z=`lefttrigger`,
  Start=`start`, L=`leftshoulder`, R=`rightshoulder`, C-buttons = right
  stick, D-pad = `dp*`. No x, y, rt or back on these pads.
- SpaghettiKart gives all pads to port 1 and ignores them on ports 2-4. The
  fix is by hand each launch (Esc > Settings > Controller). Open problem,
  and a good candidate for a small patch or a config seed.
- GoldenEye Native needs `controls = 1.1` and explicit bindings. PD and GE-X
  need `ExtendedControls=0` for all four players
  (`tools/pads/pd_n64pads.py` does this).
- Known open issue (status.md, "Ideas"): after the pads sleep and re-pair,
  pad 1 can come back as player 2. Idea: pin player number to the physical
  USB socket (the HID path encodes the port). Test pad enumeration order on
  Linux; it may differ from macOS.

## 7. Suggested order of work on the Pi

Small steps. One change, build, play, evaluate. Ask before changes that
touch more than a couple of files.

1. Record the hardware (section 8). Install 64-bit Raspberry Pi OS. Record
   OS version, kernel, Mesa version, `sdl2-config --version`.
2. ROMs: copy to `~/PsymaticArcade-ROMs` on the Pi from the Mac or the share.
   Never into the repo. Check SHA-1 against the hashes in `docs/findings.md`.
3. Display: get a stable 1920x1080 @ 60 Hz mode on the splitter. Confirm
   with a test image that a 16:9 frame is cut into four clean quadrants.
4. Mario Kart 64 first. Try the Linux ARM route from section 3. If you
   have to build, write `tools/build-spaghettikart-linux.sh`.
5. Controllers: SDL version, pad enumeration, 2 pads, then 4.
6. Measure (section 9). If MK64 is not smooth at 4P, stop and report before
   going further. That decides whether this Pi is a MK64 box only.
7. GoldenEye Native (best Linux lead), then Perfect Dark, then GE-X.
8. Launcher and kiosk behaviour: boots straight to a choice of game, quit
   returns to it. Only after the games run.

## 8. Hardware and open questions

Answered by Zooey (2026-11-08):
- Pi 4 Model B, 4 GB, bare board, 1.5 GHz quad-core, dual micro-HDMI.

Still open (the Pi session should ask these in one go):
- Cooling (heatsink or fan, case) and power supply (the Pi 4 wants a 5 V 3 A
  USB-C supply).
- Storage: microSD or USB SSD.
- Does the Pi replace the Mac for events, or run alongside it?
- Which games must run on the Pi, and which can stay on the Mac Studio?
- How will ROMs get onto it?

## 9. How to know it works (numbers, not impressions)

For each game, at 1920x1080 @ 60 Hz output, record in `docs/findings.md`:

- Players (2 and 4) and mode tested.
- Frame rate over at least 10 minutes. Use the port's own FPS overlay if it
  has one, or a frame time log. Say how it was measured.
- `vcgencmd measure_temp` at the start and end.
- `vcgencmd get_throttled` at the end. `0x0` means no throttling or
  under-voltage was recorded.
- Whether pads were seen, in what order, and after sleep and re-pair.
- Any crash, with the exact log line.

## 10. Rules (full text in `CLAUDE.md` and `docs/project-instructions.md`)

- No ROMs in git. Ever.
- Audit before code. Report file:line first.
- Runtime toggles, default off, identical to vanilla.
- Findings are numbers. Record dead ends with why, in `docs/dead-ends.md`.
- Portable first: do not bake Pi-only hotkeys or paths into shared code.
  Pi-specific scripts go under `tools/pi/`.
- Chat decides, Code builds. Decisions go in `docs/decisions/` first.
- End each session by updating `docs/status.md` and committing.
- Direct, plain language.

## 11. Lylat Wars (Star Fox 64)

Proposed as game 5. Not set up. The US ROM is in the share:
`Star Fox 64 (USA) (Rev 1).z64` (should be US 1.1; check the SHA-1). See `docs/decisions/0004-lylat-wars-starship.md`.
For the Pi: Starship's CMake already has an aarch64 branch
(`HarbourMasters/Starship CMakeLists.txt:569-570`, `-mcpu=native`), but that is
not proof it runs on a Pi. Do the Mac test first, then try it on the Pi last.
