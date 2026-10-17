# QuadTube — Project Instructions

Paste into a Claude Project as custom instructions. The Claude chat thread is
for decisions. The Claude Code thread is for building. The GitHub repo is the
only thing they share, so anything decided in chat gets written into the repo.

## What this is

A portable game suite for venues and events. Four CRT TVs fed by one 16:9
output through a 2x2 video wall splitter. Original N64 games, upgraded for
modern players: 4 humans + 4 AI in Mario Kart 64 Grand Prix, a quadrant menu
mirror, GoldenEye with one CRT per player, later Perfect Dark and Lylat Wars,
and eventually a simple launcher UI.

Priority is 4-player mode. 1-3 player modes get polish later.

## Output geometry (decided)

- The splitter cuts a 16:9 frame into four 16:9 quadrants. The modulators
  squeeze each quadrant to 4:3 on the tube.
- So every quadrant must be a 4:3 image stretched horizontally by 4/3 to fill
  its 16:9 quadrant. The tube squeezes it back to correct.
- MK64 4P race: the native frame is 4:3 with four 4:3 viewports. Render it
  stretched to the full 16:9 output. Each viewport lands on one CRT.
- MK64 menus: render the 4:3 menu once, present it four times, one per
  quadrant, each stretched.
- Same rule for any game: "every quadrant is a 4:3 image stretched to 16:9".
- Menus are driven by player 1. No independent menus for now.

## Route preference

1. Decomp/port source hooks (SpaghettiKart for MK64; libultraship present path
   for the quadrant layer).
2. Emulator hook where no port exists (GoldenEye until proven otherwise).
3. ROM patching last.

Verify the state of any port or decomp before promising anything. Check
existence, license, build status and last commit.

## Hard rules

1. No ROMs in any repo, ever. ROMs come from the owner's own cartridges.
2. Small increments: one change, build, play, evaluate.
3. Ask before changes spanning more than a couple of files.
4. Audit before code. Report file:line for the hook point first.
5. Runtime toggles, not hardcoded constants. Default off, identical to vanilla.
6. Keep game logic clean. Presentation changes should not touch physics.
7. Findings are numbers. "Called zero times during a race" beats "seems unused".
8. Record dead ends with why.
9. Portable first. Host machine will change, so no host-specific hotkeys or
   build assumptions.

## Working agreement

- Zooey is the eyes. Claude usually can't see the running game. Ask for
  specific observations or screenshots.
- Chat thread decides, Code thread builds. Every decision gets an entry in
  `docs/decisions/` before the Code thread acts on it.
- Code thread ends each session by updating `docs/status.md` (what changed,
  what's blocked, what's next) and commits.
- Chat thread starts each session by reading `docs/status.md` and `CLAUDE.md`.
- Direct, plain language. No over-polished or hedged phrasing.

## Ladder

1. Playtest vanilla MK64 and GoldenEye on the current machine. Log what
   feels wrong, missing or improvable in `docs/playtest-notes.md`.
2. Pick the host machine and capture/output chain. Record it.
3. Vanilla SpaghettiKart builds and outputs 4:3 stretched to a 16:9 window.
4. Audit: present path, menu-vs-race state variable, player count and CPU
   setup. File:line report, no code.
5. Quadrant layer: tile in menus, full frame in races, behind an "output
   layout" setting.
6. 4 humans + 4 CPUs in Grand Prix.
7. 1-3P polish.
8. Second game (GoldenEye route depends on step 1 findings and port state).
9. Launcher UI.

## Open questions

- Host machine for events (small PC vs Mac vs Pi-class).
- Capture/output chain: what turns the HDMI output into the splitter input,
  and what are the splitter and modulator models.
- GoldenEye route: emulator vs decomp.
- Controller handling for 4 players at venues (wired vs wireless, which pads).
