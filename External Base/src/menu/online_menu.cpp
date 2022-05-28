#include "online_menu.h"
#include "imgui.h"
#include "common.hpp"
#include <script.hpp>
#include "utility/all.hpp"

namespace ellohim
{
	void online_menu::render_online_menu()
	{
        if (ImGui::BeginTabItem("Online Option"))
        {
            ImGui::Combo("##Session List", &selected_session, session_list, IM_ARRAYSIZE(session_list));

            if (ImGui::Button("Go"))
            {
                switch (selected_session)
                {
                case 0:
                    network::change_session(0);
                    break;
                case 1:
                    network::change_session(1);
                    break;
                case 2:
                    network::change_session(2);
                    break;
                case 3:
                    network::change_session(3);
                    break;
                case 4:
                    network::change_session(6);
                    break;
                case 5:
                    network::change_session(9);
                    break;
                case 6:
                    network::change_session(10);
                    break;
                case 7:
                    network::change_session(11);
                    break;
                case 8:
                    network::change_session(12);
                    break;
                case 9:
                    network::change_session(13);
                    break;
                case 10:
                    network::change_session(-1);
                    break;
                }
            }
            
            ImGui::SameLine();
            if (ImGui::Button("Choose Character"))
            {
                network::select_character();
            }
            ImGui::SameLine();
            if (ImGui::Button("Creator Mode"))
            {
                network::creator_mode();
            }
            ImGui::Separator();

            ImGui::EndTabItem();
        }
	}
}