#pragma once

namespace ellohim
{
	class player_menu
	{
	public:
		static void render_player_tab();
	private:
		static inline bool godmode{};
		static inline bool auto_heal{};
		static inline bool infinite_mp{};
		static inline bool no_cooldown{};
		static inline bool infinite_buff{};
		static inline bool freeze_enemy{};
		static inline bool one_hit{};
		static inline bool infinite_potion{};
		static inline bool no_clip{};

		static inline char write_stat_name[64]{};
		static inline int write_integer_value{};
		static inline bool write_bool_value{};
		static inline float write_float_value{};

		static inline bool get_step{ false };
		static inline char read_stat_name[64]{};
		static inline int read_integer_value{};
		static inline char bool_to_text[10]{};
		static inline float read_float_value{};
		static inline int read_bool_value{};

	};

	inline static player_menu g_player;
}