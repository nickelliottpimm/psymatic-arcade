# 0002 GoldenEye candidate order

Date: 2026-10-17
Status: provisional, pending the audit in `docs/prompts/laptop-setup.md`

## Decision

Multiplayer (2-4P split-screen) is required for GoldenEye. Evaluate in this order:

1. jkdansereau/goldeneye-pc-port, built from source on the M1 laptop (no macOS
   prebuilt exists in v0.5.0).
2. Identify the repo behind "GoldenEye Native" (reported macOS build, 4P).
3. Fallback: Perfect Dark PC port plus GoldenEye X (also needs the PD NTSC v1.1
   ROM).

Excluded: akratch/mgb64 (archived), SunJaycy/GoldenEye-Recomp (Xbox 360 files).

## Why

Decomp/port route is preferred over emulator for long-term modding. The first
two options have reported 4P split-screen. Neither is verified by a build yet.

## Revisit when

The audit reports license, last commit, arm64 build result and whether 4P runs.
