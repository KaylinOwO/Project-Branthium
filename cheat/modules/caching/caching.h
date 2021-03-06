#pragma once
#include "../../sdk/common.h"

inline std::vector<EntityCache> CachedPlayerList;
inline void PlayerCache()
{
	while (true)
	{
		std::vector<EntityCache> tmplist;
		uint64_t entitylist = oBaseAddress + OFFSET_ENTITYLIST;
		uint64_t baseent = read<uint64_t>(entitylist);
		if (baseent == 0)
			continue;

		for (int i = 0; i < 128; i++)
		{
			uint64_t localent = read<uint64_t>(oBaseAddress + OFFSET_LOCAL_ENT);
			if (!localent) continue;

			uint64_t centity = read<uint64_t>(entitylist + ((uint64_t)i << 5));
			if (!entity::IsPlayer(centity)) continue;
			int health = read<int>(centity + OFFSET_HEALTH);
			if (health < 1 || entity::GetTeam(centity) == entity::GetTeam(localent)) continue;

			EntityCache EntityCache{ };
			EntityCache.player_entity = centity;
			EntityCache.player_id = i;
			tmplist.push_back(EntityCache);

		}

		CachedPlayerList = tmplist;
		Sleep(1);
	}
}
