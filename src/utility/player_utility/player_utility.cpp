#include "player_utility.h"
#include "utility/utility.hpp"
#include "utility/basic_utility/basic.hpp"
#include "menu_settings.hpp"
#include <script.hpp>

namespace ellohim::player
{
	void set_player_health(int Player, float Health)
	{
		if (auto local_ped = utility::get_player_ped(Player))
		{
			ExtInterface m_ped(local_ped, g_proxy->m_ped_proxy.get());
			m_ped.write(&m_ped.proxy->m_health, Health);
		}
	}

	void set_player_invincible(int Player, bool activate)
	{
		if (auto local_ped = utility::get_player_ped(Player))
		{
			ExtInterface m_ped(local_ped, g_proxy->m_ped_proxy.get());

			if (activate && !m_ped.is_bit_set(&m_ped.proxy->m_damage_bits, 8))
			{
				m_ped.set_bit(&m_ped.proxy->m_damage_bits, 8);
			}
			else if (!activate && m_ped.is_bit_set(&m_ped.proxy->m_damage_bits, 8))
			{
				m_ped.clear_bit(&m_ped.proxy->m_damage_bits, 8);
			}
		}
	}

	void set_player_wanted_level(int Player, int8_t wantedLevel)
	{
		if (auto local_ped = utility::get_player_info(Player))
		{
			ExtInterface m_ped(local_ped, g_proxy->m_player_info_proxy.get());
			m_ped.write(&m_ped.proxy->m_wanted_level, wantedLevel);
		}
	}

	rage::vector3 get_blip_coords(int BlipID, int BlipColor)
	{
		if (!g_pointers->m_blip_list) return rage::vector3{ 0, 0, 0 };

		for (int i = 1400; i > 3; i -= 3)
		{
			if (auto ptr = (*g_pointers->m_blip_list + (i * sizeof(int64_t))))
			{
				int icon_id = g_process->read<int>(ptr + 0x40);
				int color_id = g_process->read<int>(ptr + 0x48);
				if (icon_id == BlipID && BlipColor == NULL) BlipColor = color_id;
				if (icon_id == BlipID && color_id == BlipColor)
				{
					return g_process->read<rage::vector3>(ptr + 0x10);
				}
			}
		}
		return rage::vector3{ 0, 0, 0 };
	}

	void set_player_coords(int Player, rage::vector3 coords)
	{
		if (auto ped = utility::get_player_ped(Player))
		{
			g_fiber_pool->queue_job([=] {
				if (coords.x == 0.0 && coords.y == 0.0 && coords.z == 0.0) return;

				ExtInterface m_ped(ped, g_proxy->m_ped_proxy.get());

				if (m_ped.read(&m_ped.proxy->m_is_in_vehicle))
				{
					auto veh = (uintptr_t)m_ped.get(&m_ped.proxy->m_last_vehicle);

					ExtInterface m_veh(veh, g_proxy->m_vehicle_proxy.get());

					auto nav = (uintptr_t)m_veh.get(&m_veh.proxy->m_navigation);
					ExtInterface m_nav(veh, g_proxy->m_navigation.get());

					m_veh.set_bit(&m_veh.proxy->m_stop_vehicle, 0);

					script::get_current()->yield(250ms);

					m_veh.write(&m_veh.proxy->m_entity_position, coords);
					m_nav.write(&m_nav.proxy->m_position, coords);

					script::get_current()->yield(250ms);

					m_veh.clear_bit(&m_veh.proxy->m_stop_vehicle, 0);
				}
				else
				{
					auto navigation = (uintptr_t)m_ped.get(&m_ped.proxy->m_navigation);

					ExtInterface m_nav(navigation, g_proxy->m_navigation.get());
					g_process->write(g_pointers->m_player_gravity, NAN);
					m_ped.set_bit(&m_ped.proxy->m_invisible, 17);

					script::get_current()->yield(250ms);

					m_ped.write(&m_ped.proxy->m_entity_position, coords);
					m_nav.write(&m_nav.proxy->m_position, coords);

					script::get_current()->yield(350ms);

					g_process->write(g_pointers->m_player_gravity, -9.8f);
					m_ped.clear_bit(&m_ped.proxy->m_invisible, 17);
				}
			});
		}
	}

	void teleport_to_marker()
	{
		g_fiber_pool->queue_job([] {
			float Heights[]{ 200.0f, 150.0f, 100.0f, 50.0f, 1050.0f, 900.0f, 850.0f, 800.0f, 750.0f, 700.0f, 650.0f, 600.0f, 550.0f, 500.0f, 450.0f, 400.0f, 350.0f, 300.0f, 250.0f, 0.0f };
			rage::vector2 v2 = g_process->read<rage::vector2>(g_pointers->m_waypoint_2);
			float high = 1100.0f;
			float ground = 0.0f;

			ExtInterface m_ped(utility::get_local_ped(), g_proxy->m_ped_proxy.get());
			auto navigation = m_ped.get(&m_ped.proxy->m_navigation);
			ExtInterface m_nav(navigation, g_proxy->m_navigation.get());

			rage::vector3 v3(v2.x, v2.y, high);
			set_player_coords(PLAYER::PLAYER_ID(), v3);

			script::get_current()->yield(100ms);

			for (int i = 0; i <= _ARRAYSIZE(Heights); ++i)
			{
				LOG(INFO) << "Begin Ground : " << *g_pointers->m_ground_coord;
				if (!utility::is_float_equal(*g_pointers->m_ground_coord, 0.0f))
				{
					for (int j = 0; j <= _ARRAYSIZE(Heights); j++)
					{
						if (!utility::is_float_equal(*g_pointers->m_ground_coord, 0.0f))
						{
							set_player_coords(PLAYER::PLAYER_ID(), { v2.x, v2.y, *g_pointers->m_ground_coord + 1.2f });
							LOG(INFO) << "Ground : " << *g_pointers->m_ground_coord;
						}
						else
						{
							set_player_coords(PLAYER::PLAYER_ID(), { v2.x, v2.y, Heights[j] });
							LOG(INFO) << "Search Z Coords";
						}
						script::get_current()->yield();
					}

					set_player_coords(PLAYER::PLAYER_ID(), { v2.x, v2.y, *g_pointers->m_ground_coord + 1.2f });
					LOG(INFO) << "Finished";
					break;
				}
				else
				{
					if (i > 18) i = 0;
					high = Heights[i];
					set_player_coords(PLAYER::PLAYER_ID(), { v2.x, v2.y, high });
					LOG(INFO) << "Search Z Coords";
				}
				script::get_current()->yield();
			}
		});
	}

	void run_tick()
	{
		set_player_invincible(PLAYER::PLAYER_ID(), g_option->player.godmode);
	}
	
}