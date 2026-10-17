# Prompt: laptop setup (M1 MacBook Pro)

Open Claude Code inside `~/Developer/psymatic-arcade` and paste the block below.

```
Read CLAUDE.md and docs/status.md first. This session: get Psymatic Arcade running on
this MacBook (M1, macOS Sequoia). I want to test in a few hours, so get one game
playable fast, then do the rest properly. Work in small steps and tell me plainly what
you are doing.

STEP 1: ROMs
- The ROM share should be mounted under /Volumes (look for 01_PRODUCTION, path
  Psymatic2000/04_Gaming/2026_PsymaticArcade/ROMs). If it is not mounted, tell me to
  connect in Finder (Cmd+K) and wait. Never ask for or type passwords.
- Copy the ROMs to ~/PsymaticArcade-ROMs. That folder is outside the repo on purpose.
- Before anything else, check .gitignore excludes ROMs. Never commit a ROM.
- Tell me which of these I have: Mario Kart 64 (US), GoldenEye 007 (US), Perfect Dark
  (NTSC v1.1). Identify each by SHA1 and region. Say what is missing or the wrong format.

STEP 2: Mario Kart 64 (do this first, about 30 minutes max)
- Get vanilla SpaghettiKart running. Check the HarbourMasters/SpaghettiKart releases
  for a macOS Apple Silicon build and use it if there is one. If macOS blocks the app,
  tell me the exact steps and let me do them.
- Write down in docs/findings.md: version, whether the repo has a LICENSE file, last
  commit date, and anything that broke.
- Then tell me what to look for on screen.

STEP 3: GoldenEye (after Step 2 works)
- Look at jkdansereau/goldeneye-pc-port. The release has no Mac build, so try building
  it from source. Report: license, last commit, whether it builds on Apple Silicon,
  and whether 2 to 4 player split-screen runs.
- Also try to find the repo behind the "GoldenEye Native" release and say whether it
  has a Mac build.
- Do not use the Xbox 360 recomp or the archived akratch/mgb64.
- Do not set up Perfect Dark yet. Just tell me if the Perfect Dark PC port has a Mac build.

RULES
- Ask me before forking, pushing to anyone else's repo, or changing more than a couple
  of files.
- Report exact error text and command output, not impressions.
- If a build fails twice, stop, write it in docs/dead-ends.md, and move on.
- At the end, update docs/status.md (done, blocked, next) and commit. No ROMs staged.
```
