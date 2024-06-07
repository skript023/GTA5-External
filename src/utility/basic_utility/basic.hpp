#pragma once
#include "script_global.hpp"

namespace ellohim
{
	namespace PLAYER
	{
		inline int PLAYER_ID()
		{
			return script_global(2703660).at(4).at(16).as<int>(); //Global_2703660
		}

		inline uintptr_t PLAYER_PED_ID()
		{
			return ((*g_pointers->m_ped_factory) + 0x8);
		}
	}

	namespace NETWORK
	{
		inline int GET_NETWORK_TIME()
		{
			return script_global(1574755).at(11).as<int>(); //Global_1574755
		}
	}
}