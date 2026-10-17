# Pending patches

Our changes to the ports, exported with `git format-patch` from the local
`psymatic/stretch43` branches. They live here until the forks exist
(see CLAUDE.md: changes go into our forks, then a submodule pointer bump).
Apply to a fresh clone at the base commit with `git am <dir>/*.patch`.

| Port | Upstream | Base |
|---|---|---|
| `goldeneye-native/` | seb-patron/goldeneye-native | `0a6572e` |
| `perfect_dark/` | fgsfdsfgs/perfect_dark (branch `port`) | `32a1cb9` |
| `perfect-dark-dabs-mod/` | DabDavis/perfect-dark-dabs-mod | `90c8622` (v3.14.0) |

Every behaviour change is behind a toggle that defaults off, except the
two GoldenEye bug fixes (0002, 0003), which correct upstream bugs.
