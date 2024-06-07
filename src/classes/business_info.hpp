#pragma once

#include <cstdint>

#pragma pack(push, 1)
class BusinessMoney
{
public:
	char pad_0000[0x128];
	int32_t total_money;//0x0128
};
static_assert(sizeof(BusinessMoney) == 0x12C);
#pragma pack(pop)