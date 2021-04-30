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
			inline bool name = true, health = true, shield = true, distance = true, glow = true;
			inline float distancelimit = 500;
		}
	}
}