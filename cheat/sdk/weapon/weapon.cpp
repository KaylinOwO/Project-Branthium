#include "../common.h"

void WeaponXEntity::update(uintptr_t LocalPlayer)
{
	uint64_t entitylist = oBaseAddress + OFFSET_ENTITYLIST;
	uint64_t wephandle = read<uint64_t>(LocalPlayer + OFFSET_CURRENT_WEAPON /*active weapon*/);

	wephandle &= 0xffff;

	uint64_t wep_entity = read<uint64_t>(entitylist + (wephandle << 5));

	
	projectile_speed = read<float>(wep_entity + OFFSET_BULLET_SPEED);
	projectile_scale = read<float>(wep_entity + OFFSET_BULLET_GRAVITY);
	zoom_fov = read<float>(wep_entity + OFFSET_ZOOM_FOV);
}

float WeaponXEntity::get_projectile_speed()
{
	return projectile_speed;
}

float WeaponXEntity::get_projectile_gravity()
{
	return 750.0f * projectile_scale;
}

float WeaponXEntity::get_zoom_fov()
{
	return zoom_fov;
}