# CLAUDE.md — Psymatic Arcade

Read this and `docs/status.md` at the start of every session.

## Project

N64 game suite for a 4-CRT video wall (2x2 splitter, 16:9 in, four 4:3
tubes out). First target: Mario Kart 64 with a quadrant menu mirror and
4 humans + 4 AI in Grand Prix. Then GoldenEye, Perfect Dark, Lylat Wars,
then a launcher UI. Full brief: `docs/project-instructions.md`.

## Output geometry

Every quadrant is a 4:3 image stretched horizontally by 4/3 to 16:9. The
modulators squeeze it back. Menus: one image tiled four times. 4P race:
native 4:3 frame stretched to full output.

## Repo layout

```
CLAUDE.md
docs/
  project-instructions.md   # same text as the Claude Project
  status.md                 # updated at end of every Code session
  playtest-notes.md         # vanilla observations
  findings.md               # verified numbers, file:line refs
  dead-ends.md              # what failed and why
  decisions/                # 0001-short-title.md, one per decision
  prompts/                  # reusable Code-thread prompts
ports/                      # git submodules pointing at our forks (no ROMs)
layout/                     # shared quadrant/present layer, if split out
tools/                      # build and run scripts
assets/                     # non-ROM only
.gitignore                  # must exclude *.z64 *.n64 *.v64 *.rom roms/
```

## Rules

- No ROMs in git. Ever. Check `.gitignore` before the first commit.
- Audit before code. Report file:line, then wait.
- Small increments. Ask before touching more than a couple of files.
- Runtime toggle for every behavior change, default off.
- Submodule changes live in our forks, committed and pushed there, then the
  pointer is bumped here. `git submodule update` wipes uncommitted changes.
- Build trees go on local disk, not on a network share.
- Update `docs/status.md` and commit before ending a session.

## Verified findings

(none yet. Unverified research leads are in `docs/findings.md`; nothing
there counts as verified until a build or run confirms it.)
