#pragma once
#include "pointers.hpp""
#include "joaat.hpp"
#include "script_global.hpp"
#include "address.hpp"
#include "class_grabber.hpp"

namespace ellohim::utility
{
	inline auto find_script_thread(rage::joaat_t scriptHash) -> uintptr_t
	{
		for (int i = 0; i <= 52; i++)
		{
			auto p = g_process->read<uint64_t>(*g_pointers->m_script_local + (i * 0x8));
			int m_stack = g_process->read<int>(p + 0xB0);
			uint32_t m_hash = g_process->read<uint32_t>(p + 0xC);

			if (m_hash == NULL)
				continue;
			else if (m_hash == scriptHash && m_stack != 0)
				return p + 0xB0;
		}
		return false;
	}

	inline int character()
	{
		return script_global(g_global.character).as<int>();
	}

	inline uintptr_t get_player_ped(int player)
	{
		if (*g_pointers->m_is_session_started)
		{
			auto net_player = (*g_pointers->m_network_player_mgr + 0x180) + (player * sizeof(uintptr_t));
			if (g_process->read<uintptr_t>(net_player))
			{
				if (auto m_player_info = g_process->read<uintptr_t>(net_player) + 0xA0)
				{
					auto ped = g_process->read<uintptr_t>(m_player_info) + 0x1E8;
					return ped;
				}
			}
		}
		else if (!*g_pointers->m_is_session_started)
		{
			return (*g_pointers->m_ped_factory + 0x8);
		}
		return NULL;
	}

	inline uintptr_t get_player_info(int Player)
	{
		if (uintptr_t m_ped = get_player_ped(Player))
		{
			if (auto playerinfo = g_process->read<uintptr_t>(m_ped) + 0x10C8)
			{
				return playerinfo;
			}
		}
		return NULL;
	}

	inline uintptr_t get_local_ped()
	{
		if (auto m_ped = (*g_pointers->m_ped_factory + 0x8))
		{
			return m_ped;
		}
		return NULL;
	}

	inline bool is_float_equal(float a, float b, float epsilon = FLT_EPSILON)
	{
		return (fabs(a - b) <= epsilon * std::max(fabs(a), fabs(b)));
	}
}

namespace ellohim::memory
{
	inline bool is_bit_set(uintptr_t _value, int _bit)
	{
		auto value = g_process->read<int>(_value);
		if ((value >> _bit) & 1) return true;
		return false;
	}

	inline int set_bit(uintptr_t _value, int _bit)
	{
		auto value = g_process->read<int>(_value);
		return value |= 1 << _bit;
	}

	inline int clear_bit(uintptr_t _value, int _bit)
	{
		auto value = g_process->read<int>(_value);
		return value &= ~(1 << _bit);
	}

	inline bool is_bit_set(script_global _value, int _bit)
	{
		if ((_value.as<int>() >> _bit) & 1) return true;
		return false;
	}

	inline void set_bit(script_global _value, int _bit)
	{
		auto value = _value.as<int>() | 1 << _bit;
		_value.as(value);
	}

	inline void clear_bit(script_global _value, int _bit)
	{
		auto value = _value.as<int>() & ~(1 << _bit);
		_value.as(value);
	}

	template <typename T>
	inline bool is_bit_set(T _value, int _bit)
	{
		if ((_value >> _bit) & 1LL) return true;
		return false;
	}

	template <typename T>
	inline T set_bit(T _value, int _bit)
	{
		return _value |= 1 << _bit;
	}

	template <typename T>
	inline T clear_bit(T _value, int _bit)
	{
		return _value &= ~(1 << _bit);
	}
}