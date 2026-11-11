#include <math.h>

float dist2(float a, float b)
{
	//return __builtin_sqrt(a * a + b * b); // builtin sqrt
	return sqrt(a * a + b * b); // math.h sqrt
	//return pow(a * a + b * b, 2.5f); // math.h sqrt
	//return a * a + b * b; // no sqrt
}
