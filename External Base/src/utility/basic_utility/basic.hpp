#pragma once
#include "script_global.hpp"

namespace ellohim
{
	namespace PLAYER
	{
		inline int PLAYER_ID()
		{
			return script_global(2703660).as<int>();
		}
	}

	namespace NETWORK
	{
		inline int GET_NETWORK_TIME()
		{
			return script_global(1574755).as<int>();
		}
	}
}