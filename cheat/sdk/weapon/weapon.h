#pragma once
#include <Windows.h>

class WeaponXEntity
{
public:
	void update(uintptr_t LocalPlayer);
	float get_projectile_speed();
	float get_projectile_gravity();
	float get_zoom_fov();

private:
	float projectile_scale;
	float projectile_speed;
	float zoom_fov;
};
