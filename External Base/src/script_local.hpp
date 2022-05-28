#pragma once
#include "common.hpp"
#include "utility/joaat.hpp"

namespace ellohim
{
	class script_local
	{
	public:
		explicit script_local(uint64_t stack, std::size_t index);

		script_local at(std::ptrdiff_t index);
		script_local at(std::ptrdiff_t index, std::size_t size);

		template <typename T>
		T as()
		{
			return g_process->read<T>(get());
		}

		template <typename T>
		void as(T value = NULL)
		{
			return g_process->write(get(), value);
		}
	private:
		uintptr_t get();
		std::size_t m_index;
		uint64_t m_stack;
	};
}
