# Prompt: Raspberry Pi setup

Use this to start the separate Pi session. Run Claude Code on the Pi, inside
the cloned repo. If you are using a chat thread instead, paste
`docs/handover/pi-handover.md` first, then this.

```
Read CLAUDE.md, docs/status.md and docs/handover/pi-handover.md first.

This session: get Psymatic Arcade running on this Raspberry Pi. Start with
Mario Kart 64 only. Nothing has been built or run on a Pi yet; treat anything
marked UNVERIFIED in the handover as a test, not a fact.

Step 0, before building anything:
- Tell me the Pi model, RAM, OS and version, kernel, Mesa version, and
  `sdl2-config --version`. Record them in docs/findings.md.
- Check .gitignore excludes ROMs. Never commit a ROM.
- Ask me the open questions in handover section 8 that you cannot answer
  yourself. Ask them all at once.

Then follow handover section 7 in order. Small steps. Ask before changes that
touch more than a couple of files. If a build fails twice, stop, write it in
docs/dead-ends.md with the exact error, and tell me.

Measure, do not guess (handover section 9). Report frame rate, temperature and
throttling as numbers. If Mario Kart 64 is not smooth in 4P, stop and report
before touching the other games.

Pi-only scripts go in tools/pi/. Keep shared code portable. End by updating
docs/status.md and committing. No ROMs staged.
```
