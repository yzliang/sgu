#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

int n;

struct Sphere {
  int x, y, z, r;
} s[50];

const double kError = 1e-6;

#define SQUARE(x) ((x)*(x))

void Norm(double* x, double* y, double* z) {
  double len = sqrt(SQUARE(*x) + SQUARE(*y) + SQUARE(*z));
  *x /= len;
  *y /= len;
  *z /= len;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> s[i].x >> s[i].y >> s[i].z >> s[i].r;
  double x0, y0, z0;
  double dx, dy, dz;
  cin >> x0 >> y0 >> z0 >> dx >> dy >> dz;
  dx -= x0;
  dy -= y0;
  dz -= z0;

  int total = 0;
  bool output = false;
  bool just_meet[50] = {false};
  while (true) {
    double min_k = -1;
    int meet = -1;
    vector<int> other_meets;
    // Find the (closest) reflected sphere.
    for (int i = 0; i < n; i++) {
      // If the light just meets the sphere, they can't meet immediately again.
      if (just_meet[i])
        continue;
      // Compute the meeting point: coefficient k.
      // (x0 + dx*k - sx)^2 + (y0 + dy*k - sy)^2 + (z0 + dz*k - sz)^2 = sr^2.
      // The equation can only have positive roots.
      double a = dx * dx + dy * dy + dz * dz;
      double b = 2 * (dx * (x0 - s[i].x) + dy * (y0 - s[i].y) +
          dz * (z0 - s[i].z));
      double c = SQUARE(x0 - s[i].x) + SQUARE(y0 - s[i].y) +
        SQUARE(z0 - s[i].z) - SQUARE(s[i].r);
      double k = SQUARE(b) - 4 * a * c;
      if (k < 0)
        continue;  // No meeting point.
      k = (-b - sqrt(k)) / (2 * a);
      if (k < 0)
        continue;  // Negative meeting point.
      if (min_k == -1) {
        // New meeting point.
        min_k = k;
        meet = i;
      } else if (fabs(min_k - k) < kError) {
        // Multiple meets?
        other_meets.push_back(i);
      } else if (k < min_k) {
        // Closer meeting point.
        min_k = k;
        meet = i;
      }
    }
    if (meet == -1) {
      if (output)
        cout << endl;
      break;
    }

    // Process output.
    if (++total > 10) {
      cout << " etc." << endl;
      break;
    }
    if (output)
      cout << ' ';
    else
      output = true;
    cout << meet + 1;

    memset(just_meet, 0, sizeof(just_meet));
    just_meet[meet] = true;
    for (int i = 0; i < other_meets.size(); i++) {
      cout << ' ' << other_meets[i] + 1;
      just_meet[other_meets[i]] = true;
    }

    // Set new position and direction on the meeting point.
    x0 += min_k * dx;
    y0 += min_k * dy;
    z0 += min_k * dz;
    // (nx, ny, nz): normal vector.
    double nx = x0 - s[meet].x, ny = y0 - s[meet].y, nz = z0 - s[meet].z;
    Norm(&nx, &ny, &nz);
    // The incident vector is (dx, dy, dz).
    double prod = dx * nx + dy * ny + dz * nz;
    dx -= 2 * prod * nx;
    dy -= 2 * prod * ny;
    dz -= 2 * prod * nz;
  }
  return 0;
}
