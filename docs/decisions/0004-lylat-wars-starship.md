# 0004 Add Lylat Wars (Star Fox 64) via Starship

Date: 2026-11-08
Status: proposed. Not set up.

## Decision

Add Star Fox 64 ("Lylat Wars" in PAL regions) as game 5, using
HarbourMasters/Starship. Try it on the Mac first, time-boxed, in parallel with
the Pi brief. Do not make the Pi work wait for it.

## Facts (read from a shallow clone, 2026-11-08, nothing built)

- License: CC0 1.0 (`LICENSE.md`). Unlike SpaghettiKart, it can be forked.
- Last commit on the default branch: `3322643`, 2026-09-15.
- Same engine family as SpaghettiKart: the Advanced Resolution editor has
  `gAdvancedResolution.IgnoreAspectCorrection`
  (`src/port/ui/ResolutionEditor.cpp:297-308`). The 4:3 stretch that works on
  the wall for Mario Kart is likely to be config-only here too.
- ROM: only the **US** ROM works for building the assets. US 1.0 SHA-1
  `D8B1088520F7C5F81433292A9258C1184AFA1457`, US 1.1 SHA-1
  `09F0D105F476B00EFA5303A3EBC42E60A7753B7A`, in `.z64` format
  (`README.md`, `src/port/extractor/GameExtractor.cpp:13-15`). A PAL "Lylat
  Wars" ROM cannot be the base. EU voices can be swapped in on top of a US ROM.
- macOS: the README says to run `starship` and pick the ROM. I did not check
  the releases page, so whether an arm64 build is published is unverified.
- Graphics: DirectX 11, OpenGL, Metal (`README.md`).
- Linux ARM: CMake has an aarch64 branch (`CMakeLists.txt:569-570`). No Pi
  evidence.
- 4-player versus: the decomp has `src/engine/fox_versus.c`. Whether the port
  plays 4P versus with four pads is UNVERIFIED.

## Open

- Is there a Star Fox 64 US ROM in the share? It was not in the three ROMs
  copied so far.
- 4P versus with four pads, on the wall.
