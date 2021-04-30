#pragma once
#include "../common.h"


inline void NormalizeAngles(QAngle& angle)
{
	while (angle.x > 89.0f)
		angle.x -= 180.f;

	while (angle.x < -89.0f)
		angle.x += 180.f;

	while (angle.y > 180.f)
		angle.y -= 360.f;

	while (angle.y < -180.f)
		angle.y += 360.f;
}
inline void NormalizeAngles(Vector3& angle)
{
	while (angle.x > 89.0f)
		angle.x -= 180.f;

	while (angle.x < -89.0f)
		angle.x += 180.f;

	while (angle.y > 180.f)
		angle.y -= 360.f;

	while (angle.y < -180.f)
		angle.y += 360.f;
}
inline void ClampAngles(Vector3& angle)
{
	if (angle.y > 180.0f)
		angle.y = 180.0f;
	else if (angle.y < -180.0f)
		angle.y = -180.0f;

	if (angle.x > 89.0f)
		angle.x = 89.0f;
	else if (angle.x < -89.0f)
		angle.x = -89.0f;

	angle.z = 0;
}
inline float GetFov(const QAngle& viewAngle, const QAngle& aimAngle)
{
	QAngle delta = aimAngle - viewAngle;
	NormalizeAngles(delta);

	return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}
inline QAngle CalcAngle(const Vector3& src, const Vector3& dst)
{
	QAngle srca = { src.x, src.y, src.z };
	QAngle dsta = { dst.x, dst.y, dst.z };

	QAngle angle;
	QAngle delta = srca - dsta;

	double hyp = sqrtf((delta.x * delta.x) + (delta.y * delta.y));
	angle.x = (float)(atan(delta.z / hyp) * 57.295779513082f);
	angle.y = (float)(atan(delta.y / delta.x) * 57.295779513082f);
	if (delta.x >= 0.0) angle.y += 180.0f;


	return angle;
}
inline float Dist(D3DXVECTOR3 EntityPos, D3DXVECTOR3 PlayerPos)
{
	float Dist = sqrt((PlayerPos.x - EntityPos.x) * (PlayerPos.x - EntityPos.x)
		+ (PlayerPos.y - EntityPos.y) * (PlayerPos.y - EntityPos.y)
		+ (PlayerPos.z - EntityPos.z) * (PlayerPos.z - EntityPos.z));
	return Dist * 0.01905f;
}
inline float Dist3D(const Vector3& Src, const Vector3& Dst)
{
	return FastSqrt(powf(Src.x - Dst.x, 2.f) + powf(Src.y - Dst.y, 2.f) + powf(Src.z - Dst.z, 2.f));
}
