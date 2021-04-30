#define ENTITY_SIZE_DEF				0x42E0			//biggest entity offset

#define OFFSET_ENTITYLIST			0x18db438 // //0x18da3f8 //cl_entitylist
#define OFFSET_LOCAL_ENT			0x1c8aa98 // //0x1c89a78   //LocalPlayer


#define OFFSET_TEAM					0x450		//m_iTeamNum	
#define OFFSET_HEALTH				0x440			//m_iHealth
#define OFFSET_NAME					0x589			//m_iName
#define OFFSET_SIG_NAME				0x580			//m_iSignifierName
#define OFFSET_SHIELD				0x170			//m_shieldHealth
#define OFFSET_MAX_SHIELD			0x174			//m_shieldHealth +0x4
#define OFFSET_ITEM_ID	0x1618

#define OFFSET_IN_ATTACK 0x0408f2b0
#define OFFSET_IN_JUMP 0x0408f328
#define OFFSET_IN_RELOAD 0x0408f2d0

#define OFFSET_GLOBALVARS 0x1278220

#define OFFSET_ORIGIN				0x14C			//m_vecAbsOrigin
#define OFFSET_BONES				0xF38 			//m_bConstrainBetweenEndpoints 
#define OFFSET_AIMPUNCH				0x2390			//m_vecPunchWeapon_Angle
#define OFFSET_CAMERAPOS			0x1E30			
#define OFFSET_VIEWANGLES			0x2478 			 
#define OFFSET_OBSERVING_TARGET		0x32a8 			//m_hObserverTarget
#define OFFSET_NameList 0x81342f0 // //0x81330F0

#define OFFSET_MATRIX                  0x1b3bd0  
#define OFFSET_VIEWRENDER                0x408c968//  0x408B8E8  

#define OFFSET_ITEM_GLOW            0x2c0 //m_highlightFunctionBits

#define OFFSET_CURRENT_WEAPON				0x19ec //m_latestPrimaryWeapons
#define OFFSET_BULLET_SPEED         0x1e50
#define OFFSET_BULLET_GRAVITY         0x1e58
#define OFFSET_ZOOM_FOV             0x1678 + 0xb8 //m_playerData + m_curZoomFOV

#define OFFSET_VISIBLE_TIME         0x1A4C
#define OFFSET_ZOOMING      		0x1b41 //m_bZooming

#define OFFSET_LIFE_STATE			0x798  //m_lifeState, >0 = dead
#define OFFSET_BLEED_OUT_STATE		0x25e8 //m_bleedoutState, >0 = knocked

#define OFFSET_BREATH_ANGLES		OFFSET_VIEWANGLES - 0x10

#define OFFSET_ABS_VELOCITY         0x140 //m_vecAbsVelocity
//"Highlight: function parameter id should"

#define OFFSET_GLOW_ENABLE          0x3c8 //7 = enabled, 2 = disabled
#define OFFSET_GLOW_THROUGH_WALLS   0x3d0 //2 = enabled, 5 = disabled
#define GLOW_TYPE 0x2C4 //0x2C4 //OK Script_Highlight_GetState + 4 / m_highlightFunctionBits  + 4?
#define GLOW_COLOR_R 0x1D0 //OK Script_CopyHighlightState mov tcx nº7  / m_highlightParams + 24 (0x18)
#define GLOW_COLOR_G 0x1D4 //OK Script_CopyHighlightState mov tcx nº7  / m_highlightParams + 24 (0x18)
#define GLOW_COLOR_B 0x1D8 //OK Script_CopyHighlightState mov tcx nº7  / m_highlightParams + 24 (0x18)
#define GLOW_DISTANCE 0x3B4 //OK Script_Highlight_SetFarFadeDist / m_highlightServerFadeEndTimes + 52(0x34)

#define OFFSET_HELMET_TYPE			0x4374			//m_helmetType