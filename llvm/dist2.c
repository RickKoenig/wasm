#ifndef WASM
#include <math.h>
#endif

float dist2(float a, float b)
{
#ifdef WASM
	return __builtin_sqrt(a * a + b * b); // builtin sqrt, can't include <math.h> without WASI SDK
#else
	return sqrt(a * a + b * b); // math.h sqrt
#endif
	//return a * a + b * b; // no sqrt
} //hi
