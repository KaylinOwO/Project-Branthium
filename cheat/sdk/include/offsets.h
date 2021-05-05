#define ENTITY_SIZE_DEF				0x42E0			//biggest entity offset

#define OFFSET_ENTITYLIST			0x18EDA78 // //0x18da3f8 //cl_entitylist
#define OFFSET_LOCAL_ENT			0x1C9D198 // //0x1c89a78   //LocalPlayer


#define OFFSET_TEAM					0x448		//m_iTeamNum	
#define OFFSET_HEALTH				0x438			//m_iHealth
#define OFFSET_NAME					0x589			//m_iName
#define OFFSET_SIG_NAME				0x580			//m_iSignifierName
#define OFFSET_SHIELD				0x170			//m_shieldHealth
#define OFFSET_MAX_SHIELD			0x174			//m_shieldHealth +0x4
#define OFFSET_ITEM_ID	0x1618

#define OFFSET_IN_ATTACK 0x040c1b90
#define OFFSET_IN_JUMP 0x040c1c00
#define OFFSET_IN_RELOAD 0x040c1bb0

#define OFFSET_GLOBALVARS 0x128bf40

#define OFFSET_ORIGIN				0x14C			//m_vecAbsOrigin
#define OFFSET_BONES				0xF38 			//m_bConstrainBetweenEndpoints 
#define OFFSET_AIMPUNCH				0x2430			//m_vecPunchWeapon_Angle
#define OFFSET_CAMERAPOS			0x1ED0			
#define OFFSET_VIEWANGLES			0x2518 			 
#define OFFSET_OBSERVING_TARGET		0x3350 			//m_hObserverTarget
#define OFFSET_NameList 0x81AF4C0 // //0x81330F0

#define OFFSET_MATRIX                  0x1B3BD0  
#define OFFSET_VIEWRENDER                0x40BF2E8//  0x408B8E8  

#define OFFSET_ITEM_GLOW            0x2c0 //m_highlightFunctionBits

#define OFFSET_CURRENT_WEAPON				0x1A6C //m_latestPrimaryWeapons
#define OFFSET_BULLET_SPEED         0x1ED0
#define OFFSET_BULLET_GRAVITY         0x1ED8
#define OFFSET_ZOOM_FOV             0x16F8 + 0xb8 //m_playerData + m_curZoomFOV

#define OFFSET_VISIBLE_TIME         0x1ACC
#define OFFSET_ZOOMING      		0x1b41 //m_bZooming

#define OFFSET_LIFE_STATE			0x798  //m_lifeState, >0 = dead
#define OFFSET_BLEED_OUT_STATE		0x2688 //m_bleedoutState, >0 = knocked

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
