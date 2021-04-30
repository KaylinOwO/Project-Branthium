#include "aimbot.h"

int CAimbot::NearestBoneToCrosshair(uintptr_t target, uintptr_t localplayer)
{
	int best;
	float maxfov = FLT_MAX;
	const int size = 4;
	int bones[size] = { 3, 2, 5, 8 };
	Vector3 FeetPosition = entity::GetEntityBasePosition(target);
	for (int num = 0; num < size; num++) {
		if (target != 0) {
			float fov = GetFov(entity::GetViewAnglesA(localplayer), CalcAngle(entity::GetCamPos(localplayer), entity::GetEntityBonePosition(target, bones[num], FeetPosition)));
			if (fov < maxfov) {
				maxfov = fov;
				best = bones[num];
			}
		}
	}
	return best;
}

QAngle CAimbot::GetAimAngle(uint64_t aimentity)
{
	uint64_t localent = read<uint64_t>(oBaseAddress + OFFSET_LOCAL_ENT);
	if (localent == 0) return QAngle(0, 0, 0);
	if (!entity::IsAlive(localent)) return QAngle(0, 0, 0);

	if (aimentity == 0) return QAngle(0, 0, 0);

	static int rhitboxpos = 8;
	switch (vars::aim::bone)
	{
	case 2:
		rhitboxpos = NearestBoneToCrosshair(aimentity, localent);
		break;
	case 0:
		rhitboxpos = 8;
		break;
	case 1:
		rhitboxpos = 3;
		break;
	}

	Vector3 LocalCamera = entity::GetCamPos(localent);
	Vector3 ViewAngles = entity::GetViewAngles(localent);
	Vector3 HeadPosition = entity::GetEntityBonePosition(aimentity, rhitboxpos, entity::GetEntityBasePosition(aimentity));

	WeaponXEntity curweap = WeaponXEntity();
	curweap.update(localent);
	float BulletSpeed = curweap.get_projectile_speed();
	float BulletGrav = curweap.get_projectile_gravity();
	PredictCtx Ctx;
	Ctx.StartPos = LocalCamera;
	Ctx.TargetPos = HeadPosition;
	Ctx.BulletSpeed = BulletSpeed - (BulletSpeed * 0.08f);
	Ctx.BulletGravity = BulletGrav + (BulletGrav * 0.05f);
	Ctx.TargetVel = entity::GetAbsVelocity(aimentity);

	QAngle AimAngle = CalcAngle(LocalCamera, HeadPosition);

	AimAngle = (vars::aim::bullet_prediction && BulletPredict(Ctx) && BulletSpeed > 1.f ? QAngle{ Ctx.AimAngles.x, Ctx.AimAngles.y, ViewAngles.z } : CalcAngle(LocalCamera, HeadPosition));
	if (vars::aim::no_recoil >= 1)
		AimAngle -= vars::aim::no_recoil >= 2 ? (entity::GetSwayAnglesA(localent) - entity::GetViewAnglesA(localent)) : entity::GetRecoil(localent);

	return AimAngle;
}

float AimSpeed = 1.5f;

void CAimbot::Run(uint64_t entity, QAngle aimangle, int aimi)
{
	static double realkey = VK_LBUTTON;
	switch (vars::aim::key)
	{
	case 0:
		realkey = VK_LBUTTON;
		break;
	case 1:
		realkey = VK_RBUTTON;
		break;
	case 2:
		realkey = VK_MBUTTON;
		break;
	case 3:
		realkey = VK_XBUTTON1;
		break;
	case 4:
		realkey = VK_XBUTTON2;
		break;
	case 5:
		realkey = vars::aim::inputkey;
		break;
	}


	if (!(GetKeyState(realkey) & 0x8000))
	{
		Sleep(10);
		return;
	}
	
	uint64_t localent = read<uint64_t>(oBaseAddress + OFFSET_LOCAL_ENT);
	if (localent == 0) return;
	if (aimangle == QAngle(0, 0, 0)) return;
	if (!entity::IsAlive(localent)) return;
	if (entity::IsKnocked(localent)) return;
	if (entity == 0) return;
	if (!entity::IsVisible(entity, aimi)) return;

	QAngle CalculatedAngles = GetAimAngle(entity);
	QAngle ViewAngles = entity::GetViewAnglesA(localent);

	NormalizeAngles(CalculatedAngles);
	QAngle Delta = CalculatedAngles - ViewAngles;
	NormalizeAngles(Delta);

	QAngle SmoothedAngles = ViewAngles + (vars::aim::smooth ? Delta / vars::aim::smoothing : Delta );
	entity::SetViewAngles(localent, SmoothedAngles);
}