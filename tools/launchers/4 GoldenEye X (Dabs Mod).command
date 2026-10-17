#!/bin/bash
# Psymatic Arcade launcher. Close this window to quit the game.
# --moddir: boot straight into GoldenEye X (v3.14.0 has no main-menu entry for it).
# --no-update-notice: Dab's Mod's built-in updater would replace our patched
# binary (Stretch43, Video.Display) with the upstream dev build.
cd "$HOME/PsymaticArcade-Apps/pd-dabs-mod/unpacked/pd-dabs-mod-arm64-osx" && exec ./pd.arm64 --no-update-notice --moddir "mods/GE-X_6a_01-19-25"
