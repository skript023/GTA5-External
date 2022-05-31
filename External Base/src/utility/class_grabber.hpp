#pragma once
#include "external_class.hpp"

namespace ellohim
{
	class LoadClass;
	inline LoadClass* g_class{};

	class LoadClass
	{
	public:
		explicit LoadClass():
			m_ped_proxy(new CPed),
			m_player_info_proxy(new CPlayerInfo)
		{
			g_class = this;
		}
		~LoadClass()
		{
			delete m_ped_proxy;
			delete m_player_info_proxy;
			g_class = nullptr;
		}
	public:
		CPed* m_ped_proxy;
		CPlayerInfo* m_player_info_proxy;
	};
}