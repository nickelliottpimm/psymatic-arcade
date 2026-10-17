# 0001 Host machines and test laptop

Date: 2026-10-17
Status: decided

## Decision

- Test machine for now: M1 MacBook Pro (2020), macOS Sequoia 15.7.3.
- Event host targets over the project's life:
  - Lighter builds (e.g. Mario Kart 64): Raspberry Pi 4 is a candidate. Not
    proven. Verify SpaghettiKart on Pi 4 before relying on it.
  - Heavier builds: M1 Max Mac Studio.
- Output chain: one 1080p or 4K HDMI out into a 2x2 wall splitter, which splits
  into four quadrants, each through its own RF modulator to a CRT.
- Splitter and modulator model numbers: still to record.

## Consequences

- Portable first. No host-specific hotkeys or build assumptions.
- Build trees on local disk.
