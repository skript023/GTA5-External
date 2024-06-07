#pragma once

#include <cstdint>

#pragma pack(push, 1)

class GameSetting
{
public:
	char pad_0000[48]; //0x000
	bool m_keyboard_light_effect; //0x030
	char pad_0031[3]; //0x031
	int32_t m_sfx_volume; //0x034
	char pad_0038[8]; //0x038
	int32_t m_output_setting; //0x040
	char pad_0044[4]; //0x044
	int32_t m_radio_station; //0x048
	char pad_004C[52]; //0x04C
	bool m_kill_effect; //0x080
	char pad_0081[3]; //0x081
	bool m_subtitle; //0x084
	char pad_0085[3]; //0x085
	int32_t m_radar_setting; //0x088
	bool m_hud_setting; //0x08C
	char pad_008D[3]; //0x08D
	bool m_crosshair_setting; //0x090
	char pad_0091[3]; //0x091
	int32_t m_reticular_setting; //0x094
	bool m_gps_setting; //0x098
	char pad_0099[3]; //0x099
	int32_t m_safe_zone; //0x09C
	char pad_00A0[460]; //0x0A0
	bool m_radar_expansion; //0x026C
	char pad_026D[3]; //0x026D
	bool m_over_head_display; //0x0270
};
static_assert(sizeof(GameSetting) == 0x271, "GameSetting is not properly sized");

#pragma pack(pop)