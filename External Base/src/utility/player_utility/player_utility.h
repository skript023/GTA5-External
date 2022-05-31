#pragma once

namespace ellohim::player
{
	void set_player_health(int Player, float Health);
	void set_player_invincible(int Player, bool activate);
	void set_player_wanted_level(int Player, int8_t wantedLevel);

	void run_tick();
}