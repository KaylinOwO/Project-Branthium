#include "sdk/common.h"
bool ShowMenu = false;

void RunModules() {
	auto EntityCachePlayerList = CachedPlayerList;
	float ClosestDistance = FLT_MAX;
	uint64_t ClosestEntityToCrosshair = NULL;
	int ClosestEntityIndex = -1;

	static float rainbow;
	rainbow += 0.005f;
	if (rainbow > 1.f)
		rainbow = 0.f;
	DrawOutlinedText(m_pFont, XorStr("Project Branthium"), ImVec2(65, 25), 12, ImColor::HSV(rainbow, 1.f, 1.f), true);
	DrawOutlinedText(m_pFont, XorStr("by waxxyTF2"), ImVec2(65 * 2 + 20, 25), 12, IM_COL32(255, 255, 255, 255), true);

	if (!EntityCachePlayerList.empty()) {
		for (unsigned long i = 0; i < EntityCachePlayerList.size(); ++i)
		{
			EntityCache entity = EntityCachePlayerList[i];
			uint64_t localent = read<uint64_t>(oBaseAddress + OFFSET_LOCAL_ENT);
			if (!localent) continue;

			if (entity.player_entity != 0)
			{
				if (entity.player_entity != localent && entity::GetTeam(entity.player_entity) != entity::GetTeam(localent) && entity::IsAlive(entity.player_entity)) 
				{
					gVisuals.PlayerESP(entity.player_entity, localent);
					if (vars::aim::enabled && entity::IsAlive(localent)) {
						QAngle angle = gAim.GetAimAngle(entity.player_entity);
						if (angle != QAngle(0, 0, 0))
						{
							float fov = GetFov(entity::GetViewAnglesA(localent), angle);
							if (fov < vars::aim::fov && fov < ClosestDistance) {
								ClosestDistance = fov;
								ClosestEntityToCrosshair = entity.player_entity;
								ClosestEntityIndex = entity.player_id;
							}
						}
					}
				}
			}
		}
	}

	gAim.Run(ClosestEntityToCrosshair, gAim.GetAimAngle(ClosestEntityToCrosshair), ClosestEntityIndex);
}

void RunSoftware() {
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		ShowMenu = !ShowMenu;
		Sleep(1);
	}

	if (ShowMenu)
	{
		ImGui::PushFont(m_pFont2);
		{
			if (ImGui::Begin(XorStr("Project Branthium"), 0, ImVec2(572, 500), -1.f, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse)) {

				static short tab = 0;

				if (ImGui::Button(XorStr("Aimbot"), ImVec2(265, 25)))
					tab = 0;

				ImGui::SameLine();

				if (ImGui::Button(XorStr("Visuals"), ImVec2(265, 25)))
					tab = 1;

				if (tab == 0) {

					ImGui::Checkbox(XorStr("Aimbot##toggle"), &vars::aim::enabled);
					ImGui::Checkbox(XorStr("Bullet Prediction"), &vars::aim::bullet_prediction);
					ImGui::Text("Aim Key"); ImGui::SameLine(); ImGui::Combo(XorStr("##AimkeyC"), &vars::aim::key, aimkeys, sizeof(aimkeys) / sizeof(*aimkeys));
					ImGui::Text("Bone"); ImGui::SameLine(); ImGui::Combo(XorStr("##BoneC"), &vars::aim::bone, hitboxes, sizeof(hitboxes) / sizeof(*hitboxes));
					ImGui::Text("Recoil Removal"); ImGui::SameLine(); ImGui::Combo(XorStr("##RecoilRC"), &vars::aim::no_recoil, recoilremoval, sizeof(recoilremoval) / sizeof(*recoilremoval));
					ImGui::Text("FOV"); ImGui::SameLine(); ImGui::SliderFloat(XorStr("##FOVS"), &vars::aim::fov, 1.0f, 180.0f);
					ImGui::Checkbox(XorStr("Smooth"), &vars::aim::smooth);
					ImGui::Text("Smoothing"); ImGui::SameLine(); ImGui::SliderFloat(XorStr("##SmoothS"), &vars::aim::smoothing, 2.0f, 20.0f);
				}

				if (tab == 1) {

					ImGui::Checkbox(XorStr("ESP"), &vars::visuals::enabled);
					ImGui::Checkbox(XorStr("Player Name"), &vars::visuals::players::name);
					ImGui::Checkbox(XorStr("Player Health"), &vars::visuals::players::health);
					ImGui::Checkbox(XorStr("Player Shield"), &vars::visuals::players::shield);
					ImGui::Checkbox(XorStr("Player Distance"), &vars::visuals::players::distance);
					ImGui::Checkbox(XorStr("Player Glow"), &vars::visuals::players::glow);
					ImGui::Text("Distance Limit"); ImGui::SameLine();  ImGui::SliderFloat(XorStr("##pdisancelimit"), &vars::visuals::players::distancelimit, 1, 1501);
				}
			}
		}
		ImGui::PopFont();
		ImGui::End();
	}

	RunModules();

	ImGui::EndFrame();
	D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
	D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0,0,0, 0), 1.0f, 0);

	if (D3dDevice->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		D3dDevice->EndScene();
	}
	HRESULT result = D3dDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		D3dDevice->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

MSG Message = { NULL };
void Loop()
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, Window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();

		if (hwnd_active == hwnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(Window, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		if (GetAsyncKeyState(0x23) & 1)
			exit(8);

		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(hwnd, &rc);
		ClientToScreen(hwnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = hwnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = (float)p.x - (float)xy.x;
		io.MousePos.y = (float)p.y - (float)xy.y;

		if (GetAsyncKeyState(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;
			wLeft = rc.left;
			wTop = rc.top;

			d3dpp.BackBufferWidth = Width;
			d3dpp.BackBufferHeight = Height;
			SetWindowPos(Window, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			D3dDevice->Reset(&d3dpp);
		}
		RunSoftware();
		//Sleep(1);
	//	
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	DestroyWindow(Window);
}

int main()
{	
	while (hwnd == NULL)
	{
		printf(XorStr("Please open Apex Legends..."));
		Sleep(50);
		system("cls");
		auto wind = XorStr("Apex Legends");
		hwnd = FindWindowA(0, wind);
		Sleep(100);
	}

	oPID = GetPID(XorStr("r5apex.exe"));
	if (oPID == 0)
	{
		printf(XorStr("Failed to get PID!\n"));
		Sleep(3000);
		return 0;
	}

	oBaseAddress = GetModuleBaseAddress(XorStr("r5apex.exe"));
	if (oBaseAddress == 0)
	{
		printf(XorStr("Failed to get base address!\n"));
		Sleep(3000);
		return 0;
	}

	printf(XorStr("Running...\n"));

	global_vars = read<CGlobalVars>(oBaseAddress + OFFSET_GLOBALVARS);

	max_clients = global_vars.maxClients;
	curtime = global_vars.curtime;
	interval_per_tick = global_vars.interval_per_tick;

	CreateOWindow();
	InitializeD3D();

	std::thread PlayerCacheThread(PlayerCache);

	Loop();
	Shutdown();

	return 0;
}