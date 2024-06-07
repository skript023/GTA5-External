#include "pointers.hpp"
#include "memory/pattern.hpp"

namespace ellohim
{
	pointers::pointers():
        m_ped_factory(pattern("Ped Factory", "48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81").add(3).rip()),
        m_script_globals(pattern("Script Globals", "4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11").add(3).rip()),
        m_blip_list(pattern("Blip List", "4C 8D 05 ? ? ? ? 0F B7 C1").add(3).rip()),
        m_script_program(pattern("Script Program", "44 8B 0D ? ? ? ? 4C 8B 1D ? ? ? ? 48 8B 1D ? ? ? ? 41 83 F8 FF 74 3F 49 63 C0 42 0F B6 0C 18 81 E1").add(17).rip()),
        m_network_player_mgr(pattern("Network player manager", "48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 48 8B CF").add(3).rip()),
        m_script_local(pattern("Script Locals", "48 8B 05 ? ? ? ? 8B CF 48 8B 0C C8 39 59 68").add(3).rip()),
        m_replay_interface(pattern("Replay Interface", "48 8D 0D ? ? ? ? 48 8B D7 E8 ? ? ? ? 48 8D 0D ? ? ? ? 8A D8 E8 ? ? ? ? 84 DB 75 13 48 8D 0D ? ? ? ?").add(3).rip()),
        m_blackout(pattern("Blackout", "48 8B D7 48 8B CB E8 ? ? ? ? 40 38 35 ? ? ? ? 74 40").add(14).rip()),
        m_is_session_started(pattern("Is Session Started", "40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE").add(3).rip()),
        m_game_state(pattern("Game State", "83 3D ? ? ? ? ? 75 17 8B 43 20 25").add(2).rip().add(1)),
        m_cutscene_mgr(pattern("Cutscene Manager", "48 8B 0D ? ? ? ? 48 8B 01 48 FF 60 58").add(3).rip()),
        m_business_money(pattern("Money Indicator", "48 8D 05 ? ? ? ? 48 C1 E1 ? 48 03 C8 E8 ? ? ? ? 48 8B 5C").add(3).rip()),
        m_friend_list(pattern("Friend List", "48 03 0D ? ? ? ? E9 ? ? ? ? 48 8D 05").add(3).rip()),
        m_total_friend(pattern("Total Friend", "3B 0D ? ? ? ? 73 13").add(2).rip()),
        m_rid_joiner(pattern("RID Joiner", "48 8D BE ? ? ? ? 48 8B CF 0F 10 ? 41 8B C4")),
        m_player_gravity(pattern("Player Gravity", "F3 0F 10 05 ? ? ? ? F3 0F 11 82 ? ? ? ? 8A 05 ? ? ? ? 88 82").add(4).rip()),
        m_nightvision(pattern("Nightvision", "88 05 ? ? ? ? 48 85 FF 74 55 8A 05 ? ? ? ?").add(2).rip()),
        m_thermal_vision(pattern("Thermal Vision", "88 1D ? ? ? ? E8 ? ? ? ? 8B 05").add(2).rip()),
        m_ground_coord(pattern("Ground Check", "48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 15 ? ? ? ? 48 8D 0D ? ? ? ? F3 0F 10 15").add(3).rip().add(0x4A4)),
        m_ground_coord_2(pattern("Ground Check Alternative", "F3 0F 10 15 ? ? ? ? 44 8A CF E8 ? ? ? ? 48 8D 15").add(4).rip().add(4)),
        m_player_crew(pattern("Player Crew", "48 8D 05 ? ? ? ? 48 69 C9 ? ? ? ? 48 03 C8 E8 ? ? ? ? 48 83 C4 ? C3 48 89 ? ? ? 48 89 ? ? ? 57").add(3).rip()),
        m_weather(pattern("Weather", "8D 77 ? 0F B6 ? ? ? ? ? 48 8D ? ? 48 8D").sub(63).rip()),
        m_waypoint(pattern("Waypoint", "48 8D 05 ? ? ? ? 33 D2 48 89 50 F0 48 89 50 F8 48 89 10 48 89").add(3).rip().add(0x10)),
        m_waypoint_2(pattern("Waypoint Alternative", "74 1F F3 0F 10 05 ? ? ? ? F3 0F 11 03").add(6).rip()),
        m_defuse_event(pattern("Script Event", "48 83 EC 28 E8 ? ? ? ? 48 8B 0D ? ? ? ? 4C 8D 0D ? ? ? ? 4C 8D 05 ? ? ? ? BA 03")),
        m_censor_chat(pattern("Chat Censor", "E8 ? ? ? ? 83 F8 FF 75 B9").add(1).rip()),
        m_viewport(pattern("Viewport", "48 8B 15 ? ? ? ? 48 8D 2D ? ? ? ? 48 8B CD").add(3).rip()),
        m_pickup_data(pattern("Pickup Data", "48 8B 05 ? ? ? ? 48 8B 1C F8 8B").add(3).rip()),
        m_is_dlc_present(pattern("Is DLC Present", "48 89 5C 24 08 57 48 83 EC 20 81 F9")),
        m_posix_time(pattern("Game Time", "66 0F 6E 15 ? ? ? ? 48 8D 3D ? ? ? ? BA ? ? ? ? 48 8B CF 0F 5B").add(4).rip()),
        m_frame_count(pattern("Frame Count", "8B 15 ? ? ? ? 41 FF CF FF").add(2).rip()),
        // m_player_name_esp(pattern("Player Name Esp", "48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 83").add(3).rip().add(0x84)),
        // m_player_name_display(pattern("Player Name Display", "48 8D 05 ? ? ? ? 48 63 CB 48 8B D6 48 69 C9 ? ? ? ? 48 03 C8 E8 ? ? ? ? 84 C0 75 21").add(3).rip().add(0x14)),
        m_label_text(pattern("Label Text", "48 8D 0D ? ? ? ? 44 8B F2").add(3).rip().add(0x11F8)),
        m_sound_loudness(pattern("Sound Loudness", "48 8B 05 ? ? ? ? F3 0F 10 25 ? ? ? ? 0F 28 D0 33 C9").add(3).rip()),
        m_hash_table(pattern("Hash Table", "48 8B 05 ? ? ? ? 4C 8B 14 D0 EB 09 41 3B 0A 74 54 4D").add(3).rip()),
        // original_rid(pattern("Original RID", "48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 83").add(3).rip().add(8)),
        //m_zone_name(pattern("Zone Name", "48 8D ? ? ? ? ? B2 ? E8 ? ? ? ? 8B 0D ? ? ? ? 83 F9 ? 74 ? E8 ? ? ? ? 33 C9 E8 ? ? ? ? 84 DB 75 ? 48 8D ? ? ? ? ? E8 ? ? ? ? 84 C0 75 ? 8B 05 ? ? ? ? C1 E0 ? C1 F8 ? 83 E8 ? 83 F8 ? 77 ? 80 3D EE 4B 26 02").add(3).rip()),
        //m_street_name(pattern("Street Name", "48 8D ? ? ? ? ? B2 ? E8 ? ? ? ? 8B 0D ? ? ? ? 83 F9 ? 74 ? E8 ? ? ? ? 33 C9 E8 ? ? ? ? 84 DB 75 ? 48 8D ? ? ? ? ? E8 ? ? ? ? 84 C0 75 ? 8B 05 ? ? ? ? C1 E0 ? C1 F8 ? 83 E8 ? 83 F8 ? 77 ? 80 3D A3 84 26 02").add(3).rip()),
        m_ped_aim(pattern("Ped Aim", "48 8B 0D ? ? ? ? 48 85 C9 74 0C 48 8D 15 ? ? ? ? E8 ? ? ? ? 48 89 1D").add(3).rip()),
        // explosive_ammo(pattern("Explosive Ammo", "0F BA F1 0B EB 06").add(3)),
        // fire_ammo(pattern("Fire Ammo", "0F BA F1 0C EB 06").add(3)),
        // explosive_melee(pattern("Explosive Fist", "0F BA F1 0D EB 06").add(3)),
        // super_jump(pattern("Super Jump", "0F BA F1 0E EB 06").add(3)),
        player_aim(pattern("Aim Types", "48 8D 0D ? ? ? ? 48 63 C3 3B 14 81 0F 84 ? ? ? ? 41 B8 ? ? ? ? 8B CB").add(3).rip().add(12))
	{
                m_hwnd = FindWindow(nullptr, "Grand Theft Auto V");

		g_pointers = this;
	}

	pointers::~pointers()
	{
		g_pointers = nullptr;
	}
}