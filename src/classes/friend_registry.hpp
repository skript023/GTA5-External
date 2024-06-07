#pragma once

#include <cstdint>

#pragma pack(push, 1)

class FriendInfo
{
public:
	char pad_0000[128]; //0x0000
	char m_name[20]; //0x0080
	char pad_0094[36]; //0x0094
	uint64_t m_friend_id; //0x00B8
	char pad_00C0[4]; //0x00C0
	int32_t m_friend_status; //0x00C4
	char pad_00C8[304]; //0x00C8
	bool m_is_multiplayer; //0x01F8
	char pad_01F9[7]; //0x01F9
}; //Size: 0x0200
static_assert(sizeof(FriendInfo) == 0x200);

class FriendList
{
public:
	class FriendInfo m_friend_info[128];
	const char* get_friend_name(int index) { return m_friend_info[index].m_name; }
	const char* get_friend_status(int index) 
	{
		bool is_multiplayer = m_friend_info[index].m_is_multiplayer;
		int status = m_friend_info[index].m_friend_status;
		bool is_single_player = status >> 1 & 1;
		bool is_online = status & 1;
		return is_multiplayer ? "Multiplayer" : is_single_player ? "Single Player" : is_online ? "Online" : "Offline";
	}

	uint64_t get_friend_id(int index) { return m_friend_info[index].m_friend_id; }
	uint64_t* set_friend_id(int index) { return &m_friend_info[index].m_friend_id; }
};

#pragma pack(pop)