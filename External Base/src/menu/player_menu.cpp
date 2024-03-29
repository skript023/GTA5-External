#include "player_menu.h"
#include "imgui.h"
#include "utility/all.hpp"
#include "menu_settings.hpp"

namespace ellohim
{
    void player_menu::render_player_tab()
    {
        if (ImGui::BeginTabItem("Player Option"))
        {
            auto end = std::chrono::system_clock::now();
            std::time_t date = std::chrono::system_clock::to_time_t(end);

            ImGui::Text("%s", std::ctime(&date));

            ImGui::Checkbox("Godmode", &g_option->player.godmode);

            if (ImGui::Button("Set Max Health"))
            {
                player::set_player_health(PLAYER::PLAYER_ID(), 328.f);
            }

            if (ImGui::Button("Teleport to Waypoint"))
            {
                player::teleport_to_marker();
            }
            
            if (ImGui::SliderInt("Wanted Level", &wanted, 0, 5))
            {
                player::set_player_wanted_level(PLAYER::PLAYER_ID(), wanted);
            }

            if (ImGui::CollapsingHeader("Stat Editor"))
            {
                static int e = 0;
                ImGui::RadioButton("Integer", &e, 0);
                ImGui::SameLine();
                ImGui::RadioButton("Bool", &e, 1);
                ImGui::SameLine();
                ImGui::RadioButton("Float", &e, 2);
                
                ImGui::InputText("##Stat Name", write_stat_name, IM_ARRAYSIZE(write_stat_name), ImGuiInputTextFlags_CharsUppercase);

                switch (e)
                {
                case 0:
                    ImGui::InputScalar("##Integer", ImGuiDataType_S64, &write_integer_value);
                    break;
                case 1:
                    ImGui::Checkbox("##BoolValue", &write_bool_value);
                    break;
                case 2:
                    ImGui::InputScalar("##Float", ImGuiDataType_Float, &write_float_value);
                    break;
                }

                if (ImGui::Button("Write Stat"))
                {
                    strcpy(write_stat_name, std::regex_replace(write_stat_name, std::regex(R"(\$)"), "").c_str());
                    strcpy(write_stat_name, std::regex_replace(write_stat_name, std::regex(R"(\MPX)"), "MP" + std::to_string(utility::character())).c_str());
                    strcpy(write_stat_name, std::regex_replace(write_stat_name, std::regex(R"(\MPx)"), "MP" + std::to_string(utility::character())).c_str());
                    const auto stat_hash = rage::joaat(write_stat_name);

                    switch (e)
                    {
                    case 0:
                        stats::stat_set_int(stat_hash, write_integer_value);
                        break;
                    case 1:
                        stats::stat_set_bool(stat_hash, write_bool_value);
                        break;
                    case 2:
                        stats::stat_set_float(stat_hash, write_float_value);
                        break;
                    }
                }


                ImGui::Separator();
                static int r = 0;
                ImGui::Text("Read Stat");
                ImGui::RadioButton("Integer##Read", &r, 0);
                ImGui::SameLine();
                ImGui::RadioButton("Bool##Read", &r, 1);
                ImGui::SameLine();
                ImGui::RadioButton("Float##Read", &r, 2);

                ImGui::InputText("##ReadStat", read_stat_name, IM_ARRAYSIZE(read_stat_name), ImGuiInputTextFlags_CharsUppercase);

                switch (r)
                {
                case 0:
                    ImGui::InputInt("##Get Int", &read_integer_value, 1, 100, ImGuiInputTextFlags_ReadOnly);
                    if (ImGui::IsItemHovered())
                        ImGui::SetTooltip("Value of the stat");
                    break;
                case 1:
                    ImGui::InputText("##Get Bool", bool_to_text, IM_ARRAYSIZE(bool_to_text), ImGuiInputTextFlags_ReadOnly);
                    if (ImGui::IsItemHovered())
                        ImGui::SetTooltip("Value of the stat");
                    break;
                case 2:
                    ImGui::InputFloat("##Get Float", &read_float_value, 0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_ReadOnly);
                    if (ImGui::IsItemHovered())
                        ImGui::SetTooltip("Value of the stat");
                    break;
                }
                if (ImGui::Button("Read Stat"))
                {
                    strcpy(read_stat_name, std::regex_replace(read_stat_name, std::regex(R"(\$)"), "").c_str());
                    strcpy(read_stat_name, std::regex_replace(read_stat_name, std::regex(R"(\MPX)"), "MP" + std::to_string(utility::character())).c_str());
                    strcpy(read_stat_name, std::regex_replace(read_stat_name, std::regex(R"(\MPx)"), "MP" + std::to_string(utility::character())).c_str());
                    const auto stat_hash = rage::joaat(read_stat_name);

                    switch (r)
                    {
                    case 0:
                        stats::stat_get_int(stat_hash, &read_integer_value);
                        break;
                    case 1:
                        strcpy(bool_to_text, stats::stat_get_bool(stat_hash) ? "True" : "False");
                        break;
                    case 2:
                        stats::stat_get_float(stat_hash, &read_float_value);
                        break;
                    }
                }
                ImGui::Separator();


            }

            

            ImGui::EndTabItem();
        }
    }
}