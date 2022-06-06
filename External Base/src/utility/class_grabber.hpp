#pragma once
#include "external_class.hpp"

namespace ellohim
{
	class LoadClass;
	inline LoadClass* g_proxy{};

	class LoadClass
	{
	public:
		explicit LoadClass()
		{
			m_ped_proxy = std::make_unique<CPed>();
			m_player_info_proxy = std::make_unique<CPlayerInfo>();
			m_vehicle_proxy = std::make_unique<CVehicle>();
			m_game_settings = std::make_unique<GameSetting >();
			m_friend_list = std::make_unique<FriendList>();
			m_hash_table = std::make_unique<CPedHashTable>();
			m_cutscene_mgr = std::make_unique<CutsceneManager>();
			m_navigation = std::make_unique<CNavigation>();

			g_proxy = this;
		}
		~LoadClass()
		{
			m_ped_proxy.reset();
			m_player_info_proxy.reset();
			m_vehicle_proxy.reset();
			m_game_settings.reset();
			m_friend_list.reset();
			m_hash_table.reset();
			m_cutscene_mgr.reset();
			m_navigation.reset();

			g_proxy = nullptr;
		}
	public:
		std::unique_ptr<CPed> m_ped_proxy;
		std::unique_ptr<CPlayerInfo> m_player_info_proxy;
		std::unique_ptr<CVehicle> m_vehicle_proxy;
		std::unique_ptr<GameSetting> m_game_settings;
		std::unique_ptr<FriendList>m_friend_list;
		std::unique_ptr<CPedHashTable> m_hash_table;
		std::unique_ptr<CutsceneManager> m_cutscene_mgr;
		std::unique_ptr<CNavigation> m_navigation;
	};
}