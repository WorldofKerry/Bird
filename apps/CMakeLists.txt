add_executable(app app.cpp)
target_compile_features(app PRIVATE cxx_std_17)

target_link_libraries(app PRIVATE modern_library fmt::fmt)

add_executable(filewrite filewrite.cpp)
target_compile_features(filewrite PRIVATE cxx_std_17)

target_link_libraries(filewrite PRIVATE modern_library fmt::fmt)

