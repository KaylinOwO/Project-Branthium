#pragma once
#include "../common.h"

namespace entity 
{
	inline bool IsPlayer(uintptr_t ent)
	{
		uint64_t name = read<uint64_t>( ent + OFFSET_NAME);
		return (name == 125780153691248);
	}
	inline bool IsItem(uintptr_t ent)
	{
		return read<int>( ent + OFFSET_ITEM_GLOW) >= 1358917120;
	}

	inline bool IsAlive(uintptr_t ent)
	{
		return read<int>( ent + OFFSET_LIFE_STATE) == 0;
	}
	inline bool IsKnocked(uintptr_t ent)
	{
		return read<int>( ent + OFFSET_BLEED_OUT_STATE) > 0;
	}
	inline int GetTeam(uintptr_t ent)
	{
		return read<int>( ent + OFFSET_TEAM);
	}
	inline Vector3 GetViewAngles(uintptr_t ent)
	{
		return read<Vector3>( ent + OFFSET_VIEWANGLES);
	}
	inline Vector3 GetSwayAngles(uintptr_t ent)
	{
		return read<Vector3>( ent + OFFSET_BREATH_ANGLES);
	}
	inline QAngle GetViewAnglesA(uintptr_t ent)
	{
		return read<QAngle>( ent + OFFSET_VIEWANGLES);
	}
	inline Vector3 GetEntityBasePosition(uintptr_t ent)
	{
		return read<Vector3>( ent + OFFSET_ORIGIN);
	}
	inline D3DXVECTOR3 GetEntityBasePositionD3DX(uintptr_t ent)
	{
		return read<D3DXVECTOR3>( ent + OFFSET_ORIGIN);
	}
	inline uintptr_t GetEntityBoneArray(uintptr_t ent)
	{
		return read<uintptr_t>( ent + OFFSET_BONES);
	}
	inline Vector3 GetEntityBonePosition(uintptr_t ent, uint32_t BoneId, Vector3 BasePosition)
	{
		unsigned long long pBoneArray = GetEntityBoneArray(ent);

		Vector3 EntityHead = Vector3();

		EntityHead.x = read<float>( pBoneArray + 0xCC + (BoneId * 0x30)) + BasePosition.x;
		EntityHead.y = read<float>( pBoneArray + 0xDC + (BoneId * 0x30)) + BasePosition.y;
		EntityHead.z = read<float>( pBoneArray + 0xEC + (BoneId * 0x30)) + BasePosition.z;

		return EntityHead;
	}
	inline void SetViewAngles(uintptr_t ent, Vector3 angles)
	{
		writeval<Vector3>(ent + OFFSET_VIEWANGLES, angles);
	}
	inline void SetViewAngles(uintptr_t ent, QAngle angles)
	{
		writeval<QAngle>(ent + OFFSET_VIEWANGLES, angles);
	}
	inline float LastVisTime(uintptr_t ent)
	{
		return read<float>( ent + OFFSET_VISIBLE_TIME);
	}

	inline Vector3 GetCamPos(uintptr_t ent)
	{
		return read<Vector3>( ent + OFFSET_CAMERAPOS);
	}

	inline QAngle GetSwayAnglesA(uintptr_t ent)
	{
		return read<QAngle>( ent + OFFSET_BREATH_ANGLES);
	}

	inline QAngle GetRecoil(uintptr_t ent)
	{
		return read<QAngle>( ent + OFFSET_AIMPUNCH);
	}
	inline Vector3 GetRecoilA(uintptr_t ent)
	{
		return read<Vector3>( ent + OFFSET_AIMPUNCH);
	}
	inline Vector3 GetAbsVelocity(uintptr_t ent)
	{
		return read<Vector3>( ent + OFFSET_ABS_VELOCITY);
	}
	inline float oVisTime[100];
	inline bool IsVisible(uintptr_t ent, int i) {
		const auto VisCheck = LastVisTime(ent);

		const auto IsVis = VisCheck > oVisTime[i] || VisCheck < 0.f && oVisTime[i] > 0.f;

		oVisTime[i] = VisCheck;

		return IsVis;
	}
	inline Vector3 GetPosition(uintptr_t ent)
	{
		return read<Vector3>( ent + OFFSET_ORIGIN);
	}

	inline bool IsGlowingItem(uintptr_t ent)
	{
		return read<int>( ent + OFFSET_ITEM_GLOW) >= 1363184265;
	}
	inline void EnableGlowPlayer(uintptr_t ent)
	{
		if (read<int>( ent + GLOW_COLOR_B) == 2.f) return;
		writeval<int>(ent + OFFSET_GLOW_ENABLE, 1);
		writeval<int>(ent + OFFSET_GLOW_THROUGH_WALLS, 2);
		writeval<GlowMode>(ent + GLOW_TYPE, { 101,101,46,90 });
		writeval<float>(ent + GLOW_COLOR_R, 61.f); // r
		writeval<float>(ent + GLOW_COLOR_G, 2.f);  // g
		writeval<float>(ent + GLOW_COLOR_B, 2.f); // b
	}
	inline void DisablePlayerGlow(uintptr_t ent)
	{
		if (read<int>( ent + GLOW_COLOR_B) == 0.0f) return;

		writeval<int>(ent + OFFSET_GLOW_ENABLE, 2);
		writeval<int>(ent + OFFSET_GLOW_THROUGH_WALLS, 5);
		writeval<GlowMode>(ent + GLOW_TYPE, {  0, 0 });
		writeval<float>(ent + GLOW_COLOR_R, 0.0f); // r
		writeval<float>(ent + GLOW_COLOR_G, 0.0f);  // g
		writeval<float>(ent + GLOW_COLOR_B, 0.0f); // b
	}
	inline bool IsDummy(uintptr_t ent)
	{
		uint64_t team = read<uint64_t>( ent + OFFSET_TEAM);
		return (team == 97);
	}
};
