---
title: Build Options
description: CMake options for configuring AmityEngine.
---

Pass options to the configure step:

```bash
cmake --preset windows -DAMITY_ENABLE_LUA=ON
```

| Option | Default | Description |
|--------|---------|-------------|
| `AMITY_ENABLE_LUA` | `OFF` | Build `LuaScriptService` |
| `AMITY_BUILD_TESTS` | `ON` | Build the GoogleTest unit tests |
| `AMITY_BUILD_DEMOS` | `ON` | Build the demo games (Amity test game, PanTiltShowcase, StormySails) |
| `AMITY_BUILD_PRIVATE_GAMES` | `ON` | Build games in `src/games/PrivateGames` if present |

## Targets

| Target | Description |
|---|---|
| `AmityTests` | Unit test runner (CTest) |
| `Amity` | Engine test game |
| `StormySails` | Ocean sailing demo with volumetric clouds |
| `PanTiltShowcase` | Pan/tilt surveillance turret demo |
| `Minecraft` | Voxel sandbox |
