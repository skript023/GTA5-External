#pragma once

namespace ellohim::network
{
	void no_idle_kick(bool activation);
	void select_character();
	void creator_mode();
	void off_the_radar(bool activate);
	void reveal_player(bool activate);
	void blind_cops(bool activate);
	void disconnect();
	void change_session(int sessionId);
}