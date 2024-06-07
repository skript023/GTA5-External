#pragma once

#include <cstdint>

#pragma pack(push, 1)
class CHashTable
{
public:
	char pad_0000[0x2EB8]; //0x0000
	class CPedHashTable *m_ped_hash_table; //0x2EB8
};
static_assert(sizeof(CHashTable) == 0x2EC0);

class CPedHashTable
{
public:
	char pad_0000[0x8E0]; //0x0000
	uint32_t m_slod; //0x08E0
	char pad_08E4[0xC]; //0x08E4
	uint32_t m_slod_small; //0x08F0
	char pad_08F4[0xC]; //0x08F4
	uint32_t m_slod_large; //0x0900
};
static_assert(sizeof(CPedHashTable) == 0x904);
#pragma pack(pop)