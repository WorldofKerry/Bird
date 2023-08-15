# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")
# set(HEADER_LIST "${ModernCMakeExample_SOURCE_DIR}/include/modern/lib.hpp")

# Make an automatic library - will be static or dynamic based on user setting
set (modern_library_src
lib.cpp
display.cpp
)
add_library(modern_library ${modern_library_src} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(modern_library PUBLIC ../include)

# This depends on (header only) boost
# target_link_libraries(modern_library PRIVATE Boost::boost)

# ncurses
# find_package(Curses REQUIRED)
# include_directories(${CURSES_INCLUDE_DIR})
# target_link_libraries(modern_library PRIVATE ${CURSES_LIBRARIES})

# All users of this library will need at least C++20
target_compile_features(modern_library PUBLIC cxx_std_20)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
