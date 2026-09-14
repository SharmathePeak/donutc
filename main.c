#include <math.h>
#include <stdio.h>
#include <string.h>

int main() {
  // x = rcost , y = rsint
  // r = sqrt(x^2 + y^2) , t = tan^-1 (y/x)
  // x = cos(t)(R+rsin(p)) , y = sin(t)(R+rsin(p)) , z = partdist + rcos(p)
  // X = camdist/z * x , Y = camdist/z *y
  // 100% Human Made!!!

  const float pi = 3.14159;

  char brightness[] = ".,-~:;=!*#$@";
  char screen[50][75];

  int bright;

  float zbuffer[50][75];
  float x, y, z;
  float X, Y;
  float nx, ny, nz;
  float rnx, rny, rnz;
  float rrnx, rrny, rrnz;
  float rx, ry, rz;
  float rrx, rry, rrz;

  float R = 20, r = 8;
  float t = 0, p = 0, A_y = 0, A_x = 0;
  float camdist = 15, partdist = 35, k;
  float scale_x = 2.6 * 0.6;
  float scale_y = 1.2 * 0.6;
  float Lx = 0, Ly = 1, Lz = -1;

  memset(screen, ' ', sizeof(screen));
  memset(zbuffer, 0, sizeof(zbuffer));

  while (1) {
    memset(screen, ' ', sizeof(screen));
    memset(zbuffer, 0, sizeof(zbuffer));
    while (t <= 2 * pi) {
      while (p <= 2 * pi) {
        x = cos(t) * (R + r * sin(p));
        y = sin(t) * (R + r * sin(p));
        z = (r * cos(p));
        ry = y;
        rx = x * cos(A_y) + z * sin(A_y);
        rz = z * cos(A_y) - x * sin(A_y);
        rrx = rx;
        rry = ry * cos(A_x) + rz * sin(A_x);
        rrz = partdist + rz * cos(A_x) - ry * sin(A_x);
        k = camdist / rrz;
        X = k * rrx;
        Y = k * rry;
        int sx = 37 + (int)(X * scale_x);
        int sy = 15 - (int)(Y * scale_y);
        nx = cos(t) * sin(p);
        ny = sin(t) * sin(p);
        nz = cos(p);
        rny = ny;
        rnx = nx * cos(A_y) + nz * sin(A_y);
        rnz = nz * cos(A_y) - nx * sin(A_y);
        rrnx = rnx;
        rrny = rny * cos(A_x) + rnz * cos(A_x);
        rrnz = rnz * cos(A_x) - rny * sin(A_x);

        float dot = rrnx * Lx + rrny * Ly + rrnz * Lz;
        bright = (int)((dot + 1) * 5.5); // dot: -1..1 → bright: 0..11
        int idx = bright;
        if (sx >= 0 && sx < 75 && sy >= 0 && sy < 50) {
          float zinv = 1 / rrz;
          if (zinv > zbuffer[sy][sx]) {
            zbuffer[sy][sx] = zinv;
            screen[sy][sx] =
                brightness[(idx < 0) ? 0 : ((idx > 11) ? 11 : idx)];
          }
        }
        p += 0.01;
      }
      p = 0;
      t += 0.01;
    }
    t = 0;
    for (int i = 0; i < 50; i++) {
      for (int j = 0; j < 75; j++)
        printf("%c", screen[i][j]);
      printf("\n");
    }
    if (A_y >= 2 * pi) {
      A_y -= 2 * pi;
    }
    if (A_x >= 2 * pi) {
      A_x -= 2 * pi;
    }
    printf("\e[1;1H\e[2J");
    A_x += 0.01 * 5;
    A_y += 0.036 * 5;
  }
}
