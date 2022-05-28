#include "common.hpp"
#include "pointers.hpp"
#include "script_local.hpp"

namespace ellohim
{
	script_local::script_local(uint64_t stack, std::size_t index) :
		m_index(index), m_stack(stack)
	{
	}

	script_local script_local::at(std::ptrdiff_t index)
	{
		return script_local(m_stack, m_index + index);
	}

	script_local script_local::at(std::ptrdiff_t index, std::size_t size)
	{
		return script_local(m_stack, m_index + 1 + (index * size));
	}

	uintptr_t script_local::get()
	{
		return g_process->read<uintptr_t>(m_stack) + (m_index * sizeof(uintptr_t*));
	}
}
