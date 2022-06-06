#include "stats_utility.h"
#include "script_global.hpp"
#include "script_local.hpp"
#include "utility/all.hpp"
#include "script.hpp"

namespace ellohim::stats
{
	void stat_get_float(uint32_t Hash, float* outValue)
	{
		QUEUE_JOB_BEGIN_CLAUSE(Hash, outValue)
		{
			if (auto freemode = utility::find_script_thread(RAGE_JOAAT("freemode")))
			{
				uint32_t original_hash = script_global(g_global.get_float_stat).at(37, 3).at(utility::character(), 1).as<uint32_t>();

				script_global(g_global.get_float_stat).at(37, 3).at(utility::character(), 1).as(Hash);
				script_local(freemode, m_local.get_float_trigger).as(9);
				script_global(g_global.get_float_trigger).as(1);

				
				script::get_current()->yield(1000ms);

				*outValue = script_global(g_global.player_stat).at(PLAYER::PLAYER_ID(), g_global.player_size).at(g_global.player_offset).at(57).as<float>();
				
				script_global(g_global.get_float_stat).at(37, 3).at(utility::character(), 1).as(Hash);
			}
		} QUEUE_JOB_END_CLAUSE
	}
	void stat_get_int(uint32_t Hash, int* outValue)
	{
		QUEUE_JOB_BEGIN_CLAUSE(Hash, outValue)
		{
			script_global(g_global.get_int_stat).at(1090, 3).at(utility::character(), 1).as(Hash);
			script_global(g_global.get_int_trigger).as(15);
			script::get_current()->yield(1000ms);
			*outValue = script_global(g_global.get_int_value).as<int>();
		} QUEUE_JOB_END_CLAUSE
	}
	void stat_get_bool(uint32_t Hash, int* outValue)
	{
		uint32_t og_hash = script_global(g_global.get_bool_stat).at(130, 3).at(utility::character(), 1).as<uint32_t>();
		script_global(g_global.get_bool_stat).at(130, 3).at(utility::character(), 1).as(Hash);

		*outValue = memory::is_bit_set(script_global(g_global.player_stat).at(PLAYER::PLAYER_ID(), g_global.player_size).at(g_global.player_offset).at(49).as<int>(), 0);//MISC::SET_BIT(&(Global_1853131[bVar0 /*888*/].f_205.f_49), false);

		script_global(g_global.get_bool_stat).at(130, 3).at(utility::character(), 1).as(og_hash);
	}
	bool stat_get_bool(uint32_t Hash)
	{
		uint32_t og_hash = script_global(g_global.get_bool_stat).at(130, 3).at(utility::character(), 1).as<uint32_t>();
		script_global(g_global.get_bool_stat).at(130, 3).at(utility::character(), 1).as(Hash);

		bool result = memory::is_bit_set(script_global(g_global.player_stat).at(PLAYER::PLAYER_ID(), g_global.player_size).at(g_global.player_offset).at(49).as<int>(), 0);//MISC::SET_BIT(&(Global_1853131[bVar0 /*888*/].f_205.f_49), false);

		script_global(g_global.get_bool_stat).at(130, 3).at(utility::character(), 1).as(og_hash);

		return result;
	}
	void stat_set_float(uint32_t Hash, int value)
	{
		g_fiber_pool->queue_job([Hash, value]
		{
			int mpx = utility::character();
			static const auto backup_hash_86 = script_global(g_global.get_float_stat).at(86, 3).at(mpx, 1).as<uint32_t>();
			static const auto backup_hash_816 = script_global(g_global.get_int_stat).at(819, 3).at(mpx, 1).as<uint32_t>();
			static const auto backup_hash_1210 = script_global(g_global.get_int_stat).at(1210, 3).at(mpx, 1).as<uint32_t>();

			int no_bought_yum_snacks;
			int no_bought_health_snacks;
			stat_get_int(rage::joaat("MP" + std::to_string(mpx) + "_NO_BOUGHT_YUM_SNACKS"), &no_bought_yum_snacks);
			stat_get_int(rage::joaat("MP" + std::to_string(mpx) + "_NO_BOUGHT_HEALTH_SNACKS"), &no_bought_health_snacks);

			script::get_current()->yield(100ms);
			script_global(g_global.get_float_stat).at(86, 3).at(mpx, 1).as<int>(Hash);
			script_global(g_global.get_int_stat).at(819, 3).at(mpx, 1).as(rage::joaat("MP" + std::to_string(mpx) + "_NO_BOUGHT_YUM_SNACKS"));
			script_global(g_global.get_int_stat).at(1210, 3).at(mpx, 1).as(rage::joaat("MP" + std::to_string(mpx) + "_NO_BOUGHT_HEALTH_SNACKS"));

			stat_set_int(rage::joaat("MP" + std::to_string(mpx) + "_NO_BOUGHT_YUM_SNACKS"), 100);
			stat_set_int(rage::joaat("MP" + std::to_string(mpx) + "_NO_BOUGHT_HEALTH_SNACKS"), value);

			script_global(g_global.get_int_trigger).as(21);
			script::get_current()->yield(1000ms);
			script_global(g_global.get_float_stat).at(86, 3).at(mpx, 1).as(backup_hash_86);
			script_global(g_global.get_int_stat).at(819, 3).at(mpx, 1).as(backup_hash_816);
			script_global(g_global.get_int_stat).at(1210, 3).at(mpx, 1).as(backup_hash_1210);

			stat_set_int(rage::joaat("MP" + std::to_string(mpx) + "_NO_BOUGHT_YUM_SNACKS"), no_bought_yum_snacks);
			stat_set_int(rage::joaat("MP" + std::to_string(mpx) + "_NO_BOUGHT_HEALTH_SNACKS"), no_bought_health_snacks);

		});
	}
	void stat_set_int(uint32_t Hash, int value)
	{
		g_fiber_pool->queue_job([Hash, value]
		{
			script_global(g_global.set_int_stat).at(3, 1).as(Hash);
			script::get_current()->yield(800ms);
			script_global(g_global.set_float_trigger).as(3);
			script_global(g_global.set_int_trigger).as(3);
			script_global(g_global.set_int_value).as(value);
		});
	}
	void stat_set_bool(uint32_t Hash, bool value)
	{
		g_fiber_pool->queue_job([Hash, value]
		{
			script_global(g_global.set_bool_stat).at(205, 3).at(utility::character(), 1).as(Hash);
			script::get_current()->yield(1200ms);
			auto shop_controller = utility::find_script_thread(rage::joaat("shop_controller"));
			script_local(shop_controller, m_local.set_bool_value).as(value); //#2994561506 67
		});
	}
}


/*
Write Float Stat 1.60
void func_17815(int iParam0, int iParam1, int iParam2)
{
	int iVar0;
	int iVar1;
	float fVar2;

	iVar0 = func_20812(iParam0, -1, 0);
	iVar1 = func_20812(iParam1, -1, 0);
	fVar2 = (SYSTEM::TO_FLOAT(iVar0) / SYSTEM::TO_FLOAT(iVar1));
	fVar2 = (fVar2 * 100f);
	if (func_709(iParam2, -1) != fVar2)
	{
		func_7333(iParam2, fVar2, -1, 1);
	}
}

*/