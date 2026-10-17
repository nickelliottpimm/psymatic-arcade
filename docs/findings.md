# Findings

Verified numbers and file:line refs go here. Anything under "Unverified leads"
came from web research in the chat thread on 2026-10-17 and has NOT been
confirmed by building or running. Code thread: verify, then move items up.

## Verified

(none yet)

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
