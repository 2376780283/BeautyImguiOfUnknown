cmake_minimum_required(VERSION 3.22.1)
project(ImGuiExample)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(${CMAKE_PROJECT_NAME} SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imgui.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imgui_demo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imgui_draw.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imgui_tables.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imgui_widgets.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/backends/imgui_impl_android.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/backends/imgui_impl_opengl3.cpp
  ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
)

set(CMAKE_SHARED_LINKER_FLAGS
  "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate"
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
  IMGUI_IMPL_OPENGL_ES3
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/
  ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/backends
  ${ANDROID_NDK}/sources/android/native_app_glue
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
  android
  EGL
  GLESv3
  log
)