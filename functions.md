# 📋 River View Computer Graphics

## 🔧 Global Variables & Structures

| Variable | Purpose |
|----------|---------|
| `position1-4`, `speed1-4` | Animation positions for boat, clouds, rain, sun |
| `wingAngle`, `wingSpeed`, `wingDirection` | Bird wing animation control |
| `lightningActive`, `lightningTimer`, `lightningBrightness`, `lightningCooldown` | Lightning effect system |
| `Bird` struct | Stores bird properties (x, y, speed, wingPhase, scale, verticalOffset) |
| `birds[6]` | Array of 6 birds with unique properties |
| `Point` struct | Rain drop data (x, y, r, g, b, a) |
| `points[1000]` | Array of 1000 rain drops |

---

## ⏱️ Timer/Animation Functions

| Function | Description |
|----------|-------------|
| `birdd(int)` | Updates all 6 birds' positions and wing angles at 16ms intervals |
| `sunn(int)` | Animates sun vertical position (100ms) |
| `rain(int)` | Updates rain position + triggers random lightning (100ms) |
| `cloud(int)` | Moves clouds horizontally across sky (100ms) |
| `boat(int timer)` | Animates sailboat horizontal movement (100ms) |

---

## 🌤️ Sky & Weather Functions

| Function | Description |
|----------|-------------|
| `sky()` | Day sky - blue gradient quad |
| `sky2()` | Night sky - dark blue quad |
| `skyRain()` | Storm sky with gradient + lightning bolts with branches and glow effect |
| `drawRainPuddles()` | Draws 3 puddles with animated ripple circles using transparency |

---

## ☁️ Cloud Functions

| Function | Description |
|----------|-------------|
| `cloud1()` | First cloud cluster using overlapping circles |
| `cloud2()` | Second cloud cluster |
| `cloud3()` | Third cloud cluster (used in night scene) |

---

## ☀️🌙 Celestial Bodies

| Function | Description |
|----------|-------------|
| `sun()` | Enhanced sun with outer glow, 12 sunrays, gradient core, highlight spot |
| `moon()` | Crescent moon with glow, shadow overlay, 3 craters, highlight |
| `stars()` | Night sky stars drawn as GL_POINTS |

---

## 🌍 Terrain & Environment

| Function | Description |
|----------|-------------|
| `ground()` | Left side grass area with gradient shading and texture lines |
| `river()` | Water with depth shading, ripple lines, shimmer highlights |
| `backgroundtree()` | Palm trees and forest backdrop elements |

---

## 🏠 Buildings & Structures

| Function | Description |
|----------|-------------|
| `hut()` | Detailed house with wood planks, roof shingles, doors, windows, chimney with smoke |
| `hut1()` | House variant for night scene (outline/wireframe style) |
| `well()` | Water well with brick structure, bucket, rope |
| `well1()` | Well variant for night scene |
| `fence()` | Yellow wooden fence with horizontal and vertical slats |
| `Straw()` | Straw haystack decoration |
| `way()` | Dirt pathway (two connected quads) |

---

## 🌳 Tree Function

| Function | Description |
|----------|-------------|
| `tree()` | Foreground tree with roots, textured bark, branches, multi-layer foliage with highlights, shadow |

---

## ⛵ Boat & Character Functions

| Function | Description |
|----------|-------------|
| `boat()` | Sailboat with water reflection, hull planks, mast, sails, ropes, flag, seats, boatman |
| `boat2()` | Rowboat with fishing pole, line, bobber, anchor rope, fisherman |
| `boat3()` | Simplified boat for night scene |
| `boat4()` | Colored boat variant (black hull, orange body, red/green sails) |
| `drawBoatman(x, y, scale)` | Human figure with hat, face features, shirt, arms, hands, oar, legs, feet |

---

## 🐦 Bird Functions

| Function | Description |
|----------|-------------|
| `drawSingleBird(Bird&)` | Single bird with animated wings, body, head, beak, tail feathers |
| `bird()` | Renders all 6 birds by calling drawSingleBird for each |

---

## 🌿🌸 Grass & Flower Functions

| Function | Description |
|----------|-------------|
| `grass1()` | Grass patch with Red Rose, Orange Daisy, Yellow Sunflower |
| `grass2()` | Grass patch with Pink Tulip, Purple Violet, White Daisy |
| `grass3()` | Grass patch with Red Poppy, Blue Cornflower, Yellow Buttercup |
| `grass4()` | Night version of grass1 (muted/darker colors) |
| `grass5()` | Night version of grass2 (muted/darker colors) |
| `grass6()` | Night version of grass3 (muted/darker colors with moonlight sheen) |

---

## 💡 Lighting Function

| Function | Description |
|----------|-------------|
| `PointLight()` | Sets up OpenGL point light source with position and color parameters |

---

## 📺 Display Functions

| Function | Description |
|----------|-------------|
| `Display()` | Initial menu screen with title "RIVER VIEW" and keyboard shortcuts |
| `display()` | **Day scene** - sky, sun, clouds, birds, boats, vegetation, buildings |
| `display1()` | **Rain scene** - stormy sky, lightning overlay, rain drops, puddles |
| `display2()` | **Night scene** - calls DrawSphere() with night elements |
| `DrawSphere()` | Night scene composition with moon, stars, dark colors |

---

## 🖼️ Text & UI Functions

| Function | Description |
|----------|-------------|
| `StartingText()` | Displays title, instructions, and team member credits using GLUT bitmap fonts |

---

## ⚙️ Setup & Control Functions

| Function | Description |
|----------|-------------|
| `init()` | Initializes OpenGL settings (depth test, lighting, shading, color material) |
| `reshape(w, h)` | Handles window resize, sets perspective projection |
| `handleKeypress(key, x, y)` | Keyboard handler: D=Day, N=Night, R=Rain + plays corresponding audio |
| `main()` | Program entry: creates window, initializes rain points, starts timers, enters main loop |

---

## 📊 Summary Statistics

| Category | Count |
|----------|-------|
| Timer Functions | 5 |
| Sky/Weather | 4 |
| Cloud Functions | 3 |
| Celestial Bodies | 3 |
| Terrain | 3 |
| Buildings/Structures | 7 |
| Tree | 1 |
| Boat Functions | 4 |
| Character | 1 |
| Bird Functions | 2 |
| Grass/Flower Functions | 6 |
| Display Functions | 5 |
| Setup/Control | 4 |
| **Total Functions** | **~48** |

---

## 🎮 Keyboard Controls

| Key | Action | Sound Effect |
|-----|--------|--------------|
| `D` / `d` | Day View | bird-2.wav |
| `N` / `n` | Night View | cricket-2.wav |
| `R` / `r` | Rain View | rain-07.wav |

---

## 👥 Team Members

- Md Rijoan Maruf (23-53347-3)
- Sadia Islam Anusha (23-55670-3)
- Jakiya Sultana Meduli (23-55439-3)
