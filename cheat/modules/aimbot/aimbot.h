#pragma once
#include "../../sdk/common.h"

class CAimbot {
private:
	int NearestBoneToCrosshair(uintptr_t target, uintptr_t localplayer);

public:
	void Run(uint64_t entity, QAngle aimangle, int aimi);
	void StandaloneNoRecoil();

	QAngle GetAimAngle(uint64_t aimentity);
	bool IsAiming = false;
};

inline CAimbot gAim;