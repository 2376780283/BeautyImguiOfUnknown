mkdir -p build && cd build

# 调用 cmake
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake \
      -DANDROID_ABI=arm64-v8a \
      -DANDROID_PLATFORM=android-33 \
      -DCMAKE_BUILD_TYPE=Release \
      ..

# 编译
cmake --build . --config Release