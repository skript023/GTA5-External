#include "setting.h"
#include "imgui.h"
#include "script.hpp"
#include "utility/all.hpp"


namespace ellohim
{
    void setting::render_setting_menu()
    {
        if (ImGui::BeginTabItem("Setting"))
        {
            if (ImGui::Button("Skip Cutscene"))
            {
                ExtInterface m_cutscene(*g_pointers->m_cutscene_mgr, g_proxy->m_cutscene_mgr.get());
                m_cutscene.write(&m_cutscene.proxy->m_end_cutscene, 1);
            }
            ImGui::SameLine();
            if (ImGui::Button("Disconnect"))
            {
                network::disconnect();
            }

            if (ImGui::Button("Thread Test"))
            {
                g_thread_pool->push([] {
                    LOG(INFO) << "TEST 1 Before Sleep";
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    LOG(INFO) << "TEST 2 After Sleep for 1s";
                    });
            }
            ImGui::SameLine();
            if (ImGui::Button("Fiber Test"))
            {
                g_fiber_pool->queue_job([] {
                    LOG(INFO) << "TEST 1 Before Sleep";
                    script::get_current()->yield(std::chrono::milliseconds(1000));
                    LOG(INFO) << "TEST 2 After Sleep for 1s";
                    });
            }

            if (ImGui::Button("Read Player Health"))
            {
                for (int i = 0; i < 32; i++)
                {
                    if (auto net_player = (*g_pointers->m_network_player_mgr + 0x180) + (i * sizeof(uintptr_t)))
                    {
                        LOG(INFO) << std::uppercase << std::hex << g_process->read<uintptr_t>(net_player) << " Index : " << i << "Player id : " << PLAYER::PLAYER_ID();
                        if (!g_process->read<uintptr_t>(net_player)) continue;
                        auto m_player_info = g_process->read<uintptr_t>(net_player) + 0xA0;

                        ExtInterface m_playerinfo(m_player_info, g_proxy->m_player_info_proxy.get());
                        auto ped = m_playerinfo.read(&m_playerinfo.proxy->m_rockstar_id);
                        //if (i == PLAYER::PLAYER_ID()) LOG(INFO) << ped;
                    }
                }
            }

            if (ImGui::Button("Quit"))
            {
                g_running = false;
            }
            ImGui::EndTabItem();
        }
    }
}