#include "visuals.h"

inline float DistanceU(Vector3 myPos, Vector3 enPos) { return sqrt((myPos.x - enPos.x) * (myPos.x - enPos.x) + (myPos.y - enPos.y) * (myPos.y - enPos.y) + (myPos.z - enPos.z) * (myPos.z - enPos.z)); }
inline float DistanceM(Vector3 myPos, Vector3 enPos) { auto f = DistanceU(myPos, enPos); f *= 0.0254f; return f; }
void CVisuals::PlayerESP(uintptr_t entity, uintptr_t localent)
{
	if (!vars::visuals::enabled) return;

	/*glow esp*/
	if (vars::visuals::players::glow)
		entity::EnableGlowPlayer(entity);
	else
		entity::DisablePlayerGlow(entity);


	/*overlay esp*/
	Vector3 FeetPosition = entity::GetEntityBasePosition(entity);
	Vector3 HeadPosition = entity::GetEntityBonePosition(entity, 8, FeetPosition);
	Vector3 BasePosition = WorldToScreen(entity::GetEntityBasePosition(entity), Width, Height);
	if (BasePosition.x > 0 && BasePosition.y > 0)
	{
		Vector3 CenterHitbox = WorldToScreen(entity::GetEntityBonePosition(entity, 2, FeetPosition), Width, Height);
		Vector3 HeadHitbox = WorldToScreen(HeadPosition, Width, Height);
		Vector3 FeetHitbox = WorldToScreen(FeetPosition, Width, Height);
		float box_height = HeadHitbox.y - FeetHitbox.y;
		float box_width = box_height / 1.2f;
		int health = read<int>(entity + OFFSET_HEALTH);
		int shield = read<int>(entity + OFFSET_SHIELD);
		ImColor HealthColor = ImColor(min(510 * (100 - health) / 100, 255), min(510 * health / 100, 255), 25, 255);

		if (health > 0)
		{
			auto DistFrom = !entity::IsAlive(localent) ? -1 : DistanceM(entity::GetEntityBasePosition(localent), entity::GetEntityBasePosition(entity));

			if (DistFrom != -1 && DistFrom > vars::visuals::players::distancelimit) return;

			int iY = 0;

			if (vars::visuals::players::debug_bones)
			{
				for (int i = 0; i < 300; i++) // to save runtime only doing 300 which seems to show most if not all bones
				{
					Vector3 BonePos = WorldToScreen(entity::GetEntityBonePosition(entity, i, FeetPosition), Width, Height);
					DrawOutlinedText(m_pFont, std::to_string(i), ImVec2(BonePos.x, BonePos.y), 12, IM_COL32(255, 255, 255, 255), true); // sussy baka code
				}
			}
			if (vars::visuals::players::box)
			{
				DrawBox(CenterHitbox.x, FeetHitbox.y, box_width, box_height, IM_COL32(255, 255, 255, 255));
			}
			if (vars::visuals::players::name)
			{
				DrawOutlinedText(m_pFont, XorStr("player"), ImVec2(CenterHitbox.x, CenterHitbox.y + iY), 12, IM_COL32(255, 255, 255, 255), true);
				iY += 12;
			}
			if (vars::visuals::players::knocked && entity::IsKnocked(entity))
			{
				DrawOutlinedText(m_pFont, XorStr("knocked"), ImVec2(CenterHitbox.x, CenterHitbox.y + iY), 12, IM_COL32(0, 191, 255, 255), true);
				iY += 12;
			}
			if (vars::visuals::players::health)
			{
				DrawOutlinedText(m_pFont, std::to_string(health), ImVec2(CenterHitbox.x, CenterHitbox.y + iY), 12, ImGui::ColorConvertFloat4ToU32(HealthColor), true);
				iY += 12;
			}
			if (vars::visuals::players::shield && shield > 0)
			{
				DrawOutlinedText(m_pFont, std::to_string(shield), ImVec2(CenterHitbox.x, CenterHitbox.y + iY), 12, IM_COL32(0, 191, 255, 255), true);
				iY += 12;
			}
			if (vars::visuals::players::distance && DistFrom != -1)
			{
				DrawOutlinedText(m_pFont, (std::to_string((int)DistFrom) + "m"), ImVec2(CenterHitbox.x, CenterHitbox.y + iY), 12, IM_COL32(255, 255, 255, 255), true);
				iY += 12;
			}
		}
	}

}