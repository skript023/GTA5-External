#pragma once

namespace ellohim
{
	class menu_settings;
	inline menu_settings* g_option{};

	class menu_settings
	{
		struct player_option
		{
			bool godmode = false;
		};
	public:
		explicit menu_settings()
		{
			g_option = this;
		}

		~menu_settings()
		{
			g_option = nullptr;
		}
		player_option player{};
	

	};
}