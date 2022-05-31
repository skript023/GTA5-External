#include "player_utility.h"
#include "utility/utility.hpp"
#include "utility/basic_utility/basic.hpp"
#include "menu_settings.hpp"

namespace ellohim::player
{
	void set_player_health(int Player, float Health)
	{
		if (auto local_ped = utility::get_player_ped(Player))
		{
			ExtInterface m_ped(local_ped, g_class->m_ped_proxy);
			m_ped.write(&m_ped.proxy->m_health, Health);
		}
	}

	void set_player_invincible(int Player, bool activate)
	{
		if (auto local_ped = utility::get_player_ped(Player))
		{
			ExtInterface m_ped(local_ped, g_class->m_ped_proxy);
			auto address = m_ped.read(&m_ped.proxy->m_damage_bits);
			if (activate && !memory::is_bit_set(address, 8))
			{
				m_ped.write(&m_ped.proxy->m_damage_bits, memory::set_bit(address, 8));
			}
			else if (!activate && memory::is_bit_set(address, 8))
			{
				m_ped.write(&m_ped.proxy->m_damage_bits, memory::clear_bit(address, 8));
			}
		}
	}

	void set_player_wanted_level(int Player, int8_t wantedLevel)
	{
		if (auto local_ped = utility::get_player_info(Player))
		{
			ExtInterface m_ped(local_ped, g_class->m_player_info_proxy);
			m_ped.write(&m_ped.proxy->m_wanted_level, wantedLevel);
		}
	}

	void run_tick()
	{
		set_player_invincible(PLAYER::PLAYER_ID(), g_option->player.godmode);
	}
	
}