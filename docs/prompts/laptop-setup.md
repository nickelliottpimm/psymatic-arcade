# Prompt: laptop setup (M1 MacBook Pro)

Paste the block below into Claude Code, from inside the repo folder.

```
Read CLAUDE.md and docs/status.md first. Rules in CLAUDE.md apply. This session is
laptop setup: M1 MacBook Pro, macOS Sequoia 15.7.3. I want to test in a few hours, so
get something playable fast, then set things up properly.

ROM source: the share at smb://Beaird01._smb._tcp.local/01_PRODUCTION/01_PROJECTS/
Psymatic2000/04_Gaming/2026_PsymaticArcade/ROMs
- Check /Volumes for it already mounted. If not, tell me to connect in Finder (Cmd+K).
  Never ask for or enter credentials.
- Copy the ROMs to ~/QuadTubeROMs (local disk, OUTSIDE the repo). Build trees also go
  on local disk, never on the share.
- FIRST, before anything else: confirm .gitignore excludes *.z64 *.n64 *.v64 *.rom
  roms/ and is committed. Never put a ROM in git.
- List what is in the folder and identify each ROM by SHA1 and region. Report which of
  these I have, and what is missing or the wrong version/format:
  Mario Kart 64 (US, .z64), GoldenEye 007 (US, .z64), Perfect Dark (NTSC v1.1, for
  GoldenEye X). Convert byte order only if a port requires it.

PHASE 1 (quick win, time-box ~30 min): vanilla SpaghettiKart running.
- Check the HarbourMasters/SpaghettiKart releases for a macOS build. If one exists for
  Apple Silicon, use it with my MK64 ROM and get to a playable race. Report the exact
  version and any Gatekeeper steps. Don't bypass anything without telling me.
- Record in docs/findings.md: version, license (note whether a license file exists),
  last commit date, and anything that broke.

PHASE 2 (proper setup, ask before touching more than a couple of files):
- Fork-and-submodule plan for SpaghettiKart under ports/. Propose the steps and wait
  for my yes before forking or pushing anything.
- Audit the GoldenEye port jkdansereau/goldeneye-pc-port. Its release has no macOS or
  ARM build, so try building from source on this Mac. Report: license, last commit,
  build result on arm64, whether 2-4 player split-screen runs. Also check whether the
  project behind the "GoldenEye Native" release (Windows/Linux/macOS) is findable and
  has a Mac build. Do not use the Xbox 360 recomp. Do not use the archived akratch/mgb64.
- Do not set up Perfect Dark / GoldenEye X yet. Just report whether the Perfect Dark
  PC port has a macOS build.

Output rules: file:line or exact command output for findings, not impressions. If a
build fails twice, stop, record it in docs/dead-ends.md with the error, and move on.
If a step needs me to look at the screen, tell me exactly what to look for.
Before ending: update docs/status.md (done, blocked, next) and commit. No ROMs staged.
```
