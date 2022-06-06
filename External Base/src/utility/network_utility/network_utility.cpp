#include "network_utility.h"
#include "script_global.hpp"
#include "script.hpp"
#include "utility/all.hpp"

namespace ellohim::network
{
	void call_service_vehicle(int vehicle)
	{
		switch (vehicle)
		{
		case 0:
			script_global(g_global.terorbyte).as(1);
			break;
		case 1:
			script_global(g_global.kosatka).as(1);
			break;
		case 2:
			script_global(g_global.avanger).as(1);
			break;
		case 3:
			script_global(g_global.moc).as(1);
			break;
		case 4:
			script_global(g_global.dinghy).as(1);
			break;
		}
	}

	void instant_nano_drone()
	{
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			auto addr_drone = script_global(g_global.drone);
			memory::set_bit(addr_drone, 2);
			memory::set_bit(addr_drone, 22);
			memory::set_bit(addr_drone, 23);
			memory::set_bit(addr_drone, 24);
			script::get_current()->yield(std::chrono::milliseconds(200));
			memory::clear_bit(addr_drone, 2);
			memory::clear_bit(addr_drone, 22);
			memory::clear_bit(addr_drone, 23);
		} QUEUE_JOB_END_CLAUSE
	}

	void no_idle_kick(bool activation)
	{
		if (activation)
		{
			script_global(262145).at(87).as(INT32_MAX);
			script_global(262145).at(88).as(INT32_MAX);
			script_global(262145).at(89).as(INT32_MAX);
			script_global(262145).at(90).as(INT32_MAX);
		}
		else if (!activation)
		{
			script_global(262145).at(87).as(120000);
			script_global(262145).at(88).as(300000);
			script_global(262145).at(89).as(600000);
			script_global(262145).at(90).as(900000);
		}
	}

	void select_character()
	{
		script_global(g_global.session_unk_1).as(0);
		script_global(g_global.session_change).at(2).as(0);
		script_global(g_global.session_change).as(65);
		script_global(g_global.session_unk_2).as(1);
		script_global(g_global.session_unk_3).as(4);
	}

	void creator_mode()
	{
		script_global(g_global.session_unk_1).as(2);
		script_global(g_global.session_change).as(2);
		script_global(g_global.session_change).as(1);
	}

	void off_the_radar(bool activate)
	{
		if (activate && *g_pointers->m_is_session_started)
		{
			script_global(g_global.radar_toggle).at(PLAYER::PLAYER_ID(), g_global.radar_size).at(g_global.radar_offset).as(1);
			script_global(g_global.radar_time).at(70).as(NETWORK::GET_NETWORK_TIME());
			script_global(2544210).at(4628).as(4);
		}
		else if (!activate && *g_pointers->m_is_session_started)
		{
			script_global(g_global.radar_toggle).at(PLAYER::PLAYER_ID(), g_global.radar_size).at(g_global.radar_offset).as(0);
			script_global(g_global.radar_time).at(70).as(0);
			script_global(2544210).at(4628).as(0);
		}
	}

	void reveal_player(bool activate)
	{
		if (activate && *g_pointers->m_is_session_started)
		{
			script_global(g_global.radar_toggle).at(PLAYER::PLAYER_ID(), g_global.radar_size).at(212).as(1);
			script_global(g_global.radar_time).at(71).as(NETWORK::GET_NETWORK_TIME());
		}
		else if (!activate && *g_pointers->m_is_session_started)
		{
			script_global(g_global.radar_toggle).at(PLAYER::PLAYER_ID(), g_global.radar_size).at(212).as(0);
			script_global(g_global.radar_time).at(71).as(0);
		}
	}

	void blind_cops(bool activate)
	{
		if (activate && *g_pointers->m_is_session_started)
		{
			script_global(g_global.blind_cops).at(g_global.blind_cops_offset).as(1);
			script_global(g_global.blind_cops).at(g_global.blind_cops_offset).at(2).as(NETWORK::GET_NETWORK_TIME());
			script_global(g_global.blind_cops).at(g_global.blind_cops_offset - 1).as(5);
		}
		else if (!activate && *g_pointers->m_is_session_started)
		{
			script_global(g_global.blind_cops).at(g_global.blind_cops_offset).as(0);
			script_global(g_global.blind_cops).at(g_global.blind_cops_offset).at(2).as(0);
			script_global(g_global.blind_cops).at(g_global.blind_cops_offset - 1).as(0);
		}
	}

	void disconnect()
	{
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			script_global(g_global.disconnect).as(1);
			script::get_current()->yield(std::chrono::milliseconds(5000));
			script_global(g_global.disconnect).as(0);
		} QUEUE_JOB_END_CLAUSE
	}

	void change_session(int sessionId)
	{
		QUEUE_JOB_BEGIN_CLAUSE(=)
		{
			if (sessionId == -1)
			{
				script_global(1574589).at(2).as(-1);
				script_global(1574589).as(1);
				script::get_current()->yield(std::chrono::milliseconds(200));
				script_global(1574589).as(0);
				script_global(2676084).as(false);
			}
			else if (sessionId == 13)
			{
				script_global(1575012).as(sessionId);
				script_global(1574589).as(1);
				script::get_current()->yield(std::chrono::milliseconds(200));
				script_global(1574589).as(0);
				script_global(2676084).as(true);
			}
			else
			{
				script_global(1575012).as(sessionId);
				script_global(1574589).as(1);
				script::get_current()->yield(std::chrono::milliseconds(200));
				script_global(1574589).as(0);
				script_global(2676084).as(false);
			}
		} QUEUE_JOB_END_CLAUSE
	}
}