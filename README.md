# SnakeOS

A snake game built from scratch on an Arduino Nano with a 128x64 OLED display and joystick control. No game engine, no shortcuts, just embedded C++, 2KB of RAM, and a lot lot lot of debugging.

---

## Hardware

| Component | Details |
|---|---|
| Microcontroller | Arduino Nano (ATmega328P) |
| Display | SSD1306 OLED 128x64 I2C |
| Input | KY-023 Analog Joystick |
| Power | 8V via Vin pin |

---

## Features

- Start / Resume menu with joystick navigation
- Joystick direction control with orientation-aware snake
- Snake grows on ball catch
- Score and speed display
- Speed increases with score
- Modular code structure 

---

## File Structure

```
SnakeOS/
├── SnakeOS.ino          — main loop, setup, display init
├── functions.cpp        — all game logic functions
├── functions.h          — function declarations
├── global_variables.cpp — global state definitions
└── global_variables.h   — extern declarations
```

---

## How It Works

The snake is a rectangle that moves across a 128x64 pixel canvas. Direction is controlled by reading the joystick's analog X and Y axes, mapped to a threshold range (±150 to ±180) to handle ADC noise. When the joystick crosses a threshold, the snake's width and height swap to reflect the new orientation, and speed vectors update accordingly.

Food spawns at a random position. Collision is detected using axis-aligned bounding box (AABB), checking if the food point falls within the snake rectangle on all four sides.

A start menu uses joystick Y-axis to navigate between Start and Resume options. A selection rectangle highlights the active option. Button press reads the highlighted position and either resets game state (Start) or returns to the game without resetting (Resume).

---

## What Was Hard

**The RAM wall.** The ATmega328P has 2KB of SRAM. The Adafruit SSD1306 library alone consumes 1024 bytes for its display frame buffer, half the available RAM before any game variables exist. Adding tail coordinate arrays pushed free RAM down to 194 bytes, causing silent crashes with no error output.

I got to know that this is a known constraint in Arduino embedded development. The solution is a grid-based movement system (storing grid units instead of pixel coordinates) which I learned from Lakshya-Coder in References, the , `byte` arrays instead of `int`, and moving string literals to flash using the `F()` macro. This work is ongoing, see the `dev` branch.

**Gyro drift and complementary filters.** Before this project, the same hardware stack was used to build an MPU6050 complementary filter with adaptive k blending. That work established the foundation for understanding real-time sensor systems, which directly informed how this game handles continuous joystick input without blocking delays. I am planning to add Gyro functions to this game too if time allows.

**Modular Arduino C++.** Splitting an Arduino sketch into `.cpp` and `.h` files requires `extern` declarations, careful include order, and understanding that `.ino` globals are not automatically visible to `.cpp` files. Several silent bugs came from variable shadowing — declaring `int snake_x` inside an `if` block instead of assigning to the global.

---

## Known Limitations

- Tail system not yet complete — RAM constraint requires grid-based refactor
- No game over screen yet
- No self-collision detection
- Joy Y-axis exact comparison (`== ±180`) in menu — needs threshold fix

---

## What's Next

- Grid-based movement system to free RAM
- `byte` arrays for tail coordinates
- Game over screen with score
- Self-collision detection
- Possibly port to ESP32 for full tail implementation and WiFi data logging

---

## References

These repositories were studied to understand the RAM constraint and how others solved it on the same hardware:

- [deshrit/snake_game_arduino](https://github.com/deshrit/snake_game_arduino) — Arduino Nano + SSD1306, explicitly documents `#define MAX_SNAKE_SIZE 50 // low memory`
- [Lakshya-Coder/Arduino_Snake_Game](https://github.com/Lakshya-Coder/Arduino_Snake_Game) — Nano + OLED + joystick, same hardware stack, uses PROGMEM bitmaps to save RAM

---

## Author

**ctrl+z** — EEE 3rd year, building toward embedded AI engineering.
