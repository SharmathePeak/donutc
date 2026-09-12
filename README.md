# donutc

A from-scratch C implementation of the classic spinning ASCII donut, built in about 8 hours by working through the underlying math and rendering pipeline step by step — no copy-pasting the famous one-liner, just building each piece up from the source material and understanding *why* it works.

```
```

## What it does

Renders a rotating 3D torus (donut) directly to the terminal using nothing but ASCII characters, recreating the effect popularized by Andy Sloane's `donut.c`.

## How it works

The renderer builds up the shape and image entirely from scratch, frame by frame:

1. **Torus generation** — every point on the donut's surface is generated from two angles: one sweeping around the big ring (`t`), one sweeping around the tube's cross-section (`p`).
2. **3D rotation** — each point is rotated around two axes (`A_x`, `A_y`) using standard rotation matrices, so the donut tumbles in 3D space rather than sitting static.
3. **Perspective projection** — rotated 3D points are projected onto a 2D plane by dividing by depth, so closer parts of the donut appear larger than farther parts.
4. **Z-buffering** — a per-pixel depth buffer ensures that when multiple surface points project to the same screen character, only the nearest one is drawn, correctly hiding the far side of the donut behind the near side.
5. **Lighting** — a surface normal is calculated for every point and compared against a fixed light direction via a dot product, producing a brightness value that's mapped onto a gradient of ASCII characters (`.,-~:;=!*#$@`) from dim to bright.
6. **Animation** — the whole pipeline reruns every frame with incrementing rotation angles, clearing and redrawing the terminal to produce continuous motion.

## Building

```bash
gcc donut.c -o donut -lm
```

## Running

```bash
./donut
```

Press `Ctrl+C` to stop.

## Notes

- Tune `R` (ring radius) and `r` (tube radius) to change the donut's proportions — a larger `R`-to-`r` ratio gives a more pronounced hole.
- `A_x` and `A_y` control rotation speed on each axis; using non-simple-ratio increments keeps the tumble from looking mechanically repetitive.
- `scale_x` / `scale_y` compensate for terminal character aspect ratio (characters are taller than they are wide), keeping the donut looking round instead of squished.
