# Status

Last updated: 2026-10-17 (Code session, cloud/Linux, research only)

## Done

- Repo bootstrapped: CLAUDE.md, project instructions, docs skeleton, .gitignore
  (excludes ROMs and build trees).
- Chat-thread research logged in `docs/findings.md` (all unverified by build).
- Decision 0001 recorded: host machines and test laptop.
- Decision 0002 recorded: GoldenEye candidate order.
- `laptop-setup.md` was started in a cloud session by mistake. That session
  is Linux with no Mac and no ROM share, so it did the desk research only.
  Results are in `docs/findings.md`, under "Checked from source":
  - SpaghettiKart 1.0.0 ships `spaghetti-mac-arm64.zip`. The repo has no
    LICENSE file. Last commit 2026-10-11.
  - goldeneye-pc-port: MIT. Last commit 2026-10-07. No Mac build, and the
    maintainer says macOS has never been built. 4P is not yet verified
    upstream.
  - "GoldenEye Native" identified: seb-patron/goldeneye-native (the original
    SegfaultEvan repo was deleted). MIT, with Apple Silicon as its primary
    target and 2-4P split-screen marked done. There is no prebuilt; it
    builds from source with a Mac installer script.
  - Perfect Dark port: has a Mac arm64 build (`pd-arm64-osx.tar.xz`). MIT.
  - Reference ROM hashes recorded for MK64 US, GE US and PD NTSC v1.1 (MD5).

## Blocked / unknown

- No build or run has happened yet. Nothing is verified on hardware.
- ROM inventory not done. It needs the laptop and the mounted share.
- SpaghettiKart has no license. This must be resolved before forking.
- goldeneye-pc-port on Apple Silicon: an untested platform upstream.

## Next

1. Run `docs/prompts/laptop-setup.md` in Claude Code on the M1 laptop itself.
   Steps 2 and 3 can skip the research already in `docs/findings.md`.
2. Step 2: use the `spaghetti-mac-arm64.zip` asset from release 1.0.0.
3. Step 3: suggested order on the Mac is seb-patron/goldeneye-native first
   (Mac is its primary target), then a time-boxed attempt at
   goldeneye-pc-port. Pass the ROM with `--rom ~/PsymaticArcade-ROMs/...`.
   Read `tools/install.sh` before running it. Revisit decision 0002 after.
4. Log playtest observations in `docs/playtest-notes.md`.
