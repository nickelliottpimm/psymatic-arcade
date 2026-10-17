#!/bin/bash
# Psymatic Arcade launcher. Close this window to quit the game.
# GETV_STRETCH43=1: 4:3 image stretched to fill a 16:9 output (Psymatic patch).
# Output is also saved to ~/PsymaticArcade-Apps/logs/ for debugging.
LOG="$HOME/PsymaticArcade-Apps/logs/goldeneye-$(date +%Y%m%d-%H%M%S).log"
cd "$HOME/PsymaticArcade-Apps/goldeneye-native" && GETV_STRETCH43=1 getv/build-mac/goldeneye --launcher 2>&1 | tee "$LOG"
