# AmityEngine

A lightweight 3D game engine written in C++23 with OpenGL

![CI](https://github.com/TheSlabby/AmityEngine/actions/workflows/cmake-tests.yml/badge.svg)

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

**Dependencies**: OpenGL, GLFW, GLM, Assimp, OpenAL, libsndfile

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

**Run tests:**

```bash
cd build && ctest -C Debug --output-on-failure
```

---

## Shader References

| Shader | Source |
|--------|--------|
| Water Fragment (`waterFrag.glsl`) | [Shadertoy — MdXyzX](https://www.shadertoy.com/view/MdXyzX) |
| Volumetric Clouds (`postprocessFrag.glsl`) | [Shadertoy — XtBXDw](https://www.shadertoy.com/view/XtBXDw) by valentingalea |
