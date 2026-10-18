#!/bin/bash
# Build SpaghettiKart 1.0.0 with the Psymatic patches on macOS (arm64).
# SpaghettiKart has no licence, so we keep patches here instead of a fork.
#
# Needs: Xcode command line tools, Homebrew, and an mk64.o2r made from your
# own ROM (copy it from an existing SpaghettiKart install, or let
# Spaghettify make one on first run).
#
# Usage: tools/build-spaghettikart.sh [src_dir] [install_dir]
set -euo pipefail

REPO="$(cd "$(dirname "$0")/.." && pwd)"
SRC="${1:-$HOME/PsymaticArcade-Apps/src/spaghettikart}"
DEST="${2:-$HOME/PsymaticArcade-Apps/spaghettikart-cpu}"

brew install cmake sdl2 libpng glew ninja nlohmann-json libzip vorbis-tools sdl2_net tinyxml2

if [ ! -d "$SRC/.git" ]; then
    git clone --depth 1 --branch 1.0.0 https://github.com/HarbourMasters/SpaghettiKart.git "$SRC"
fi
cd "$SRC"
git submodule update --init --depth 1 libultraship torch
if ! git log --oneline | grep -q "CPU racers"; then
    git -c user.name=Claude -c user.email=noreply@anthropic.com am "$REPO"/ports/pending-patches/spaghettikart/*.patch
fi

cmake -H. -Bbuild-cmake -GNinja -DCMAKE_BUILD_TYPE:STRING=Release
cmake --build build-cmake

mkdir -p "$DEST"
cp build-cmake/Spaghettify "$DEST/"
cp -R build-cmake/yamls build-cmake/meta build-cmake/config.yml "$DEST/"
echo "Built into $DEST. Copy mk64.o2r, spaghetti.o2r and gamecontrollerdb.txt"
echo "from a SpaghettiKart 1.0.0 release folder if they are not there yet."
