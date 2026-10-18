# Findings

Verified numbers and file:line refs go here. Anything under "Unverified leads"
came from web research in the chat thread on 2026-10-17 and has NOT been
confirmed by building or running. Code thread: verify, then move items up.

## Verified

(none yet)

## Checked from source (2026-10-17, cloud session, not build-tested)

Read from shallow clones and GitHub release pages in a Linux cloud session.
These are facts about the repos, not about whether anything runs. Nothing
here has been built or played on the M1 yet.

### ROM identification (what the laptop session should check)
- MK64 US: SHA-1 `579c48e211ae952530ffc8738709f078d5dd215e`, must be `.z64`
  (SpaghettiKart README.md:16-20).
- GoldenEye US: SHA-1 `abe01e4aeb033b6c0836819f549c791b26cfde83`
  (goldeneye-pc-port `ge007.u.sha1`; same hash in goldeneye-native
  `tools/install.sh:225`).
- Perfect Dark NTSC v1.1 (`ntsc-final`, "US Rev 1"): MD5
  `e03b088b6ac9e0080440efed07c1e40f`. The PD README gives MD5 only, no SHA-1
  (fgsfdsfgs/perfect_dark README.md:6). v1.0 MD5 is
  `7f4171b0c8d17815be37913f535e4e93` and is not the one GoldenEye X wants.
- Format check: first 4 bytes `80 37 12 40` = .z64 (big-endian, wanted),
  `37 80 40 12` = .v64 (byte-swapped), `40 12 37 80` = .n64 (little-endian).

### SpaghettiKart (HarbourMasters/SpaghettiKart)
- Latest release: 1.0.0 "Bolognese Alfa", 25 Feb (2026). Assets include
  `spaghetti-mac-arm64.zip` (7.19 MB) and `spaghetti-mac-intel-x64.zip`.
  Use the arm64 zip on the M1.
- LICENSE: none. No file matching license/copying anywhere in the tree at
  `5073d2e` (`git ls-tree -r`). Blocker for forking until clarified.
- Last commit on main: `5073d2e`, 2026-10-11, "Remove jitter fix slider (#767)".
- README: Metal is the default backend on macOS. OpenGL is the fallback,
  set in `spaghettify.cfg.json` (README.md:67). Nightly mac builds are linked
  from README.md:93-94.

### GoldenEye: jkdansereau/goldeneye-pc-port
- License: MIT (c) 2026 James Dansereau, covering port/, build system,
  tools_pc/, docs. NOTICE says vendored code keeps its own licenses, e.g.
  gzip sources under GPL-2.0.
- Last commit on main: `fda76b6`, 2026-10-07 (post-v0.5.0 docs merge).
  Branches: `main`, `release/v0.6.0`.
- v0.5.0 (07 Oct) assets: win64 zip and linux-x86_64 tar.gz only. No macOS.
- macOS has never been built: docs/building.md:32-34 says "the macOS column
  is best-effort guidance and has never been built or run there."
  docs/ROADMAP.md:178 lists macOS/ARM as open, parked until after 1.0, and
  depending on a 64-bit ABI hazard sweep (ROADMAP.md:149). The roadmap
  mentions a `macos` branch, but there is none on origin. Only PR refs
  `refs/pull/88/head` and `refs/pull/95/head` exist.
- Build deps (macOS): Xcode CLT, `brew install cmake sdl2` (building.md
  table). The `build-pc.sh` header says `brew install cmake libsdl2-dev`,
  which is wrong: there is no such brew formula. Asset extraction also needs
  MIPS binutils (`binutils-mips-linux-gnu` or equivalent).
- Split-screen: ROADMAP.md:132 says 2P and 3P passed a maintainer playtest
  on 2026-10-03. 4P with real pads is "still owed".
- Expectation for Step 3: a source build on Apple Silicon is likely to hit
  build breaks or 64-bit pointer bugs. Time-box it.

### GoldenEye: "GoldenEye Native" (identified)
- Original repo: SegfaultEvan/goldeneye-native, deleted 2026-08-29 (per the
  fork's page). Community continuation: seb-patron/goldeneye-native.
  birdturtle/goldeneye-native is a fork of that, at the same commit.
- Last commit: `0a6572e`, 2026-09-15 (seb-patron, PR #100).
- License: MIT (c) 2026 SegfaultEvan, for the platform layer and tools.
  NOTICE says the decomp source (n64decomp/007, fetched at build time into
  vendor/ge-decomp/) has no license file and libultra carries SGI headers.
- Mac build: there is no prebuilt release. A source build is done by
  `Install on Mac.command`, which runs `tools/install.sh`. The README lists
  "macOS (Apple silicon): Builds and plays. Primary target", with
  performance measured on an M1.
- What install.sh does (read, not run): it does not use sudo or download a
  ROM. It clones n64decomp/007 with `--depth 1` and builds SDL2 from source.
  It takes `--rom <path>`, so the ROM can stay in ~/PsymaticArcade-ROMs and
  does not need to be on the Desktop. It checks SHA-1 `abe01e4a...` and
  copies the ROM into its own `roms/ge007.u.z64`. The README says it needs
  about 4 GB of disk and takes 10-40 minutes the first time.
- Split-screen: the README feature table marks it "Done: two, three and
  four players". Co-op 2-4P is beta and LAN netplay is beta (it desyncs).

### Perfect Dark PC port (fgsfdsfgs/perfect_dark)
- Has a Mac build: the `ci-dev-build` release (commit `32a1cb9`,
  2026-08-13) includes `pd-arm64-osx.tar.xz` and `pd-x86_64-osx.tar.xz`.
  README.md:41 says "MacOS: x86_64 (OS 10.9+), arm64 (OS 11.0+)".
- License: MIT (c) 2022 Ryan Dwyer. Default branch: `port`.
- Not set up, per the laptop prompt.

## Checked on the M1 laptop (2026-10-17)

Machine: Apple M1, macOS 15.7.3 (24G419).

### ROMs
- Share path: the ROMs are at
  `/Volumes/01_PRODUCTION/01_PROJECTS/Psymatic2000/04_Gaming/2026_PsymaticArcade/ROMs`.
  That is under `01_PROJECTS/`, not directly under the volume as the laptop
  prompt says. Copied to `~/PsymaticArcade-ROMs`.
- All three match the reference hashes above. All three are `.z64`
  (`80 37 12 40`):
  - `Mario Kart 64 (USA).z64`: SHA-1 `579c48e2...d215e`, header `NKTE`, rev 00.
  - `GoldenEye 007 (USA).z64`: SHA-1 `abe01e4a...cde83`, header `NGEE`, rev 00.
  - `Perfect Dark (U) (V1.1) [!].z64`: SHA-1
    `af8788ac4d1a57260eae9c53ffe851fcf2a3319b`, MD5 `e03b088b...1e40f`
    (matches v1.1), header `NPDE`, rev 01.
- The share folder also holds `GE-X_6a_01-19-25/` and a
  `goldeneye-pc-port-main/` source snapshot. Neither has been copied or used.

### SpaghettiKart 1.0.0 on the M1
- `spaghetti-mac-arm64.zip`: SHA-256
  `d40314ed0cd8932c359239fb6dcd8554d4dd48e85be3c460c044004a88a03e80`.
  Unpacked to `~/PsymaticArcade-Apps/spaghettikart/unzipped/`.
- The zip has no `.app` bundle. It holds a bare `Spaghettify` binary
  (Mach-O arm64, ad-hoc linker-signed), `spaghetti.o2r`, `config.yml`,
  `yamls/` and `gamecontrollerdb.txt`. The binary links only system
  frameworks; Metal and OpenGL are both linked.
- Downloaded with curl, so no `com.apple.quarantine` xattr is set.
- Re-checked 2026-10-17: still no LICENSE/COPYING; last commit still `5073d2e`
  (2026-10-11).
- First run (12:50): a file picker appeared and was cancelled, so it exited
  with `[Engine.cpp:315] [error] No ROM selected.` This is the expected
  behaviour, not a bug. The ROM auto-detect scan (looks for `.z64` in the
  cwd) sits under `#elif unix` in `src/port/GameExtractor.cpp:138`. That
  macro is likely not defined on macOS, so expect the picker every time.
- Second run (12:53): picked the ROM in the dialog. Extraction took about
  1 minute and wrote `mk64.o2r` (26,664,858 bytes) and `spaghettify.cfg.json`
  next to the binary. The game boots and is playable on keyboard. Backend:
  Metal (`"Backend": {"Id": 2, "Name": "Metal"}`), audio SDL. The log shows
  only extractor "Found vtx" warnings, no errors. No controller tested yet.
- That session ran 12:53-13:44 and exited cleanly (exit 0, normal teardown).
  About every 5 minutes it logged `[error] RGBA Texture that isn't 16 or 32
  bit. Size = 1`. Its visible effect, if any, is unknown. The interval suggests
  attract/demo-mode looping while idle. Not investigated.
- Launch: `cd ~/PsymaticArcade-Apps/spaghettikart/unzipped && ./Spaghettify`
  (it must run with that cwd). The auto-mode classifier refuses to let Claude
  run this binary, so the user launches it with `!`.

### GoldenEye Native (seb-patron/goldeneye-native) on the M1
- Cloned at `0a6572e` to `~/PsymaticArcade-Apps/goldeneye-native`.
- Prereqs: the laptop had Xcode CLT, git, python3 3.9.6, make and clang,
  but no cmake. Installed Homebrew (native, `/opt/homebrew`) and
  `brew install cmake` (4.4.4, arm64). The Homebrew installer did not write
  `~/.zprofile`, so brew had to be added to PATH by hand.
- First `tools/install.sh --rom ...` run: patches 0001-0032 applied, with
  whitespace warnings only. Then it stopped at step 5 with
  `no SDL2 source at .../deps/SDL2-2.30.9`. Step 4 also printed
  `ImGui fetch failed` because the SDL headers were missing. The cause is a
  manual step that `docs/SETUP.md:286-315` documents and the README's quick
  install omits: the user must supply the SDL2 2.30.9 source. Fixed by
  unpacking the libsdl-org `release-2.30.9` asset `SDL2-2.30.9.tar.gz`
  (SHA-256 `24b574f71c87a763f50704bbb630cbe38298d544a1f890f099a4696b1d6beba4`)
  into `deps/`.
- Second run: the build completed. Game 167, assets 746, audio 40, port
  layer 80, all 0 failed. Only linker warning: `reducing alignment of section
  __DATA,__common from 0x8000 to 0x4000`. Output: `getv/build-mac/goldeneye`
  (19M, arm64) and `getv/build-mac/GoldenEye.app`. The ROM was copied to
  `roms/ge007.u.z64`. The default renderer is GL (`GETV_RENDERER=gl`); Metal
  is an option.
- Not yet run or played.

### Perfect Dark PC port (vanilla) on the M1
- `ci-dev-build` asset `pd-arm64-osx.tar.xz`, updated 2026-08-13, SHA-256
  `36a649bc011031286b65260a60bbb5317eb2d938371ff7ed63a3a40bef2ecbe2`.
  Unpacked to `~/PsymaticArcade-Apps/perfectdark/unpacked/pd-arm64-osx/`.
  It contains `pd.arm64`, `pd.pal.arm64`, `pd.jpn.arm64`, a bundled
  `SDL2.framework` and `data/`. No quarantine xattr (downloaded with curl).
- ROM copied to `data/pd.ntsc-final.z64` (MD5 re-checked: v1.1).
- The tarball loses the execute bit: `pd.arm64` unpacked as `-rw-r--r--`, so
  launching gave `zsh: permission denied: ./pd.arm64`. This is not
  Gatekeeper. Fixed with `chmod +x pd*arm64*`. The Dab's Mod binary kept
  its execute bit.
- Launchers: `~/Desktop/Psymatic Arcade/*.command`, one per game.
  These live outside the repo.

### GoldenEye X via Dab's Mod (DabDavis/perfect-dark-dabs-mod)
- GE-X 6a is a console ROM patch for PD v1.1
  (`GE-X_6a_01-19-25.xdelta`, SHA-256 `85de3d0e...e05c9`, on the share).
  Its FAQ recommends the 1964 60FPS emulator (Windows) until the mod moves to
  the PD decomp. Dab's Mod instead imports console patches into the PC port.
- Dab's Mod: MIT. Last push 2026-10-14. Release v3.14.0 (2026-10-03) asset
  `pd-dabs-mod-arm64-osx.tar.xz`, SHA-256
  `1f4f1dd48ca79831dc0500ace2a7dcbe4588031581a2c716ac02226c1a574d0d`.
  Unpacked to `~/PsymaticArcade-Apps/pd-dabs-mod/unpacked/pd-dabs-mod-arm64-osx/`,
  a separate folder so its `pd.ini` and saves stay apart from vanilla PD.
- Per its README: the PD ROM goes in `data/pd.ntsc-final.z64`. Console mods
  go in `mods/` as a zip or bare `.xdelta`, and are converted on first start
  with nothing on screen while that runs. The mod is then selected from
  Perfect Menu > **Perfect Dark Mods**, and `IMPORT.txt` in the converted
  folder says what could not be carried over. A GE-X hi-res `.htc` pack
  loads only when Extended Options > Texture Packs > Use Texture Packs is
  on (F8 toggles it). Up to 80 simulants.
- Set up: the PD ROM is in `data/`, `mods/GE-X_6a_01-19-25.zip` is a zip of
  the share folder (xdelta plus 1964 HIRES files), and the GoldenEye US ROM
  is in `added-content/`. The README says that last one gives GoldenEye's
  arenas, missions and music inside the PD engine, converted on first start
  into `mods/GoldenEye Arenas/`.
- Not yet run.

### macOS Gatekeeper (general guidance, not yet tried on this laptop)
- Unsigned downloaded apps: on Sequoia, Control-click > Open no longer
  bypasses Gatekeeper. Try to open the app once, then go to System Settings >
  Privacy & Security, scroll down, click "Open Anyway" and authenticate.
  The Terminal alternative is `xattr -dr com.apple.quarantine <app or folder>`.

## Unverified leads (from chat research, 2026-10-17)

### SpaghettiKart (HarbourMasters/SpaghettiKart)
- Native MK64 port by Harbour Masters. Needs US MK64 ROM in .z64 format.
- 1.0.0 release (reported Feb 2026): harder CPU, frame interpolation overhaul
  including 3/4P, new Rulesets system, expanded custom track system.
- License: at launch (June 2025) press said no license file was attached.
  Re-check the repo for a LICENSE file before forking.
- Pi 4 viability: no source found. Treat as unproven.

### GoldenEye 007 (N64) candidates
- jkdansereau/goldeneye-pc-port: decomp-based, same engine family as the
  Perfect Dark PC port. 2-4 player split-screen, widescreen, 60 fps, mouse or
  pad. Pre-1.0. v0.5.0 release lists Windows x86-64 and Linux x86-64 only, no
  macOS or ARM builds. NTSC-U only. 4P reportedly played live on Temple only.
  Roadmap lists split-screen as "verify" (merged 2026-10-01). Crash issue
  opened 2026-10-13. License and last commit: unchecked.
- "GoldenEye Native": an Aug 2026 article describes a launcher, bots, co-op and
  4P split-screen on Windows/Linux/macOS. Repo not identified. A separate
  report says KholdFuzion's GoldenRecomp had no release and an unfinished
  multiplayer interface around mid-Aug. Conflicting. Identify the repo first.
- n64decomp/007 and kholdfuzion/goldeneye_src: the decompilation itself
  (reported 100% decompiled Aug 2026). Needs the ROM to extract assets.
- akratch/mgb64: archived and discontinued Aug 18 2026. Do not use.
- SunJaycy/GoldenEye-Recomp: recompiles the Xbox 360 version, Windows-focused,
  needs Xbox game files. Does not fit the own-cartridges rule. Do not use.

### Perfect Dark / GoldenEye X
- GoldenEye X is a ROM mod of Perfect Dark, applied as a patch to the NTSC
  v1.1 ROM. Multiplayer fully supported, with simulant bots.
- Perfect Dark PC port: fgsfdsfgs/perfect_dark. Split-screen multiplayer
  works. macOS build status: unchecked.
- Dab's Mod (DabDavis/perfect-dark-dabs-mod) for the PD port loads GoldenEye X.
- Friends of Joanna (cylonicboom): a 4-player co/counter-op mod for the PD
  port, in progress.

## 4:3 to 16:9 stretch (2026-10-17, M1)

Problem: the splitter expects 16:9, so a 4:3 Mac mode (800x600) gets
pillarboxed before the modulators squeeze it. The Mac must output a 16:9
mode, and each game must fill it with its 4:3 image stretched by 4/3. The
external display currently reports 1280x1024 @ 60 Hz (5:4)
(`system_profiler SPDisplaysDataType`).

- SpaghettiKart: supported by a setting, with no code change.
  libultraship `60c9bb7` `src/fast/Fast3dGui.cpp:385-405`: Advanced
  Resolution with the aspect forced to 4:3 renders a 4:3 frame. The
  `gAdvancedResolution.IgnoreAspectCorrection` flag then skips the
  pillarbox and draws that frame at the full window size. Set
  `CVars.gAdvancedResolution.IgnoreAspectCorrection = 1` in
  `spaghettify.cfg.json`; a backup is saved beside it as `.bak-*`. Not yet
  seen on the wall. Note: LowResMode ("N64 mode") takes priority and always
  pillarboxes (`Fast3dGui.cpp:381-385`).
- GoldenEye Native: no stretch option. `getv/port/fast3d/gfx_pc.c:240-446`
  uses one uniform scale, `ge_scale()` (RATIO_X == RATIO_Y), and pillarboxes
  with `ge_offset_x()`. The `widescreen` key widens the FOV instead and is
  single-player only (docs/CONFIGURATION.md:120-133). A stretch would need
  a patch in our fork: separate X/Y scale and zero offset, behind a toggle.
- Perfect Dark port: no stretch option. The game aspect follows the window
  (`port/src/video.c:182-187`, `videoGetAspect` at :232), so a 16:9 window
  gives a wider FOV, not a stretched 4:3 image. A stretch would need a
  patch in our fork. Dab's Mod README has no aspect or stretch setting.

### Stretch patches (2026-10-17, built on the M1, not yet seen on the wall)
All are off by default. Each is committed on a local `psymatic/stretch43`
branch and not yet pushed or forked.
- SpaghettiKart: confirmed on the wall by the user with
  `IgnoreAspectCorrection = 1`. It works perfectly.
- GoldenEye Native: commit `a5bffda` on `0a6572e`, toggled by env
  `GETV_STRETCH43=1`. Per-axis `ge_scale_x()`/`ge_scale_y()` back
  RATIO_X/RATIO_Y, the pillarbox offsets become 0,
  `gfx_adjust_x_for_aspect_ratio()` is the identity, and the text overlay
  in `gfx_opengl.c` gets the same split. It overrides `widescreen`, which
  defaults ON (`port_support.c:203`). The fast3d files are generated and
  git-ignored, so the change is recorded in
  `getv/patches/thirdparty/0001-getv-port-layer.patch` via
  `tools/fetch-thirdparty.sh regen`; `verify` reports 15/15. Rebuilt with
  `getv/build_mac.sh all`: 0 failed. The launcher runs the binary directly
  with the env var, because the `.app` stub does not pass env through.
- Perfect Dark (fgsfdsfgs `32a1cb9`): commit `cd002b3`, ini
  `[Video] Stretch43=1`. In `gfx_start_frame()` the window aspect is
  forced to 4/3 after it is measured, so the game lays out 4:3 (FOV, HUD,
  menus via `videoGetAspect()`) while RATIO_X/RATIO_Y (`gfx_pc.cpp:52-53`)
  still scale to the real window. Built against the release's bundled
  `SDL2.framework` using `-DCMAKE_FRAMEWORK_PATH`, so no sudo or
  `/Library/Frameworks` install was needed. The installed binary's original
  is kept as `pd.arm64.orig-ci`.
- Dab's Mod (v3.14.0 `90c8622`): commit `379b3ca`, the same patch, ini key
  and anchors (`gfx_pc.cpp:8577`). Vulkan was not found, so it built the
  OpenGL renderer; the release binary links the same libraries (OpenGL,
  curl, zlib, SDL2). The original is kept as `pd.arm64.orig-v3.14.0`.
- pd.ini location: vanilla PD reads `./pd.ini` when it exists
  (`fs.c:155-158`), otherwise `~/Library/Application Support/perfectdark`.
  Dab's Mod prefers the exe folder when it is writable. Both now have their
  own `pd.ini` in their folders, so they do not share settings. Vanilla's
  was seeded from the Application Support copy (first run 13:44).
- Fullscreen: Alt+Enter in PD and Dab's (`gfx_sdl2.cpp:296`), F11 in
  GoldenEye.

## Controllers (2026-10-17, M1)
- The two USB N64-style pads are clones that report as Nintendo Switch Pro
  (`057e:2009`), both with serial `000000000001`. macOS System Settings
  shows only one, but SDL 2.30.9 enumerates both, at separate paths, and both
  send every input (`tools/padtest`, log in
  `~/PsymaticArcade-Apps/logs/padtest.log`).
- SDL mapping, identical on both: A=`a`, B=`b`, Z=`lefttrigger`, Start=`start`,
  L=`leftshoulder`, R=`rightshoulder`, C-buttons=right stick
  (`righty-` up, `rightx-` left), D-pad=`dp*`, stick=left stick. No
  x/y/rt/back exist on these pads.
- SpaghettiKart: gives every pad to port 1 and makes ports 2-4 ignore all of
  them (libultraship `ConnectedPhysicalDeviceManager.cpp:103-105`). Fixed by
  hand in Esc > Settings > Controller: untick pad 2 on Port 1, tick it on
  Port 2, then Set defaults > Gamepad (SDL). The user confirmed it works.
  The ignore list is in memory only, so expect to redo the ticks each launch.
- GoldenEye Native: its `modern` preset puts fire on `rt`, next weapon on `y`
  and reload on `x`, none of which exist on these pads. That is why weapon
  switching failed. Its default `controls = 2.2` also makes a second
  physical pad drive player 1's second N64 port (`port_os.c:336-338`). Set
  `controls = 1.1` plus explicit 1.1 Honey bindings in
  `~/Library/Application Support/Goldeneye-Native/goldeneye.cfg`. Not yet
  played with these settings.
- GoldenEye MP crash on Library/Basement/Stack (stage 48/45/46): FIXED.
  Root cause is upstream in the decomp (n64decomp/007 `c435646`):
  `assets/obseg/file_resource_table.inc.c:33` maps `"bg/bg_ame_all_p.seg"` to
  `&bg_imp_all_p_seg`, an empty cut level. `gePortObsegSize()` returns 0
  for it, so `obLoadBGFileBytesAtOffset()` (`ob.c:160`) copies nothing, and
  `load_bg_file()` parses an uninitialised stack header. That gives a
  random size per run: either the misleading "cut during development" exit
  or SIGBUS. The port's stretch patch was not involved; the first
  successful test must have used another arena. Fixed by pointing the
  entry at `&bg_ame_all_p_seg`, recorded as
  `getv/patches/0033-library-basement-stack-bg.patch` (commit `78ff8c2`).
  Verified headless with `GETV_STAGE=45|46|48 GETV_MP=2 GETV_EXIT_FRAME=240`:
  size 8928 and exit 0 for all three. The same table also maps ELD, ASH and
  LUE to `bg_imp`, but those are cut levels.
- GoldenEye MP freeze on weapon cycle: FIXED, pending a playtest. The game
  froze at 100% CPU (not a crash) during 2P on Basement. `sample` and
  `lldb -p` on the live process showed the main thread stuck in
  `bondinvCycleForward` via `advance_through_inventory`, walking a ring of
  two free (`type -1`) InvItems that point at each other and never reach
  `ptr_inventory_first_in_cycle`. Root cause is upstream in the decomp:
  `src/game/inititemslots.c:19` allocates `equipmaxitems * 0x14`, the N64
  `sizeof(InvItem)`. Natively the struct is 32 bytes (`next`/`prev` are
  8-byte pointers, `bondview.h:271-284`), so each player's array overruns
  into the next stage-pool allocation, which in MP is the next player's
  inventory. Fixed with `sizeof(InvItem)` under `GE_PORT_NATIVE`, recorded
  as `getv/patches/0034-invitem-native-size.patch` (commit `87b5fa6`). A
  headless 4P Basement run for 600 frames exits cleanly, but weapon cycling
  itself can only be tested by hand.
- Headless repro recipe: `GETV_STAGE=<id> GETV_MP=2 GETV_EXIT_FRAME=240
  perl -e 'alarm 60; exec @ARGV' getv/build-mac/goldeneye` (macOS has no
  `timeout`). Level IDs are in `vendor/ge-decomp/src/bondconstants.h:1744`.
- Pad drift (both pads, same values): `tools/padmon` and `tools/padrest`.
  With SDL's HIDAPI Switch driver the clones rest at lx 1614, ly 45 (fine),
  but the C-button "right stick" rests at rx **+8478** and ry **-8054**, or
  **+4398** after a C-up press. That is the Pro calibration applied to
  digital buttons. GoldenEye's C hysteresis is on 12000 / off 8000
  (`port_os.c:662`), so C-right and C-up latch on after one press: the
  view drifts right or stares at the ceiling. Other SDL backends are worse
  (`SDL_JOYSTICK_HIDAPI_SWITCH=0` with MFI shows 0 pads; IOKit decodes
  ly=-32768 and lt stuck on). Fix: GE commit `81a9895`
  makes the thresholds overridable, and goldeneye.cfg sets
  `GETV_C_ON = 24000`, `GETV_C_OFF = 16000`. Verified loaded. Not yet
  playtested. Perfect Dark and GE-X read the same SDL values, so check them.
- GoldenEye mouse look was on and captured during play; set `mouse = 0`.
- Drift, real root cause: SDL 2.30.9 bug. `SDL_hidapi_switch.c`
  `ApplyStickCalibration()` (around :966) remaps each axis linearly over the
  widest travel seen so far (`m_StickExtents` grows on every new extreme).
  On an axis with uneven travel the rest point maps off centre, and it moves
  as new extremes arrive: drift that changes direction during play and in
  menus, on sticks and C-buttons alike. SDL 2.32.10 (release-2.32.10,
  2025-09-01) remaps each side of centre separately. Measured at rest:
  2.30.9 gives lx 1614, rx 8478, ry -8054; 2.32.10 gives lx 0, ly -1,
  rx 2551, ry -3659, all inside the 20% deadzone. The plain HID backend
  (`SDL_JOYSTICK_HIDAPI=0`) is unusable: no handshake, so buttons read held
  and the hat stuck.
  - PD and Dab's Mod: `SDL2.framework` swapped for the official 2.32.10 dmg
    framework (dmg SHA-256 `4a7ac316...1a7f`); originals kept as
    `SDL2.framework.orig-2.30.9`. Their binaries are unchanged (`@rpath`
    link).
  - GoldenEye: `GETV_SDL_SRC` override in `build_mac.sh` (commit `8e0d654`).
    SDL 2.32.10 was rebuilt into `~/.n64tvos/sdl2-mac`; the old prefix is
    kept as `sdl2-mac.orig-2.30.9`. The stale `~/.n64tvos/build-sdl2-mac`
    cache had to be deleted first. The binary embeds
    `SDL-release-2.32.10`. A headless 2P run saw both pads.
  - SpaghettiKart links SDL statically and was left on 2.30.9; the user
    reports it plays fine.
  - The `GETV_C_ON/OFF` thresholds (24000/16000) stay as a safety margin.
- PD / Dab's Mod display: there was no option to choose a display; the
  window opens on the main display (`gfx_sdl2.cpp:111`
  `SDL_WINDOWPOS_UNDEFINED`), and dragging it to the CRT disrupted the
  pads. Added `Video.Display=<SDL index>` to both forks (default -1,
  unchanged), which creates the window centred on that display. SDL order
  on the M1 (`tools/displays`): 0 = built-in 1440x900, 1 = external
  1280x720 @ 60. Both pd.ini files now have `Display=1` and
  `DefaultFullscreen=1`.
- Dab's Mod self-updater (`port/src/update.c`, `updatemenu.c`): a local
  build follows the rolling `dabs-mod-dev` prerelease and, once accepted,
  swaps in the downloaded binary on the next start. That happened here:
  pd.ini had `UpdateLastBuild=3ee8ed0-dev` (upstream 2026-10-14) and had
  lost `Stretch43`, because our patched binary had been replaced. Fixed
  with `Mod.UpdateNotice=0` and `--no-update-notice` in the launcher, and
  our build reinstalled. Watch for this whenever Dab's Mod settings seem
  to vanish.
- Dab's Mod menus differ by version. The README fetched from the `dabs-mod`
  branch head describes a "Perfect Dark Mods" main-menu entry and a
  GoldenEye option. Those exist only in newer dev builds (the user saw them
  in `3ee8ed0-dev`). In v3.14.0, mods load from Options > Extended Options >
  Load Mods (then Restart Now), and the GoldenEye ROM content is named
  "GE Plus" (v3.14.0 README.md:261, :297-300). The GE-X launcher now
  passes `--moddir "mods/GE-X_6a_01-19-25"` to boot straight into GE-X.
  Lesson: read the README that ships in the release tarball, not the
  branch head.

## PD / GE-X control style (2026-10-18)

`Game.PlayerN.ExtendedControls=1` in pd.ini forces `CONTROLMODE_PC` at
every profile load (`src/game/mplayer/mplayer.c:440`, `:3522`;
`src/game/gamefile.c:170`, `:345`), overriding the in-game style. On our
N64 pads that reads as "C buttons move, stick looks", and Combat Sim /
Virtual Reality has no menu to change it. Set to 0 for all four players
in both pd.ini files; mode then defaults to 1.1 (`mplayer.c:438`).
`tools/pads/pd_n64pads.py` now does this too. Not yet playtested.
