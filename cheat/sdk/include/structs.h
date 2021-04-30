#pragma once
#include "../common.h"

struct GlowMode
{
	int8_t GeneralGlowMode, BorderGlowMode, BorderSize, TransparentLevel;
};

enum struct GroupType_t
{
	PLAYERS_ALL,
	PLAYERS_ENEMIES,
	PLAYERS_TEAMMATES,

	BUILDINGS_ALL,
	BUILDINGS_ENEMIES,
	BUILDINGS_TEAMMATES,

	PROJECTILES_ALL,
	PROJECTILES_ENEMIES,
	PROJECTILES_TEAMMATES,

	AMMOPACKS_ALL,
	HEALTHPACKS_ALL
};

typedef struct _EntityCache
{
	uint64_t player_entity, item_entity;
	int player_id, item_id;
}EntityCache;


typedef struct _ItemCacheS
{
	uint64_t item_entity = 0x0;
	D3DXVECTOR3 origin = D3DXVECTOR3();
	DWORD nameid;
	FLOAT Distance = 0;
	int itemtype = 0;
}ItemCacheS;

struct MatrixA
{
	float matrix[16];
};

union FloatInt {
	float f32;
	int32_t i32;
	uint32_t u32;
	uint8_t bytes[4];
};

typedef struct
{
	char szCN[0x100];
	char szEN[0x100];
	char szTexture[0x100];
}ITEM_NAME, * PITEM_NAME;


struct kbutton_t
{
	// key nums holding it down
	int		down[2];
	// low bit is down state
	int		state;
};