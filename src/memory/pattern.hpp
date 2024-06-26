#pragma once
#include "common.hpp"
#define CHUNK_SIZE 0x1000

namespace ellohim 
{

	class pattern 
	{
		std::vector<std::optional<uint8_t>> compiled;
		std::string name;
		uintptr_t   address = 0;

	public:
		inline pattern(std::string name, std::string x) :
			name(name)
		{
			try
			{
				compile(x);
				scan();
				LOG(INFO) << name << " Found";
			}
			catch(const std::exception& e)
			{
				LOG(WARNING) << name << " not found";
			}
		}

		inline pattern(std::string name_, uintptr_t addr)
		{
			name = name_;
			address = addr;
		}

		void compile(const std::string& pat);

		pattern& scan();

		inline pattern add(size_t sigOffset)
		{
			return pattern(name, address + sigOffset);
		}

		inline pattern sub(size_t sigOffset)
		{
			return pattern(name, address - sigOffset);
		}

		pattern rip();

		inline operator std::uint64_t() const
		{
			return address;
		}
	};
};