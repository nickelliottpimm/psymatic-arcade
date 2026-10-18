# Status

Last updated: 2026-10-18 (Code session on the M1 laptop: setup, patches, playtests)

## Done

- ROMs: copied from the share to `~/PsymaticArcade-ROMs`. MK64 US, GE US
  and PD NTSC v1.1 are all `.z64` and all match the reference hashes. The
  share path is `/Volumes/01_PRODUCTION/01_PROJECTS/Psymatic2000/...`, not
  the one in the prompt.
- All four games are installed under `~/PsymaticArcade-Apps` and launched
  from `~/Desktop/Psymatic Arcade/*.command`. Copies of the launchers are
  in `tools/launchers/`. `0 Claude (this project).command` reopens this
  conversation.
  - **Mario Kart 64** (SpaghettiKart 1.0.0 arm64): plays. 2 pads work after
    assigning pad 2 to Port 2 in Esc > Settings > Controller. The 4:3 to
    16:9 stretch is done by config (`IgnoreAspectCorrection`), and the user
    confirmed it on the wall.
  - **GoldenEye** (seb-patron/goldeneye-native, built from source): plays
    2P on the wall, and the user reports it working well. Local branch
    `psymatic/stretch43` has the stretch toggle, two upstream bug fixes
    (Library/Basement/Stack crash, MP weapon-cycle hang), C-button
    thresholds, and an SDL 2.32.10 build.
  - **Perfect Dark** (fgsfdsfgs port, built from source) and **GoldenEye X**
    (Dab's Mod v3.14.0, built from source, GE-X 6a imported): both open
    fullscreen on the CRT (`Video.Display=1`) with `Video.Stretch43=1`. GE-X
    boots straight into the mod via `--moddir`. Dab's built-in updater is
    disabled because it had replaced our binary.
- Pad drift: root cause was an SDL 2.30.9 calibration bug. GoldenEye, PD
  and Dab's Mod now use SDL 2.32.10. Details in `docs/findings.md`
  ("Controllers").
- All port changes are exported to `ports/pending-patches/` (9 commits).
  Pad and display diagnostic tools are in `tools/pads/`. Upstream bug
  report drafts are in `docs/upstream-drafts/`.

## Blocked / unknown

- No forks or submodules yet. This needs `gh` installed and logged in by
  the user, plus their choice of GitHub account. Until then the patches
  live in local clones and `ports/pending-patches/`.
- SpaghettiKart still has no license. Do not fork until that is resolved.
- GE-X Virtual Reality runs with 4 players and the N64 pad layout plus
  control style 1.1 (`ExtendedControls=0`). Plain Perfect Dark with the
  same layout is not yet playtested.
- SpaghettiKart's per-port pad assignment resets each launch (libultraship
  keeps the ignore list in memory only).
- goldeneye-pc-port was not attempted (GoldenEye Native works). Decision
  0002 needs revisiting.

## Next

1. Playtest plain Perfect Dark 2P with the new pad layout and style 1.1.
2. Install `gh`, log in, choose the account, then fork the three ports,
   push `psymatic/stretch43`, and add them as submodules under `ports/`.
3. Decide whether to post the upstream drafts.
4. Write playtest observations into `docs/playtest-notes.md`.
5. Then: the quadrant menu mirror and the 4P layout work from the brief.

## Ideas from the user (2026-10-18), not started

- Pad re-pair changes player number. Likely cause: both pads report the
  same VID/PID/serial, so on reconnect a game can only order them by
  connection time. Lead to audit: the HID device path encodes the USB
  port, which could pin pad N to the physical socket N. Also check
  whether the pads' sleep timer can be held off by host output reports.
- Mario Kart 64: early experiment, 4 humans + AI opponents in Grand Prix
  (already the brief's first target).
- Exhibition launcher: first choice is number of players, then jump
  straight to each game's character select, skipping title menus. Quit
  back to the launcher with one button combo.
- GoldenEye X is the preferred GoldenEye; Native stays for purists.
