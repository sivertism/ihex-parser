add_executable(example main.cpp)
target_compile_features(example PRIVATE cxx_std_11)

target_link_libraries(example PRIVATE ihex_library)
