#pragma once
#include <windows.h>
#include <winternl.h>
#include <process.h>
#include <tlhelp32.h>
#include <inttypes.h>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <memory>
#include <string_view>
#include <cstdint>
#include <string>
#include <cmath>
#include <thread>
#include <cassert>
#include <xstring>
#include <dwmapi.h>
#include <vector>
#include <map>
#include <array>
#include <sstream>
#include <fstream>
#include <direct.h>

#define COGNITOKEY "gjDlgzRznEDRsfaO1pADDIoRsoRseVqC3lteuxDQR1MP7Cp7XZC15cX0WPI57jUr"

#pragma comment (lib, "d3d9.lib")

#include "dxsdk/d3d9.h"
#include "dxsdk/d3dx9.h"
#include "dxsdk/d3d9_x.h"

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx9.h"
#include "Imgui/imgui_impl_win32.h"

inline ImFont* m_pFont; 
inline ImFont* m_pFont2;
inline DWORD ScreenCenterX;
inline DWORD ScreenCenterY;
inline uintptr_t verifiedusercmd;

inline uint32_t max_clients;
inline float curtime;
inline float interval_per_tick;

#include "include/vars.h"
#include "include/offsets.h"
#include "include/structs.h"
#include "include/xorstr.h"
#include "include/win_utils.h"
#include "include/classes.h"
#include "include/math.h"
#include "include/basestruct.h"

inline std::map<int, ITEM_NAME> g_ItemHash;
#include "include/utils.h"

#include "draw/draw.h"

#include "entity/entity.h"
#include "weapon/weapon.h"
#include "weapon/prediction.h"
#include "pattern/pattern.h"

#include "../modules/caching/caching.h"
#include "../modules/aimbot/aimbot.h"
#include "../modules/visuals/visuals.h"

inline uintptr_t forcejump;
inline CGlobalVars global_vars;
inline CClientState client_state;
inline CInput input;
inline CUserCmd usercmd;
inline CNetChan netchan;

inline Vector3 oAngles = Vector3{ 0,0,0 };