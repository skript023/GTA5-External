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

		static inline float crit_damage_p{};
		static inline float crit_damage_m{};
		static inline float crit_damage_a{};
		static inline float crit_damage_b{};
		static inline float crit_damage_c{};


		static inline int physical_attack{};
		static inline int magical_attack{};
		static inline int physical_deff{};
		static inline int magical_deff{};
		static inline float item_found{};


	};

	inline static player_menu g_player;
}