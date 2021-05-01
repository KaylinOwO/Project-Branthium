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

		for (int i = 0; i < max_clients + 1; i++)
		{
			uint64_t localent = read<uint64_t>(oBaseAddress + OFFSET_LOCAL_ENT);
			if (!localent) continue;

			uint64_t centity = read<uint64_t>(entitylist + ((uint64_t)i << 5));
			int health = read<int>(centity + OFFSET_HEALTH);
			if (!entity::IsPlayer(centity)) continue;
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