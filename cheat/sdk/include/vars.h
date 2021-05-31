#pragma once

namespace vars {
	namespace aim {
		inline bool enabled = true, returnold = true;

		inline bool bullet_prediction = true, smooth = false;
		inline float fov = 13, smoothing = 6;
		inline int no_recoil = 1, key, bone = 2;
		inline double  inputkey;
	}
	namespace visuals {
		inline bool enabled = true;

		namespace players {
			inline bool name = true, knocked = true, health = true, shield = true, distance = true, box = true, glow = true, debug_bones = false;
			inline float distancelimit = 500;
		}
	}
}