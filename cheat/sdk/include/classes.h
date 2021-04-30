#pragma once
#include "../common.h"

class bf_write
{
public:
	void* m_data; //0x0000
	int32_t m_dataBytes; //0x0008
	int32_t m_dataBits; //0x000C
	int32_t m_curBit; //0x0010
	bool m_overflow; //0x0014
	bool m_assertOnOverflow; //0x0015
	char pad_0016[2]; //0x0016
	char* m_debugName; //0x0018
}; //Size: 0x0020

struct CGlobalVars {
	/*0x00*/double realtime;
	/*0x08*/int32_t framecount;
	/*0x0c*/float absoluteframetime;
	/*0x10*/float curtime;
	/*0x14*/float curtime2;
	/*0x18*/float curtime3;
	/*0x1c*/float curtime4;
	/*0x20*/float frametime;
	/*0x24*/float curtime5;
	/*0x28*/float curtime6;
	/*0x2c*/float zero;
	/*0x30*/float frametime2;
	/*0x34*/int32_t maxClients;
	/*0x38*/int32_t unk38;
	/*0x3c*/int32_t unk3C;
	/*0x40*/int32_t tickcount;
	/*0x44*/float interval_per_tick;
	/*0x48*/float interpolation_amount;
	// There's more stuff after this but I don't know and I don't care
};

class CUtlMemory
{
public:
	void* m_memory; //0x0000
	int64_t m_allocationCount; //0x0008
	int64_t m_growSize; //0x0010
}; //Size: 0x0018

class CNetChan;

class CClientState
{
public:
	char pad_0000[96]; //0x0000
	class CNetChan* m_netChan; //0x0060
	char pad_0068[48]; //0x0068
	int32_t m_signonState; //0x0098
	char pad_009C[4]; //0x009C
	double m_nextCmdTime; //0x00A0
	uint32_t m_serverCount; //0x00A8
	uint32_t m_currentSequence; //0x00AC
	char pad_00B0[168]; //0x00B0
	int32_t m_deltaTick; //0x0158
	char pad_015C[12]; //0x015C
	uint32_t m_playerSlot; //0x0168
	char pad_016C[8]; //0x016C
	char m_mapFileName[64]; //0x0174
	char m_levelNameShort[64]; //0x01B4
	char m_levelName[260]; //0x01F4
	char pad_02F8[4]; //0x02F8
	int32_t m_highestClientIndex; //0x02FC
	char pad_0300[64]; //0x0300
	int32_t m_maxClients; //0x0340
	char pad_0344[100748]; //0x0344
	int32_t m_lastUsedCommandNr; //0x18CD0
	char pad_18CD8[60]; //0x18CD8
	Vector3 m_viewAngles; //0x18D18
	char gimmeMore[0x1000];
}; //Size: 0x18D24

class CNetChan
{
public:
	char pad_0000[4]; //0x0000
	uint32_t m_outSeqNr; //0x0004
	uint32_t m_inSeqNr; //0x0008
	uint32_t m_outSeqNrAck; //0x000C
	uint32_t m_chokedCommands; //0x0010
	char pad_0014[16]; //0x0014
	int32_t m_socket; //0x0024
	char pad_0028[8]; //0x0028
	bf_write m_streamReliable; //0x0030
	CUtlMemory m_reliableDataBuffer; //0x0050
	bf_write m_streamUnreliable; //0x0068
	CUtlMemory m_unreliableDataBuffer; //0x0088
	bf_write m_streamVoice; //0x00A0
	CUtlMemory m_voiceDataBuffer; //0x00C0
	char pad_00D8[4]; //0x00D8
	uint32_t m_maxReliablePayloadSize; //0x00DC
	double m_lastReceived; //0x00E0
	double m_connectTime; //0x00E8
	int32_t m_rate; //0x00F0
	char pad_00F4[4]; //0x00F4
	double m_clearTime; //0x00F8
	char pad_0100[8]; //0x0100
	int32_t m_signonState; //0x0108 only display 4 and 8
	char pad_010C[108]; //0x010C
	CClientState* m_clientState; //0x0178
	char pad_0180[64]; //0x0180
	void* m_sendBuffer; //0x01C0
	bf_write m_sendStream; //0x01C8
}; //Size: 0x01E8

class CUserCmd//CInput::DecodeUserCmdFromBuffer
{
public:
	int           command_number;
	int           tick_count;
	float         command_time;
	Vector3       viewangles;
	BYTE          _pad0[0x14];
	float         forwardmove;
	float         sidemove;
	float         upmove;
	int           buttons;
	BYTE          impulse;
	BYTE          _pad1[492];
};

class CVerifiedUserCmd : public CUserCmd
{
public:
	uint64_t m_crc64; //0x01F8
}; //Size: 0x0200

class CInput
{
public:
	char pad_0000[32]; //0x0000
	float m_frametime; //0x0020
	float m_prevFrametime; //0x0024
	char pad_0028[136]; //0x0028
	uint32_t m_buttonBits; //0x00B0
	char pad_00B4[8]; //0x00B4
	float m_pingHoldStartTime; //0x00BC
	float m_somethingPing; //0x00C0 0.0 when not pinging.
	char pad_00C4[11]; //0x00C4
	bool m_cameraIsOrthographic; //0x00CF
	Vector3 m_previousViewAngles; //0x00D0
	char pad_00DC[12]; //0x00DC
	float m_lastForwardMove; //0x00E8 -1.0 -> 1.0
	int32_t m_clearInputState; //0x00EC
	CUserCmd* m_commands; //0x00F0 // Does not change or go null
	CVerifiedUserCmd* m_verifiedCommands; //0x00F8 // Does not change or go null
}; //Size: 0x0100

enum class WeaponID : int {
	BARE_HANDS = 14,

	HAVOC = 64,
	LSTAR = 65,

	KRABER = 54,
	MASTIFF = 55,
	DEVOTION = 48,

	SENTINEL = 1,
	CHARGE_RIFLE = 66,
	LONGBOW = 49,
	TRIPLE_TAKE = 62,

	WINGMAN = 63,
	SPITFIRE = 61,
	PROWLER = 57,
	HEMLOK = 53,
	FLATLINE = 51,

	RE45 = 47,
	P2020 = 60,
	R301 = 0,
	R99 = 59,
	ALTERNATOR = 46,
	G7_SCOUT = 52,

	MOZAMBIQUE = 56,
	PEACEKEEPER = 58,
	EVA8_AUTO = 50,
};
enum class HelmetID : int {
	HELMET_LV0,
	HELMET_LV1,
	HELMET_LV2,
	HELMET_LV3,
	HELMET_LV4,
};
enum class ArmorID : int {
	BODY_ARMOR_LV0,
	BODY_ARMOR_LV1,
	BODY_ARMOR_LV2,
	BODY_ARMOR_LV3,
	BODY_ARMOR_LV4,
};
enum class ItemID : int {
	DeathBox = 0,
	KRABER_HEIRLOOM = 1,
	MASTIFF = 2,
	MASTIFF_GOLD = 3,
	LSTAR = 7,
	LSTAR_GOLD = 8,
	HAVOC = 12,
	HAVOC_GOLD = 13,
	DEVOTION = 18,
	DEVOTION_GOLD = 19,
	TRIPLE_TAKE = 24,
	TRIPLE_TAKE_GOLD = 25,
	FLATLINE = 29,
	FLATLINE_GOLD = 30,
	HEMLOK = 34,
	HEMLOK_GOLD = 35,
	G7_SCOUT = 39,
	G7_SCOUT_GOLD = 40,
	ALTERNATOR = 45,
	ALTERNATOR_GOLD = 46,
	R99 = 51,
	R99_GOLD = 52,
	PROWLER_HEIRLOOM = 56,
	VOLT = 61,
	VOLT_GOLD = 62,
	LONGBOW = 66,
	LONGBOW_GOLD = 67,
	CHARGE_RIFLE = 71,
	CHARGE_RIFLE_GOLD = 72,
	SPITFIRE = 76,
	SPITFIRE_GOLD = 77,
	R301 = 81,
	R301_GOLD = 82,
	EVA8_AUTO = 86,
	EVA8_AUTO_GOLD = 87,
	PEACEKEEPER_HEIRLOOM = 91,
	MOZAMBIQUE = 92,
	MOZAMBIQUE_GOLD = 93,
	WINGMAN = 98,
	WINGMAN_GOLD = 99,
	P2020 = 104,
	P2020_GOLD = 105,
	RE45 = 110,
	RE45_GOLD = 111,
	SENTINEL = 116,
	SENTINEL_GOLD = 117,
	Repeater = 121,
	Repeater_GOLD = 122,

	LIGHT_ROUNDS = 126,
	ENERGY_AMMO,
	SHOTGUN_SHELLS,
	HEAVY_ROUNDS,
	SNIPER_AMMO,

	ULTIMATE_ACCELERANT,
	PHOENIX_KIT,
	MED_KIT,
	SYRINGE,
	SHIELD_BATTERY,
	SHIELD_CELL,

	HELMET_LV1,
	HELMET_LV2,
	HELMET_LV3,
	HELMET_LV4,
	BODY_ARMOR_LV1,
	BODY_ARMOR_LV2,
	BODY_ARMOR_LV3,
	BODY_ARMOR_LV4,
	EVO_SHIELD_LV0,
	EVO_SHIELD_LV1,
	EVO_SHIELD_LV2,
	EVO_SHIELD_LV3,
	EVO_SHIELD_LV4,
	KNOCKDOWN_SHIELD_LV1,
	KNOCKDOWN_SHIELD_LV2,
	KNOCKDOWN_SHIELD_LV3,
	KNOCKDOWN_SHIELD_LV4,
	BACKPACK_LV1,
	BACKPACK_LV2,
	BACKPACK_LV3,
	BACKPACK_LV4,

	THERMITE_GRENADE,
	FRAG_GRENADE,
	ARC_STAR,

	HCOG_CLASSIC,
	HCOG_BRUISER,
	HOLO,
	VARIABLE_HOLO,
	DIGITAL_THREAT,
	HCOG_RANGER,
	VARIABLE_AOG,
	SNIPER,
	VARIABLE_SNIPER,
	DIGITAL_SNIPER_THREAT,

	BARREL_STABILIZER_LV1,
	BARREL_STABILIZER_LV2,
	BARREL_STABILIZER_LV3,
	BARREL_STABILIZER_LV4,
	LIGHT_MAGAZINE_LV1,
	LIGHT_MAGAZINE_LV2,
	LIGHT_MAGAZINE_LV3,
	HEAVY_MAGAZINE_LV1,
	HEAVY_MAGAZINE_LV2,
	HEAVY_MAGAZINE_LV3,
	ENERGY_MAGAZINE_LV1,
	ENERGY_MAGAZINE_LV2,
	ENERGY_MAGAZINE_LV3,
	SNIPER_MAGAZINE_LV1,
	SNIPER_MAGAZINE_LV2,
	SNIPER_MAGAZINE_LV3,
	SHOTGUN_BOLT_LV1,
	SHOTGUN_BOLT_LV2,
	SHOTGUN_BOLT_LV3,
	STANDARD_STOCK_LV1,
	STANDARD_STOCK_LV2,
	STANDARD_STOCK_LV3,
	SNIPER_STOCK_LV1,
	SNIPER_STOCK_LV2,
	SNIPER_STOCK_LV3,

	TURBOCHARGER,
	SKULLPIERCER_RIFLING,
	HAMMERPOINT_ROUNDS,
	DOUBLE_TAP_TRIGGER,
	HOPUP_187,
	QUICKDRAW_HOLSTER,
	VAULT_KEY,
	MOBILE_RESPAWN_BEACON,
	ITEM_191,
	TREASURE_PACK,
};