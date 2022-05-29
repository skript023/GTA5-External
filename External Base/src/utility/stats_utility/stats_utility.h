#pragma once

namespace ellohim::stats
{
	void stat_get_float(uint32_t Hash, float* outValue);
	void stat_get_int(uint32_t Hash, int* outValue);
	void stat_get_bool(uint32_t Hash, int* outValue);
	void stat_set_float(uint32_t Hash, int value);
	void stat_set_int(uint32_t Hash, int value);
	void stat_set_bool(uint32_t Hash, bool value);
}