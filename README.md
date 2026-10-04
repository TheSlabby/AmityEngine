# AmityEngine

A lightweight 3D game engine written in C++23 with OpenGL

![CI](https://github.com/TheSlabby/AmityEngine/actions/workflows/cmake-tests.yml/badge.svg)
[![Docs](https://img.shields.io/badge/docs-theslabby.github.io%2FAmityEngine-16a34a)](https://theslabby.github.io/AmityEngine/)

📖 **[Read the documentation →](https://theslabby.github.io/AmityEngine/)**

---

## Screenshots
<img width="2622" height="1127" alt="image" src="https://github.com/user-attachments/assets/a67f2ee7-0f2a-4966-8f13-c2241852e797" />
<img width="1562" height="1168" alt="image" src="https://github.com/user-attachments/assets/2e27295f-e0de-4e42-8c19-ec5798953cd4" />
<img width="2298" height="963" alt="image" src="https://github.com/user-attachments/assets/daf137b3-3d90-4df3-b485-cdd28425b729" />



---

## Engine Features/Architecture

- **Actor-Component Model** — OOP-style `Entity`, `Component`, and `Scene`
- **3D Model Loading** — Assimp for 3D model loading
- **Terrain Generation** — Simple terrain with diffuse lighting
- **Water Rendering** — Real-time animated ocean surface via fragment shader
- **Spatial Audio** — Using OpenAL
- **Font Rendering** — Font bitmap for font rendering
- **UI System** — Very simple UI system (panels, text)
- **Lua Scripting** — Embedded LUA (still very early)
- **Pan/Tilt Camera** — For azimuth/elevation camera pointing
- **Simple Shader Pipeline**
- **Resource Caching** — With singleton `ResourceManager`

---


## Example Code Snippets

```cpp

// 1. Create scene
auto scene = std::make_shared<Core::Scene>();

// 2. Use ResourceManager to load shaders & models
auto shader = Core::ResourceManager::GetShader("main_shader", "vert.glsl", "frag.glsl");
auto model  = Core::ResourceManager::GetModel("assets/models/ship.obj", 1.0f, 1.0f, shader);

// 3. Create Entity & move it
auto entity = std::make_shared<Core::Entity>();
entity->setName("PirateShip");
entity->setPosition(glm::vec3(0.0f, 5.0f, -10.0f));
entity->setScale(glm::vec3(2.5f));

// 4. Add a component to the entity
// Components basically add behavior to an entity
entity->addComponent<Core::MeshComponent>(model, shader);

// 5. Add entity to the scene (so it can be rendered and interacted with)
scene->addEntity(entity);
```

---



## Building

Dependencies (GLFW, GLM, Assimp, OpenAL, libsndfile, plus GoogleTest and Lua when enabled) are installed automatically by [vcpkg](https://vcpkg.io) from `vcpkg.json`.

**One-time setup:** install vcpkg and set `VCPKG_ROOT` to its folder:

```bash
git clone https://github.com/microsoft/vcpkg
./vcpkg/bootstrap-vcpkg.bat        # or bootstrap-vcpkg.sh on Linux/macOS
# then set the VCPKG_ROOT environment variable to that vcpkg folder
```

**Configure and build** (Windows, Visual Studio 2022):

```bash
cmake --preset windows
cmake --build build/windows --config Release
cmake --build build/windows --config Debug --target Minecraft   # build a single target
```

The first configure builds every dependency, which takes a while; later configures reuse vcpkg's cache.

**Options** (pass to the configure step, e.g. `cmake --preset windows -DAMITY_ENABLE_LUA=ON`):

| Option | Default | Description |
|--------|---------|-------------|
| `AMITY_ENABLE_LUA` | `OFF` | Build LuaScriptService |
| `AMITY_BUILD_TESTS` | `ON` | Build unit tests |
| `AMITY_BUILD_DEMOS` | `ON` | Build demo games (Amity test game, PanTiltShowcase, StormySails) |
| `AMITY_BUILD_PRIVATE_GAMES` | `ON` | Build games in `src/games/PrivateGames` if present |

If vcpkg ever seems to ignore `vcpkg.json`, reconfigure with `--fresh`.

**Run tests:**

```bash
ctest --test-dir build/windows -C Debug --output-on-failure
```

---

## Shader References

| Shader | Source |
|--------|--------|
| Water Fragment (`waterFrag.glsl`) | [Shadertoy — MdXyzX](https://www.shadertoy.com/view/MdXyzX) |
| Volumetric Clouds (`postprocessFrag.glsl`) | [Shadertoy — XtBXDw](https://www.shadertoy.com/view/XtBXDw) by valentingalea |
