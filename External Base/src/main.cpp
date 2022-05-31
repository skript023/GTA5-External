#include "renderer.hpp"
#include "Functions.h"
#include "memory/process.hpp"
#include "pointers.hpp"
#include "common.hpp"
#include "file_manager.hpp"
#include "thread_pool.hpp"
#include "fiber_pool.hpp"
#include "script_mgr.hpp"
#include "features.hpp"
#include "utility/class_grabber.hpp"
#include "menu_settings.hpp"

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)

inline uint32_t find_game_id() 
{
	auto win = ellohim::functions::GetProcessId(ellohim::TargetProcess); //::FindWindowA("grcWindow", nullptr);
	if (!win) 
	{
		LOG(INFO) << "Cannot find game window";
	}
	return win;
}

int main()
{
	using namespace ellohim;

	//while (!FindWindow("grcWindow", "Grand Theft Auto V"))
		//Sleep(0);

	std::cout << R"kek(
 ______      _                        _   ____                 
|  ____|    | |                      | | |  _ \                
| |__  __  _| |_ ___ _ __ _ __   __ _| | | |_) | __ _ ___  ___ 
|  __| \ \/ / __/ _ \ '__| '_ \ / _` | | |  _ < / _` / __|/ _ \
| |____ >  <| ||  __/ |  | | | | (_| | | | |_) | (_| \__ \  __/
|______/_/\_\\__\___|_|  |_| |_|\__,_|_| |____/ \__,_|___/\___|
 )kek" << std::endl;

	std::filesystem::path base_dir = std::getenv("appdata");
	base_dir /= "External";

	auto file_manager_instance = std::make_unique<file_manager>(base_dir);

	auto logger_instance = std::make_unique<logger>(
		"Ellohim Template",
		file_manager_instance->get_project_file("./cout.log")
		);

	auto process_instance = std::make_unique<process>(find_game_id());
	LOG(INFO) << "Process initalized.";

	auto pointers_instance = std::make_unique<pointers>();
	LOG(INFO) << "Pointers initialized.";

	auto setting_instance = std::make_unique<menu_settings>();

	auto fiber_pool_instance = std::make_unique<fiber_pool>(10);
	LOG(INFO) << "Fiber pool initialized.";

	auto fiber_pool = std::make_unique<thread_pool>();
	LOG(INFO) << "Thread pool initialized.";

	auto thread_pool_instance = std::make_unique<thread_pool>();
	LOG(INFO) << "Thread pool initialized.";

	auto class_grabber_instance = std::make_unique<LoadClass>();
	LOG(INFO) << "Classes initialized.";

	auto renderer_instance = std::make_unique<renderer>();
	LOG(INFO) << "Renderer Initialized.";

	g_script_mgr.add_script(std::make_unique<script>(&features::script_func));
	LOG(INFO) << "Scripts registered.";

	while (g_running)
	{
		g_script_mgr.tick();
		if (g_process->is_running())
		{
			g_renderer->render_on_tick();
		}
		else
		{
			g_running = false;
		}

		Sleep(0);
	}

	g_script_mgr.remove_all_scripts();
	LOG(INFO) << "Scripts unregistered.";

	renderer_instance.reset();
	LOG(INFO) << "Renderer Uninitialized";

	process_instance.reset();
	LOG(INFO) << "Process uninitalized.";

	pointers_instance.reset();
	LOG(INFO) << "Pointers uninitialized.";

	class_grabber_instance.reset();
	LOG(INFO) << "Classes uninitialized.";

	fiber_pool_instance.reset();
	LOG(INFO) << "Fiber pool uninitialized.";

	thread_pool_instance->destroy();
	LOG(INFO) << "Destroyed thread pool.";

	thread_pool_instance.reset();
	LOG(INFO) << "Thread pool uninitialized.";

	setting_instance.reset();

	logger_instance.reset();
	file_manager_instance.reset();

	exit(0);
}