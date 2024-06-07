#pragma once

#include <cstdint>
#include <basetsd.h>

#pragma pack(push, 1)

class CPlayerCrew
{
public:
	char pad_0000[8]; //0x0000
	uint64_t m_rockstar_id; //0x0008
	char pad_0010[24]; //0x0010
	uint32_t m_crew_id; //0x0028
	char pad_002C[43]; //0x002C
	char m_crew_tag[4]; //0x0057
	char pad_005B[117]; //0x005B
	bool m_active_crew; //0x00D0
	char* get_crew_tag(int& index) { return (m_crew_tag + (0xB8LL * index)); }
	bool get_active_crew(int& index) { return *(bool*)((DWORD64)this + 0xD0LL + (0xB8LL * index)); }
};
static_assert(sizeof(CPlayerCrew) == 0xD1);

#pragma pack(pop)