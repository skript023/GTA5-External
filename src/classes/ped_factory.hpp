#pragma once
#include "player.hpp"
#include "utility/vector.hpp"

#pragma pack(push, 1)

class CPed : public fwEntity
{
public:
	char pad_02A4[4]; //0x02A4
	void* m_attackers; //0x02A8
	char pad_02B0[112]; //0x02B0
	rage::vector3 m_velocity; //0x0320
	char pad_032C[2532]; //0x032C
	class CVehicle* m_last_vehicle; //0x0D10
	char pad_0D18[314]; //0x0D18
	bool m_is_in_vehicle; //0x0E52
	char pad_0E53[613]; //0x0E53
	uint8_t m_ragdoll; //0x10B8
	char pad_10B9[3]; //0x10B9
	int8_t m_decal_index; //0x10BC
	int8_t m_decal_info; //0x10BD
	char pad_10BE[2]; //0x10BE
	class UnknownPlayer* m_unk_player; //0x10C0
	class CPlayerInfo* m_playerinfo; //0x10C8
	class CPedInventory* m_weapon_inventory; //0x10D0
	class CPedWeaponManager* m_weapon_mgr; //0x10D8
	char pad_10E0[892]; //0x10E0
	uint8_t seatbelt; //0x145C
	char pad_145D[16]; //0x145D
	int m_ped_task; //ox146D
	char pad_1471[191]; //0x1471
	float m_armor; //0x1530

};	//Size: 0x14E4
static_assert(sizeof(CPed) == 0x1534, "CPed is not properly sized");
#pragma pack(pop)

class CPedFactory
{
public:
	virtual ~CPedFactory() = default;
	class CPed *m_local_ped;
};

class PresenceData
{
public:
	virtual ~PresenceData() = default; // 0 (0x00)
	virtual bool updateIntegerAttribute(uint32_t alwaysZero, const char* attributeName, int64_t attr) = 0; // 1 (0x08)
	virtual bool _0x10(unsigned int a2, int64_t a3) = 0; // 2 (0x10)
	virtual bool updateStringAttribute(uint32_t alwaysZero, const char* attributeName, const char* str) = 0; // 3 (0x18)
	virtual bool _0x20(unsigned int a2, int64_t a3, uint64_t* a4) = 0; // 4 (0x20)
	virtual bool _0x28(unsigned int a2, int64_t a3, uint64_t* a4) = 0; // 5 (0x28)
	virtual bool _0x30(unsigned int a2, int64_t a3, uint8_t* a4, unsigned int a5) = 0; // 6 (0x30)
	virtual bool _0x38() = 0; // 7 (0x38)
	virtual bool _0x40() = 0; // 8 (0x40)
	virtual bool _0x48() = 0; // 9 (0x48)
	virtual bool _0x50() = 0; // 10 (0x50)
	virtual bool _0x58() = 0; // 11 (0x58)
	virtual bool _0x60(unsigned __int8 a2) = 0; // 12 (0x60)
	virtual bool _0x68(uint8_t* a2) = 0; // 13 (0x68)
	virtual bool _0x70(unsigned __int8 a2) = 0; // 14 (0x70)
	virtual bool _0x78(uint8_t* a2) = 0; // 15 (0x78)
	virtual bool _0x80(unsigned int a2, int64_t a3, unsigned int a4) = 0; // 16 (0x80)
	virtual bool _0x88(unsigned int a2, int64_t a3, unsigned int a4) = 0; // 17 (0x88)
	virtual bool _0x90(int a2) = 0; // 18 (0x90)
	virtual bool _0x98() = 0; // 19 (0x98)
	virtual bool _0xa0(uint8_t* a2) = 0; // 20 (0xa0)
	virtual bool _0xa8(unsigned __int8 a2) = 0; // 21 (0xa8)
	virtual bool _0xb0(int64_t a2, int64_t a3) = 0; // 22 (0xb0)
	virtual bool _0xb8() = 0; // 23 (0xb8)
	virtual bool _0xc0(int64_t a2) = 0; // 24 (0xc0)
	virtual bool _0xc8() = 0; // 25 (0xc8)
};