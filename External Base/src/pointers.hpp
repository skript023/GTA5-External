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
		pointer<bool> m_is_session_started;
		pointer<uint64_t> m_ped_factory;
		pointer<uint64_t> m_script_globals;
		pointer<uint64_t> m_blip_list;
		pointer<uint64_t> m_network_player_mgr;
		pointer<uint64_t> m_script_local;
		pointer<uint64_t> m_replay_interface;
		pointer<uint64_t> m_blackout;
		pointer<eGameState> m_game_state;
		pointer<uint64_t> m_cutscene_mgr;
		pointer<uint64_t> m_business_money;
		pointer<uint64_t> m_total_friend;
		pointer<uint64_t> m_friend_list;
		pointer<uint64_t> m_nightvision;
		pointer<uint64_t> m_thermal_vision;
		pointer<uint64_t> m_ground_check;
		pointer<uint64_t> m_player_crew;
		
	};

	inline pointers* g_pointers;
}