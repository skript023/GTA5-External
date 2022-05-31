#include "features.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "utility/all.hpp"


namespace ellohim::features
{
	void run_per_tick()
	{
		player::run_tick();
	}

	void script_func()
	{
		while (true)
		{
			try 
			{
				if (*g_pointers->m_game_state == eGameState::Playing)
					features::run_per_tick();
			}
			catch (std::exception const& ex)
			{
				LOG(INFO) << ex.what();
			}
			script::get_current()->yield();
		}
	}
}
