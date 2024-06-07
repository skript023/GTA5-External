#pragma once
#include "pointer.hpp"
#include "utility/enums.hpp"

namespace ellohim
{
	class pointers
	{
	public:
		explicit pointers();
		~pointers();
	public:
		pointer<uint64_t> m_ped_factory;
		pointer<uint64_t> m_script_globals;
		pointer<uint64_t> m_blip_list;
		pointer<uint64_t> m_script_program;
		pointer<uint64_t> m_network_player_mgr;
		pointer<uint64_t> m_script_local;
		pointer<uint64_t> m_replay_interface;
		pointer<uint64_t> m_blackout;
		pointer<bool> m_is_session_started;
		pointer<eGameState> m_game_state;
		pointer<uint64_t> m_cutscene_mgr;
		pointer<uint64_t> m_business_money;
		pointer<uint64_t> m_friend_list;
		pointer<int> m_total_friend;
		pointer<uint64_t> m_rid_joiner;
		pointer<uint64_t> m_player_gravity;
		pointer<uint64_t> m_nightvision;
		pointer<uint64_t> m_thermal_vision;
		pointer<float> m_ground_coord;
		pointer<float> m_ground_coord_2;
		pointer<uint64_t> m_player_crew;
		pointer<uint64_t> m_weather;
		pointer<uint64_t> m_waypoint;
		pointer<uint64_t> m_waypoint_2;
		pointer<uint64_t> m_defuse_event;
		pointer<uint64_t> m_censor_chat;
		pointer<uint64_t> m_viewport;
		pointer<uint64_t> m_pickup_data;
		pointer<uint64_t> m_is_dlc_present;
		pointer<uint64_t> m_posix_time;
		pointer<uint64_t> m_frame_count;
		// pointer<uint64_t> m_player_name_esp;
		// pointer<uint64_t> m_player_name_display;
		pointer<uint64_t> m_label_text;
		pointer<uint64_t> m_sound_loudness;
		pointer<uint64_t> m_hash_table;
		// pointer<uint64_t> original_rid;
		pointer<uint64_t> m_ped_aim;
		// pointer<uint64_t> explosive_ammo;
		// pointer<uint64_t> fire_ammo;
		// pointer<uint64_t> explosive_melee;
		// pointer<uint64_t> super_jump;
		pointer<uint64_t> player_aim;
		HWND m_hwnd;
		
	};

	inline pointers* g_pointers;
}