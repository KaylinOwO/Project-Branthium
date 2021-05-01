#pragma once
#include "../common.h"

struct GlowMode
{
	int8_t GeneralGlowMode, BorderGlowMode, BorderSize, TransparentLevel;
};

typedef struct _EntityCache
{
	uint64_t player_entity;
	int player_id;
}EntityCache;

struct MatrixA
{
	float matrix[16];
};

struct kbutton_t
{
	// key nums holding it down
	int		down[2];
	// low bit is down state
	int		state;
};