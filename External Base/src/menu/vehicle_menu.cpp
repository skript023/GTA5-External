#include "vehicle_menu.h"
#include "imgui.h"
#include "utility/network_utility/network_utility.h"


namespace ellohim
{
    void enhancement_menu::render_enhacement_menu()
    {
        if (ImGui::BeginTabItem("Enhancement"))
        {
            ImGui::Text("Enhancement Effect Changer");
            ImGui::Combo("##Auto Area", &current_enhancement, enhancement_list, IM_ARRAYSIZE(enhancement_list));
            if (ImGui::Button("Change Effect"))
            {
                
            }
            ImGui::SameLine();
            if (ImGui::Button("Disable Effect"))
            {

            }

            ImGui::Checkbox("Add 100% enhancement rate", &enhancement_success);
            ImGui::Checkbox("No Fuel Required", &no_fuel);
            ImGui::Checkbox("Always Protected", &no_vaccine);

            if (ImGui::Button("Add 100% Enhancement Buff"))
            {

            }

            ImGui::EndTabItem();
        }
    }
}