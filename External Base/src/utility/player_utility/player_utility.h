#pragma once
#include "utility/vector.hpp"

namespace ellohim::player
{
	void set_player_health(int Player, float Health);
	void set_player_invincible(int Player, bool activate);
	void set_player_wanted_level(int Player, int8_t wantedLevel);
	void teleport_to_marker();
	rage::vector3 get_blip_coords(int BlipID, int BlipColor = NULL);
	void set_player_coords(int Player, rage::vector3 coords);

	void run_tick();
}