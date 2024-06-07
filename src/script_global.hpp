#pragma once
#include "common.hpp"
#include "memory/process.hpp"

namespace ellohim
{
	class script_global
	{
	public:
		explicit script_global(std::size_t index);

		script_global at(std::ptrdiff_t index);
		script_global at(std::ptrdiff_t index, std::size_t size);

		template <typename T>
		T as()
		{
			return g_process->read<T>(get());
		}

		template <typename T>
		void as(T value)
		{
			g_process->write(get(), value);
		}

	private:
		uintptr_t get();
		std::size_t m_index;
	};
}
