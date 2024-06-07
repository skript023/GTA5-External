#pragma once

#include <cstdint>

#pragma pack(push, 1)
class CutsceneManager
{
public:
	char pad_0000[0xC98]; //0x0000
	int m_end_cutscene; //0xC98
};
static_assert(sizeof(CutsceneManager) == 0xC9C, "CutsceneManager Not Sized Properly");
#pragma pack(pop)