#include <cmath>
#include <Windows.h>

struct PredictCtx
{
	Vector3 StartPos;
	Vector3 TargetPos;
	Vector3 TargetVel;
	float BulletSpeed;
	float BulletGravity;

	Vector2D AimAngles;
};

inline Vector3 ExtrapolatePos(const PredictCtx& Ctx, float Time)
{
	return Ctx.TargetPos + (Ctx.TargetVel * Time);
}

inline bool OptimalPitch(const PredictCtx& Ctx, const Vector2D& Dir2D, float* OutPitch)
{
	float Vel = Ctx.BulletSpeed, Grav = Ctx.BulletGravity, DirX = Dir2D.x, DirY = Dir2D.y;
	float Root = Vel * Vel * Vel * Vel - Grav * (Grav * DirX * DirX + 2.f * DirY * Vel * Vel);
	if (Root >= 0.f) { *OutPitch = atanf((Vel * Vel - sqrt(Root)) / (Grav * DirX)); return true; }
	return false;
}

inline bool SolveTrajectory(PredictCtx& Ctx, const Vector3& ExtrPos, float* TravelTime)
{
	Vector3 Dir = ExtrPos - Ctx.StartPos;
	Vector2D Dir2D = { sqrtf(Dir.x * Dir.x + Dir.y * Dir.y), Dir.z };

	float CurPitch;
	if (!OptimalPitch(Ctx, Dir2D, &CurPitch))
	{
		return false;
	}

	*TravelTime = Dir2D.x / (cosf(CurPitch) * Ctx.BulletSpeed);
	Ctx.AimAngles.y = atan2f(Dir.y, Dir.x);
	Ctx.AimAngles.x = CurPitch;
	return true;
}

inline bool BulletPredict(PredictCtx& Ctx)
{
	float MAX_TIME = 1.f, TIME_STEP = (1.f / 256.f);
	for (float CurrentTime = 0.f; CurrentTime <= MAX_TIME; CurrentTime += TIME_STEP)
	{
		float TravelTime;
		Vector3 ExtrPos = ExtrapolatePos(Ctx, CurrentTime);
		if (!SolveTrajectory(Ctx, ExtrPos, &TravelTime))
		{
			return false;
		}

		if (TravelTime < CurrentTime)
		{
			Ctx.AimAngles = { -RAD2DEG(Ctx.AimAngles.x), RAD2DEG(Ctx.AimAngles.y) };
			return true;
		}
	}
	return false;
}