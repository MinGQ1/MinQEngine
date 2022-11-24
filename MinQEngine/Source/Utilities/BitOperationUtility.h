#pragma once

#define LOWEST_BIT_CLEAR(x) x & (x - 1)

template<typename T>
inline T BitCeil(T input, size_t refNum)
{
	refNum = refNum - 1;
	return (input + refNum) & ~refNum;
}

