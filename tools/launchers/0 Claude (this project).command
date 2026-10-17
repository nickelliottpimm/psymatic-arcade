#!/bin/bash
# Reopens the Psymatic Arcade setup conversation in Claude Code.
# Falls back to the most recent conversation in this project if that one is gone.
cd "$HOME/Developer/psymatic-arcade" || exit 1
"$HOME/.local/bin/claude" --resume 6fd0e379-7b6e-48b6-a54f-b34fb1440f59 || exec "$HOME/.local/bin/claude" --continue
