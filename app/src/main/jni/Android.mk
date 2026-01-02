LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := ImGuiExample
LOCAL_SRC_FILES := \
    Main.cpp \
    ImGui/imgui.cpp \
    ImGui/imgui_demo.cpp \
    ImGui/imgui_draw.cpp \
    ImGui/imgui_tables.cpp \
    ImGui/imgui_widgets.cpp \
    ImGui/backends/imgui_impl_android.cpp \
    ImGui/backends/imgui_impl_opengl3.cpp

# 添加 native_app_glue
LOCAL_STATIC_LIBRARIES := android_native_app_glue
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/ImGui \
    $(LOCAL_PATH)/ImGui/backends \
    $(ANDROID_NDK)/sources/android/native_app_glue

LOCAL_LDLIBS := -landroid -lEGL -lGLESv3 -llog
LOCAL_CPPFLAGS := -DIMGUI_IMPL_OPENGL_ES3

include $(BUILD_SHARED_LIBRARY)

# 引用 native_app_glue
$(call import-module,android/native_app_glue)