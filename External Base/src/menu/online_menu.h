#pragma once

namespace ellohim
{
	class online_menu
	{
	public:
		static void render_online_menu();
	private:
		static inline int selected_session{0};
		static inline const char* const session_list[]{ "Join Public Session", "New Public Session", "Closed Crew Session", "Crew Session","Closed Friend Session", "Find Friend Session","Solo Session", "Invite Only Session","Join Crew Session", "Join SCTV", "Leave GTA Online" };

	};

}