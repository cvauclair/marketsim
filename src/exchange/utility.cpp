#include "utility.h"

bool sameRate(double rate1, double rate2)
{
	return std::floor(rate1 * 1000 + 0.5) == std::floor(rate2 * 1000.0 + 0.5);
}

bool sameRate(float rate1, float rate2)
{
	return std::floor(rate1 * 1000.f + 0.5f) == std::floor(rate2 * 1000.0f + 0.5f);
}
