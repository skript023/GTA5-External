#pragma once
#include "memory/process.hpp"
#include "classes/ped_factory.hpp"

namespace ellohim
{
	template <class Z>
	class ExtInterface
	{
	public:
		Z* proxy;
		uintptr_t ext;

		ExtInterface(uintptr_t ext, Z* ExtInterface)
		{
			this->ext = ext;
			this->proxy = ExtInterface;
		}

		template <typename T>
		T read(T* var)
		{
			//resolve offset dynamically
			uintptr_t offset = (uintptr_t)var - (uintptr_t)proxy;

			//add offset to get to member variable
			uintptr_t extAddr = g_process->read<uintptr_t>(ext) + offset;

			//Read it
			return g_process->read<T>(extAddr);
		}

		template <typename T>
		void write(T* var, T value)
		{
			uintptr_t offset = (uintptr_t)var - (uintptr_t)proxy;
			uintptr_t extAddr = g_process->read<uintptr_t>(ext) + offset;
			g_process->write(extAddr, value);
		}
	};

#define GET(obj, var) obj.read(&obj.proxy->var);
#define SET(obj, var, val) obj.write(&obj.proxy->var, val);
}

/*

//Create 1 local proxy object for all objects of type "playerent" to use
playerent* proxy_playerent = new playerent;

//Create interface between proxy and external object
ExtInterface<playerent> player(EvalPtr(hProc, 0x50f4f4, 0, 0), proxy_playerent);

auto health = GET(player, health);
SET(player, health, 1337);

//When member variable is a ptr to a class object you need to create more interfaces
auto weaponAddr = (uintptr_t)GET(player, pWeapon);
ExtInterface<weapon> gun(weaponAddr, new weapon);
auto ammoAddr = (uintptr_t)GET(gun, ammo);
auto ammo = EvalPtr(hProc, ammoAddr);

*/