# Prompt: Lylat Wars (Star Fox 64) test on the Mac

Run in Claude Code in `~/Developer/psymatic-arcade`. Time-box about 45 minutes.
See `docs/decisions/0004-lylat-wars-starship.md`.

```
Read CLAUDE.md, docs/status.md and docs/decisions/0004-lylat-wars-starship.md first.

Goal: get Star Fox 64 running on this Mac with HarbourMasters/Starship, stretched
to fill the 16:9 output, and find out whether 4-player versus works. Small steps.
Tell me plainly what you are doing.

1. ROM: it is already at
   /Users/nickelliottpimm/PsymaticArcade-ROMs/Star Fox 64 (USA) (Rev 1).z64
   Do not copy it anywhere. Check the first four bytes are 80 37 12 40 and the
   SHA-1 is 09f0d105f476b00efa5303a3ebc42e60a7753b7a. Report both. Never commit a
   ROM.
2. Check the Starship releases page for a macOS arm64 build. Report the exact
   version and file name. If there is one, install it under
   ~/PsymaticArcade-Apps/starship and use it. If not, tell me before building
   from source.
3. Run it. If macOS blocks it, tell me the exact steps and let me do them.
4. Stretch: set gAdvancedResolution.IgnoreAspectCorrection = 1 (with the
   resolution aspect forced to 4:3), the same as SpaghettiKart. Back up the
   config first. LowResMode overrides it, so keep that off. Tell me what to look
   for on the wall.
5. Pads: check whether two pads, then four, are seen and in what order. Report
   exact names and ports. Do not change code yet.
6. Versus: find out whether 4-player versus can be started with four pads. If it
   cannot, say exactly where it stops (menu, option, crash) with the log line.
7. Record everything in docs/findings.md with exact output. Add a launcher
   to tools/launchers/ named "7 Lylat Wars.command" (same style as the others).
   Update docs/status.md and commit. No ROMs staged.

Ask me before forking Starship or changing more than a couple of files. If a
build fails twice, stop and write it in docs/dead-ends.md.
```
