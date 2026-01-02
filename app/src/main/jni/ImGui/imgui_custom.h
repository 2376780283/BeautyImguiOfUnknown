#include <vector>
#include <random>
#include <map>
#include <array>
#include <cmath>
#include <functional>
#include <memory>
#include <string>

inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
inline ImVec2 operator*(const ImVec2& lhs, float rhs) { return ImVec2(lhs.x * rhs, lhs.y * rhs); }
inline ImVec2 operator/(const ImVec2& lhs, float rhs) { return ImVec2(lhs.x / rhs, lhs.y / rhs); }
inline ImVec2& operator+=(ImVec2& lhs, const ImVec2& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
inline ImVec2 operator*(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
inline ImVec2& operator*=(ImVec2& lhs, float rhs) { lhs.x *= rhs; lhs.y *= rhs; return lhs; }

inline ImVec4 operator*(const ImVec4& lhs, float rhs) { return ImVec4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs); }
inline ImVec4 operator*(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }
inline ImVec4 operator+(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
inline ImVec4 operator-(const ImVec4& lhs, const ImVec4& rhs) { return ImVec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }

inline float ImLength(const ImVec2& vec) { return sqrtf(vec.x * vec.x + vec.y * vec.y); }
inline bool operator<(const ImVec4& lhs, const ImVec4& rhs) { return lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z && lhs.w < rhs.w; }
inline bool operator>(const ImVec4& lhs, const ImVec4& rhs) { return lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z && lhs.w > rhs.w; }
inline float ImClamp(float v, float mn, float mx) { return v < mn ? mn : (v > mx ? mx : v); }
inline ImVec4 ImClamp(const ImVec4& v, const ImVec4& mn, const ImVec4& mx) { return ImVec4(ImClamp(v.x, mn.x, mx.x),ImClamp(v.y, mn.y, mx.y),ImClamp(v.z, mn.z, mx.z),ImClamp(v.w, mn.w, mx.w)); }

namespace Custom {
    namespace Colors {
        const ImVec4 accent = { 100/255.f, 180/255.f, 255/255.f, 1.f };
        namespace tab {
            const ImVec4 icon_inactive = ImVec4(0.5f, 0.5f, 0.5f, 0.6f);
            const ImVec4 icon_active = { 100/255.f, 180/255.f, 255/255.f, 1.f };
            const ImVec2 default_font_offset = ImVec2(0.0f, 0.0f);
        }
        namespace widget {
            static ImVec4 background = { 28/255.f, 28/255.f, 35/255.f, 1.f };
            static ImVec4 selectable = { 37/255.f, 37/255.f, 47/255.f, 1.f };
        };
        namespace text {
            static ImVec4 text_active = { 1.f, 1.f, 1.f, 1.f };
            static ImVec4 text_hov = { 89 / 255.f, 95 / 255.f, 105 / 255.f, 1.f };
            static ImVec4 text = { 50 / 255.f, 54 / 255.f, 59 / 255.f, 1.f };
            static ImVec4 text_gray = { 0.5f, 0.5f, 0.5f, 1.0f };
            static ImVec4 text_disabled = { 0.4f, 0.4f, 0.4f, 0.6f };
        };
    }

    namespace Easing {
        float Linear(float t) { return t; }
        float EaseInCubic(float t) { return t * t * t; }
        float EaseOutCubic(float t) { return 1 - pow(1 - t, 3); }
        float EaseOutElastic(float t) { 
            const float c4 = (2 * 3.14159f) / 3; 
            return t == 0 ? 0 : t == 1 ? 1 : pow(2, -10 * t) * sin((t * 10 - 0.75) * c4) + 1; 
        }
        float EaseOutBack(float t) { 
            const float c1 = 1.70158f; 
            const float c3 = c1 + 1;
            return 1 + c3 * pow(t - 1, 3) + c1 * pow(t - 1, 2); 
        }
        float EaseOutQuad(float t) { return 1 - (1 - t) * (1 - t); }
        float EaseOutExpo(float t) { return t == 1 ? 1 : 1 - pow(2, -10 * t); }
        float EaseInOutBack(float t) {
            const float c1 = 1.70158f; 
            const float c2 = c1 * 1.525f; 
            return t < 0.5 ? 
                (pow(2 * t, 2) * ((c2 + 1) * 2 * t - c2)) / 2 : 
                (pow(2 * t - 2, 2) * ((c2 + 1) * (t * 2 - 2) + c2) + 2) / 2; 
        }
        float EaseOutCirc(float t) { return sqrt(1 - pow(t - 1, 2)); }
        float EaseOutSine(float t) { return sin((t * 3.14159f) / 2); }
        float EaseOutBounce(float t) {
            const float n1 = 7.5625f;
            const float d1 = 2.75f;
            
            if (t < 1 / d1) {
                return n1 * t * t;
            } else if (t < 2 / d1) {
                return n1 * (t -= 1.5f / d1) * t + 0.75f;
            } else if (t < 2.5 / d1) {
                return n1 * (t -= 2.25f / d1) * t + 0.9375f;
            } else {
                return n1 * (t -= 2.625f / d1) * t + 0.984375f;
            }
        }
    }

    template<typename T>
    T CustomLerp(const T& a, const T& b, float t, float (*easing)(float) = Easing::EaseOutCubic) {
        return a + (b - a) * easing(t);
    }

    ImVec4 CustomLerp(const ImVec4& a, const ImVec4& b, float t, float (*easing)(float) = Easing::EaseOutCubic) {
        float eased_t = easing(t);
        return ImVec4(a.x + (b.x - a.x) * eased_t,a.y + (b.y - a.y) * eased_t,a.z + (b.z - a.z) * eased_t,a.w + (b.w - a.w) * eased_t);
    }

    struct SpringFloat {
        float target = 0.0f;
        float current = 0.0f;
        float velocity = 0.0f;
        void Update(float dt, float stiffness = 200.0f, float damping = 18.0f) {
            float force = (target - current) * stiffness;
            velocity += force * dt;
            velocity *= (1.0f - damping * dt);
            current += velocity * dt;
        }
    };

    struct TabState {
        ImVec4 icon_color = ImVec4(0.5f, 0.5f, 0.5f, 0.6f);
        float scale = 1.0f;
        float hover_scale = 0.0f;
        float press_scale = 0.0f;
    };

    bool Tab(const char* icon, const char* label, bool selected, const ImVec2& font_offset = Colors::tab::default_font_offset) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const float tab_width = 45.0f;
        const float tab_height = 45.0f;
        const ImVec2 pos = window->DC.CursorPos;
        const ImRect total_bb(pos, pos + ImVec2(tab_width, tab_height));
        ImGui::ItemSize(total_bb, style.FramePadding.y);
        if (!ImGui::ItemAdd(total_bb, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
        static std::map<ImGuiID, TabState> anim;
        auto it = anim.find(id);
        if (it == anim.end()) {
            anim.insert({id, TabState()});
            it = anim.find(id);
        }

        TabState& state = it->second;
        float target_hover_scale = hovered ? 0.08f : 0.0f;
        state.hover_scale = ImLerp(state.hover_scale, target_hover_scale, g.IO.DeltaTime * 15.0f);
        float target_press_scale = held ? -0.05f : 0.0f;
        state.press_scale = ImLerp(state.press_scale, target_press_scale, g.IO.DeltaTime * 20.0f);
        state.scale = 1.0f + state.hover_scale + state.press_scale;

        ImVec4 target_icon_color;
        if (selected) {
            target_icon_color = Colors::accent;
        } else if (held) {
            target_icon_color = Colors::text::text_active;
        } else if (hovered) {
            target_icon_color = Colors::text::text_hov;
        } else {
            target_icon_color = Colors::text::text_gray;
        }

        state.icon_color = ImLerp(state.icon_color, target_icon_color, g.IO.DeltaTime * 6.0f);
        ImDrawList* draw_list = window->DrawList;
        const ImVec2 center = ImVec2(pos.x + tab_width * 0.5f, pos.y + tab_height * 0.5f);
        ImVec2 icon_size = ImGui::CalcTextSize(icon);
        ImVec2 icon_pos = center - icon_size * 0.5f + font_offset;
        ImGui::PushFont(g.IO.Fonts->Fonts[1]);
        draw_list->AddText(icon_pos, ImGui::GetColorU32(state.icon_color), icon);
        ImGui::PopFont();
        return pressed;
    }

    struct switch_state {
        ImVec4 background, circle, text;
        float background_opticaly, circle_offset;
    };

    bool Switch(const char* label, bool* v) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
        const float square_sz = 18.0f;
        const float y_size = 18.0f;
        const float spacing = 8.0f;
        const float right_padding = 4.0f;
        const ImVec2 pos = window->DC.CursorPos;
        const float switch_width = square_sz * 2;
        const float available_width = ImGui::GetContentRegionMax().x - style.WindowPadding.x;
        const ImRect total_bb(pos, pos + ImVec2(available_width, y_size));

        ImGui::ItemSize(total_bb, style.FramePadding.y);
        if (!ImGui::ItemAdd(total_bb, id)) return false;

        bool hovered, held, pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
        static std::map<ImGuiID, switch_state> anim;
        auto it_anim = anim.find(id);
        if (it_anim == anim.end()) {
            anim.insert({id, switch_state()});
            it_anim = anim.find(id);
        }

        it_anim->second.circle_offset = ImLerp(it_anim->second.circle_offset, *v ? square_sz : -square_sz,g.IO.DeltaTime * 6.f);
        it_anim->second.background_opticaly = ImLerp(it_anim->second.background_opticaly, *v ? 0.2f : 1.0f, g.IO.DeltaTime * 6.f);
        it_anim->second.background = ImLerp(it_anim->second.background, *v ? Colors::accent : Colors::widget::background, g.IO.DeltaTime * 6.f);
        it_anim->second.circle = ImLerp(it_anim->second.circle, *v ? Colors::accent : Colors::text::text, g.IO.DeltaTime * 6.f);
        it_anim->second.text = ImLerp(it_anim->second.text, *v ? Colors::text::text_active : (hovered ? Colors::text::text_hov : Colors::text::text), g.IO.DeltaTime * 6.f);

        if (pressed) {
            *v = !(*v);
            ImGui::MarkItemEdited(id);
        }

        const ImVec2 switch_pos = ImVec2(pos.x + available_width - switch_width - right_padding,pos.y + (y_size - square_sz) * 0.5f);
        const ImRect check_bb(switch_pos, switch_pos + ImVec2(switch_width, square_sz));
        window->DrawList->AddRectFilled(check_bb.Min, check_bb.Max, ImGui::GetColorU32(ImVec4(it_anim->second.background.x, it_anim->second.background.y, it_anim->second.background.z, it_anim->second.background.w * it_anim->second.background_opticaly)), 5.0f);
        window->DrawList->AddRect(check_bb.Min, check_bb.Max, ImGui::GetColorU32(it_anim->second.background), 5.0f, ImDrawFlags_None, 1.1f);
        ImVec2 circle_center = ImVec2(check_bb.GetCenter().x + it_anim->second.circle_offset * 0.5f,check_bb.GetCenter().y);
        window->DrawList->AddCircleFilled(circle_center, 5.0f, ImGui::GetColorU32(it_anim->second.circle), 30);
        const ImVec2 text_pos = ImVec2(pos.x,pos.y + (y_size - label_size.y) * 0.5f);
        window->DrawList->AddText(text_pos, ImGui::GetColorU32(it_anim->second.text), label);
        return pressed;
    }
    
    struct HUDModule {
        std::string name;
        std::string suffix;
        bool enabled;
        SpringFloat anim;
        int icon;
    };

    inline void DrawHudIcon(ImDrawList* draw, ImVec2 center, float size, int type, ImU32 col) {
        if (type == 1) {
            draw->AddCircle(ImVec2(center.x, center.y - size*0.25f), size*0.3f, col, 0, 1.5f);
            draw->PathArcTo(ImVec2(center.x, center.y + size*0.5f), size*0.55f, 3.14f + 0.5f, 0.0f - 0.5f);
            draw->PathStroke(col, 0, 1.5f);
        } else if (type == 0) {
            draw->AddLine(ImVec2(center.x - size*0.4f, center.y + size*0.4f), ImVec2(center.x + size*0.4f, center.y - size*0.4f), col, 1.5f);
            draw->AddLine(ImVec2(center.x - size*0.4f, center.y - size*0.4f), ImVec2(center.x + size*0.4f, center.y + size*0.4f), col, 1.5f);
        } else if (type == 2) {
            draw->AddLine(ImVec2(center.x - size*0.4f, center.y - size*0.3f), ImVec2(center.x + size*0.4f, center.y - size*0.3f), col, 1.5f);
            draw->AddLine(ImVec2(center.x - size*0.4f, center.y - size*0.3f), ImVec2(center.x, center.y + size*0.5f), col, 1.5f);
            draw->AddLine(ImVec2(center.x + size*0.4f, center.y - size*0.3f), ImVec2(center.x, center.y + size*0.5f), col, 1.5f);
        } else if (type == 3) {
            draw->AddCircle(ImVec2(center.x + 1, center.y - 4), 2, col);
            draw->AddLine(ImVec2(center.x, center.y), ImVec2(center.x - 3, center.y + 5), col, 1.5f);
        } else {
            draw->AddCircle(center, size*0.3f, col, 0, 1.5f);
        }
    }

    inline float ScaleValue(float v, float scale) {
        return v * scale;
    }

    namespace HUD {
        static std::vector<HUDModule> g_HUDModules;
        
        void InitHUDData() {
            g_HUDModules.clear();
            g_HUDModules.push_back({"InvManager", "OpenInv | 5.0", true, {}, 1});
            g_HUDModules.push_back({"IRCClient", "Connected", true, {}, 0});
            g_HUDModules.push_back({"ClientSpoofer", "Lunar", true, {}, 0});
            g_HUDModules.push_back({"Disabler", "Prediction", true, {}, 0});
            g_HUDModules.push_back({"Teams", "ArmorColor", true, {}, 0});
            g_HUDModules.push_back({"GuiMove", "Hypixel", true, {}, 3});
            g_HUDModules.push_back({"Velocity", "Reduce", true, {}, 2});
            g_HUDModules.push_back({"AutoTool", "Spoof", true, {}, 1});
            g_HUDModules.push_back({"AntiBot", "Hypixel", true, {}, 2});
            g_HUDModules.push_back({"KillAura", "Switch", true, {}, 2});
            g_HUDModules.push_back({"NoSlow", "Vanilla", true, {}, 3});
            g_HUDModules.push_back({"NoJumpDelay", "", true, {}, 3});
            g_HUDModules.push_back({"FastPlace", "1.0", true, {}, 1});
            g_HUDModules.push_back({"AutoWeapon", "", true, {}, 2});
            g_HUDModules.push_back({"Stealer", "0.0", true, {}, 1});
            g_HUDModules.push_back({"AutoPlay", "", true, {}, 0});
            g_HUDModules.push_back({"KillSults", "", true, {}, 0});
            g_HUDModules.push_back({"Sprint", "", true, {}, 3});
            for(auto& m : g_HUDModules) {
                if(m.enabled) {
                    m.anim.current = 1.0f;
                    m.anim.target = 1.0f;
                }
            }
        }

        void RenderHUD(ImDrawList* draw, ImVec2 display_size, float scale = 1.0f) {
            #define S(v) ((v) * scale)

            float start_x = display_size.x - S(10.0f);
            float start_y = S(10.0f);
            float item_h = S(26.0f);
            float hud_stiffness = 250.0f;
            float hud_damping = 20.0f;

            std::vector<HUDModule*> active_mods;
            for (auto& mod : g_HUDModules) {
                mod.anim.target = mod.enabled ? 1.0f : 0.0f;
                mod.anim.Update(ImGui::GetIO().DeltaTime, hud_stiffness, hud_damping);
                if (mod.anim.current > 0.01f) active_mods.push_back(&mod);
            }

            std::sort(active_mods.begin(), active_mods.end(), [](HUDModule* a, HUDModule* b){
                float wa = ImGui::CalcTextSize(a->name.c_str()).x + ImGui::CalcTextSize(a->suffix.c_str()).x;
                float wb = ImGui::CalcTextSize(b->name.c_str()).x + ImGui::CalcTextSize(b->suffix.c_str()).x;
                return wa > wb;
            });

            int count = active_mods.size();
            if(count == 0) return;

            for (int i = 0; i < count; i++) {
                HUDModule* m = active_mods[i];
                float alpha = m->anim.current;
                float t = (count > 1) ? (float)i / (float)(count - 1) : 0.0f;
                ImVec4 c_top = ImVec4(1.0f, 0.75f, 0.0f, 1.0f);
                ImVec4 c_bot = ImVec4(0.0f, 0.8f, 0.9f, 1.0f);
                ImVec4 c_cur = ImVec4(c_top.x + (c_bot.x - c_top.x) * t,c_top.y + (c_bot.y - c_top.y) * t,c_top.z + (c_bot.z - c_top.z) * t,alpha);
                ImU32 text_col = ImGui::GetColorU32(c_cur);
                ImU32 suffix_col = IM_COL32(160, 160, 160, (int)(255 * alpha));
                ImU32 icon_col = IM_COL32(200, 190, 120, (int)(255 * alpha));

                float name_w = ImGui::CalcTextSize(m->name.c_str()).x;
                float suffix_w = m->suffix.empty() ? 0 : ImGui::CalcTextSize(m->suffix.c_str()).x + S(6.0f);
                float icon_w = S(20.0f);
                float total_w = name_w + suffix_w + icon_w + S(12.0f);
                float off_x = (1.0f - alpha) * (total_w + S(80.0f));

                ImVec2 p_min = ImVec2(start_x - total_w + off_x, start_y);
                ImVec2 p_max = ImVec2(start_x + off_x, start_y + item_h);
                draw->AddRectFilled(p_min, p_max, IM_COL32(15, 15, 15, (int)(160 * alpha)), S(4.0f));
                ImVec2 icon_center = ImVec2(p_max.x - S(13.0f), p_min.y + item_h * 0.5f);
                draw->AddCircleFilled(icon_center, S(9.0f), IM_COL32(40, 40, 40, (int)(180*alpha)));
                DrawHudIcon(draw, icon_center, S(11.0f), m->icon, icon_col);

                float cur_x = p_max.x - icon_w - S(4.0f);
                if (!m->suffix.empty()) {
                    cur_x -= ImGui::CalcTextSize(m->suffix.c_str()).x;
                    draw->AddText(ImVec2(cur_x, p_min.y + (item_h - ImGui::GetFontSize()) * 0.5f), suffix_col, m->suffix.c_str());
                    cur_x -= S(6.0f);
                }

                cur_x -= name_w;
                draw->AddText(ImVec2(cur_x, p_min.y + (item_h - ImGui::GetFontSize()) * 0.5f), text_col, m->name.c_str());
                start_y += item_h + S(2.0f);
            }
            #undef S
        }

        void SetModuleEnabled(const std::string& moduleName, bool enabled) {
            for (auto& mod : g_HUDModules) {
                if (mod.name == moduleName) {
                    mod.enabled = enabled;
                    break;
                }
            }
        }

        bool GetModuleEnabled(const std::string& moduleName) {
            for (auto& mod : g_HUDModules) {
                if (mod.name == moduleName) {
                    return mod.enabled;
                }
            }
            return false;
        }

        std::vector<HUDModule>& GetModules() {
            return g_HUDModules;
        }
    }
}