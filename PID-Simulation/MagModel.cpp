#include <math.h>

/* 
* ydepth - extrusion depth in inches
* N - turns
* i - current in amps
* g - gap in meters
*/

double Frel (double ydepth, int N, double i, double g)
{
  return(0.6167266375e9 / ydepth * pow(-(double) (2 * N * i) + 0.4446789110e5, 0.2e1) * pow(0.2466906550e10 * g / ydepth + 0.6886569338e8 / ydepth, -0.2e1) - 0.3042813963e19 * g * pow(ydepth, -0.2e1) * pow(-(double) (2 * N * i) + 0.4446789110e5, 0.2e1) * pow(0.2466906550e10 * g / ydepth + 0.6886569338e8 / ydepth, -0.3e1));
}


