#include "setting.h"
#include "imgui.h"
#include "script.hpp"


namespace ellohim
{
    void setting::render_setting_menu()
    {
        if (ImGui::BeginTabItem("Setting"))
        {
            if (ImGui::Button("Thread Test"))
            {
                g_thread_pool->push([] {
                    LOG(INFO) << "TEST 1";
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    LOG(INFO) << "TEST 2";
                    });
            }
            ImGui::SameLine(150);
            if (ImGui::Button("Fiber Test"))
            {
                g_fiber_pool->queue_job([] {
                    LOG(INFO) << "TEST 1";
                    script::get_current()->yield(std::chrono::milliseconds(1000));
                    LOG(INFO) << "TEST 2";
                    });
            }

            if (ImGui::Button("Quit"))
            {
                g_running = false;
            }
            ImGui::EndTabItem();
        }
    }
}