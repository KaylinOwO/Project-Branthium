#pragma once
#include <Windows.h>

namespace PatternScan
{
	uintptr_t FindPattern(const char* pattern, uintptr_t start, uintptr_t end);
	uintptr_t FindPattern(const char* __restrict pattern, const char* __restrict module);
}