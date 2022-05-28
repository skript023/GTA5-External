#pragma once
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <iostream>
#include <dwmapi.h>
#include <d3d9.h>
#include <time.h>
#include <vector>
#include <thread>
#include <stack>

#include <chrono>
#include <atomic>
#include <optional>
#include <filesystem>
#include <fstream>
#include <map>

#include <logger.hpp>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dwmapi.lib")

inline std::atomic_bool g_running{ true };