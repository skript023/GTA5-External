#pragma once
#include "pointers.hpp""
#include "joaat.hpp"
#include "script_global.hpp"
#include "address.hpp"

namespace ellohim::utility
{
	inline auto find_script_thread(rage::joaat_t scriptHash) -> uintptr_t
	{
		auto a = g_pointers->m_script_local;
		for (int i = 0; i <= 52; i++)
		{
			auto p = g_process->read<uint64_t>(g_process->read<uint64_t>(a) + (i * 0x8));
			int m_stack = g_process->read<int>(p + 0xB0);
			uint32_t m_hash = g_process->read<uint32_t>(p + 0xC);
			if (m_hash == NULL)
				continue;
			else if (m_hash == scriptHash && m_stack != 0)
				return p + 0xB0;
			return false;
		}
	}

	inline int character()
	{
		return *script_global(g_global.character).as<int*>();
	}
}

namespace ellohim::memory
{
	static inline bool is_bit_set(uintptr_t _value, int _bit)
	{
		auto value = g_process->read<int>(_value);
		if ((value >> _bit) & 1) return true;
		return false;
	}

	static inline int set_bit(uintptr_t _value, int _bit)
	{
		auto value = g_process->read<int>(_value);
		return value |= 1 << _bit;
	}

	static inline int clear_bit(uintptr_t _value, int _bit)
	{
		auto value = g_process->read<int>(_value);
		return value &= ~(1 << _bit);
	}

	static inline bool is_bit_set(script_global _value, int _bit)
	{
		if ((_value.as<int>() >> _bit) & 1LL) return true;
		return false;
	}

	static inline void set_bit(script_global _value, int _bit)
	{
		auto value = _value.as<int>() | 1 << _bit;
		_value.as(value);
	}

	static inline int clear_bit(script_global _value, int _bit)
	{
		auto value = _value.as<int>() & ~(1 << _bit);
		_value.as(value);
	}
}