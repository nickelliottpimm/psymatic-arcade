# 0003 Raspberry Pi as an event host

Date: 2026-11-08
Status: proposed. Hardware known; remaining answers in `docs/handover/pi-handover.md` section 8.

## Decision

Start a separate Pi setup effort, briefed by `docs/handover/pi-handover.md`.
Mario Kart 64 goes first. The other games follow only if the Pi measures well.

## Hardware (confirmed 2026-11-08)

Raspberry Pi 4 Model B, 4 GB, bare board, dual micro-HDMI. Cooling, power
supply and storage are still open.

## Why

Decision 0001 already named a Pi as the target for lighter builds. All four
games now run on the M1 laptop, so the Mac is a working reference to compare
the Pi against.

## Known risks

- No performance numbers for any of these ports on any Pi.
- Perfect Dark and Dab's Mod list no Linux arm64 release.
- GoldenEye Native lists Linux arm64 but says nobody has played a mission on
  Linux.
- Controller behaviour (SDL version, pad order) is unverified on Linux.

## Revisit when

MK64 4P frame rate and temperature are measured on the chosen Pi.
