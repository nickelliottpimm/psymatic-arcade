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
