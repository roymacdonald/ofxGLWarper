
#ifdef ofxAddons_ENABLE_IMGUI
#include "ofxGLWarperImGui.h"
#include "imgui.h"

namespace ImGuiEx {
    namespace ofxGLWarper {
        // Duplicated from : ofxSimpleApp/ofxSimpleAppUtils.cpp
        bool DragPad2(const char* label, ImVec2& vec){
            // Calc some dimensions
            ImGui::Text("%s", label); ImGui::SameLine();
            ImVec2 availableSpace = { ImGui::GetContentRegionAvail().x, ImGui::GetFrameHeight() };
            bool ret = false;
            availableSpace.x -= availableSpace.y + (ImGui::GetStyle().ItemSpacing.x*2.f);// + (ImGui::GetStyle().ItemInnerSpacing.x*4.f);

            ImGui::PushID(label);
            ImGui::SetNextItemWidth(availableSpace.x*.5f);
            if(ImGui::DragFloat("##x", &vec.x, 1.f, 0.f, 10000, "%1.0f")){
                ret = true;
            }
            ImGui::SameLine();
            ImGui::SetNextItemWidth(availableSpace.x*.5f);
            if(ImGui::DragFloat("##y", &vec.y, 1.f, 0.f, 10000, "%1.0f")){
                ret = true;
            }
            ImGui::SameLine();

            static ImVec2 mousePos;
            static ImVec2 fromValue;
            static void* beingDragged = nullptr;
            static bool isDragging;
            isDragging = label == beingDragged;
            if(isDragging) ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetColorU32(ImGuiCol_ButtonActive)); // Force-Mark active (unhovered+active is not "held" state)
            ImGui::Button("+##dragBtn", {availableSpace.y, availableSpace.y});
            if(isDragging) ImGui::PopStyleColor();
            if(isDragging){
                if(ImGui::IsItemDeactivated()){
                    beingDragged = nullptr;
                    ret = true;
                }
                else if(ImGui::IsItemActive()){
                    ret = true; // Indicates an updated value while dragging (make this optional)
                    vec = fromValue + (ImGui::GetMousePos() - mousePos);
                }
            }
            else if(ImGui::IsItemClicked()){
                mousePos = ImGui::GetMousePos();
                fromValue = vec;
                beingDragged = (void*) label;
            }
            ImGui::PopID();
            return ret;
        }
    }
}

//using namespace ImGuiEx::ofxGLWarper;

//--------------------------------------------------------------
ofxGLWarperImGui::~ofxGLWarperImGui(){
    ofxGLWarper::deactivate();
}

//--------------------------------------------------------------
bool ofxGLWarperImGui::isEnabled() const {
    return bEnableQuadWarper;
}

//--------------------------------------------------------------
void ofxGLWarperImGui::drawImGuiWidget(ofRectangle resetDimension){
    ImGui::SeparatorText("Quad Wrapping");
    ImGui::SameLine();
    if(ImGui::BeginCombo("##options", nullptr, ImGuiComboFlags_NoPreview)){
        ImGui::SeparatorText("Edit options");
        ImGui::Checkbox("Draw outline", &drawSettings.bDrawRectangle);
        ImGui::Checkbox("Draw corners", &drawSettings.bDrawCorners);
        ImGui::EndCombo();
    }
    ImGui::Checkbox("Enable Quad Wrapping", &bEnableQuadWarper);
    static bool bEnableQuadEditing = false;
    if(ImGui::Checkbox("Enable Editing Mode", &bEnableQuadEditing)){
        activate(bEnableQuadEditing); // to enable event listeners for easily configuring the quads
    }
    ImGui::Text("Quads :");
    if(!resetDimension.isEmpty()){
        ImGui::SameLine();
        if(ImGui::Button("Reset")){
            setup(0, 0, resetDimension.getWidth(), resetDimension.getHeight());
        }
    }
    ImGui::SameLine();
    if(ImGui::Button("Save")){
        save();
    }
    ImGui::SameLine();
    if(ImGui::Button("Load")){
        load();
    }
    static std::pair<const char*, ofxGLWarper::CornerLocation> cornerModes[4] = {
        { "TL", ofxGLWarper::TOP_LEFT},
        { "TR", ofxGLWarper::TOP_RIGHT},
        { "BR", ofxGLWarper::BOTTOM_RIGHT},
        { "BL", ofxGLWarper::BOTTOM_LEFT}
    };
    for(auto& cornerMode : cornerModes){
        ImVec2 corner = getCorner(cornerMode.second);
        if(ImGuiEx::ofxGLWarper::DragPad2(cornerMode.first, corner)){
            setCorner(cornerMode.second, corner);
        }
    }
}
#endif
