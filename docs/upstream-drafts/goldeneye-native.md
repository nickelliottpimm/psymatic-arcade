# Upstream report drafts: seb-patron/goldeneye-native

Drafted 2026-10-17. Not posted. Post only with the user's go-ahead, from
the user's account, once our fork exists so the fix can be linked as a PR.
Verified on an M1 MacBook Pro, macOS 15.7.3, at `0a6572e`.

---

## 1. Library, Basement and Stack crash or exit on load

**Symptom.** Starting a multiplayer match on Library, Basement or Stack
either exits with

```
[getv] stage 45 has an implausible background size: 4035120 bytes from 'bg/bg_ame_all_p.seg'.
... This stage id was cut during development and cannot be loaded.
```

or crashes with SIGBUS in `load_bg_file+1148`. The reported size differs
on every run.

**Repro.** `GETV_STAGE=45 GETV_MP=2 GETV_EXIT_FRAME=240 getv/build-mac/goldeneye`
(stage 46 or 48 also reproduce it).

**Cause.** `assets/obseg/file_resource_table.inc.c:33` in the decomp maps
`"bg/bg_ame_all_p.seg"` to `&bg_imp_all_p_seg`, which is an empty cut
level. `gePortObsegSize()` returns 0 for that address, so
`obLoadBGFileBytesAtOffset()` copies nothing, and `load_bg_file()` parses
its uninitialised `header[0x10]` stack buffer. On the N64 the pointer was
only a ROM marker, so the typo was harmless there.

**Fix.** Point the entry at `&bg_ame_all_p_seg`, as a new patch
`getv/patches/0033-library-basement-stack-bg.patch`. With the fix, all
three stages read size 8928 and run cleanly. The same table also maps ELD,
ASH and LUE to `bg_imp`; those are cut levels, so they were left alone.

The typo is also in n64decomp/007 at `c435646`, so it is worth reporting
there too.

---

## 2. Multiplayer freezes (100% CPU) when cycling weapons

**Symptom.** In 2P multiplayer, pressing next-weapon hangs the game. The
window stays open and the log stops.

**Evidence.** `sample` on the hung process shows the main thread in
`bondinvCycleForward` <- `advance_through_inventory` <- `bondviewProcessInput`.
Reading memory with lldb showed the item being walked is in a ring of two
free (`type == -1`) InvItems that point at each other and never reach
`ptr_inventory_first_in_cycle`.

**Cause.** `src/game/inititemslots.c:19` allocates
`equipmaxitems * 0x14` bytes, the N64 `sizeof(InvItem)`. Natively
`next`/`prev` are 8-byte pointers and the struct is 32 bytes
(`bondview.h:271-284`), so each player's array overruns into the next
`MEMPOOL_STAGE` allocation. In multiplayer that is the next player's
inventory, and the item rings get cross-linked.

**Fix.** Use `sizeof(InvItem)` under `GE_PORT_NATIVE`, as a new patch
`getv/patches/0034-invitem-native-size.patch`. With the fix, the user
reports 2P play with weapon cycling working.

It may be worth checking other `mempAllocBytesInBank(n * 0x..)` sizes for
the same 32-bit struct size problem.

---

## 3. Suggestion: build SDL 2.32.x instead of 2.30.9

SDL 2.30.9's HIDAPI Switch driver (`ApplyStickCalibration`, around
`SDL_hidapi_switch.c:966`) maps each axis linearly over the widest travel
seen so far. Pads with uneven travel therefore rest off centre, and the
offset shifts during play. With third-party "Switch Pro" pads (for example
N64-style USB pads) this shows up as view drift that changes direction,
including in menus. SDL 2.32.10 calibrates each side of centre separately.
Measured at rest on two pads: 2.30.9 gave rx 8478 / ry -8054; 2.32.10 gave
rx 2551 / ry -3659 and sticks at 0.

The C-button thresholds (`GE_C_ON 12000` / `GE_C_OFF 8000`,
`port_os.c:662`) are also tight for such pads. Our fork makes them
overridable with `GETV_C_ON` / `GETV_C_OFF`.
