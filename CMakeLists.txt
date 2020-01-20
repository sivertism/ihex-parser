cmake_minimum_required(VERSION 3.12)

project(IntelHexParser
  VERSION 0.1
  DESCRIPTION "Fork from https://github.com/bstrysko/IntelHexParser. Moved to CMAKE build system and added handling of Record Type 4."
  LANGUAGES CXX)

# If this project is not included through add_subdirectory
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_subdirectory(src)
add_subdirectory(apps)

# Install
# Include files
install(DIRECTORY include/ DESTINATION include ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS ihex_library LIBRARY DESTINATION lib ${CMAKE_INSTALL_LIBDIR})

# CMake config files
#install(EXPORT ihex-parser
#DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/ihex-parser"
#NAMESPACE IntelHexParser::
#FILE "${CMAKE_CURRENT_BINARY_DIR}/IntelHexParserConfig.cmake"
#)
#install(FILES "${CMAKE_CURRENT_BINARY_DIR}/IntelHexParserConfig.cmake"
#"${CMAKE_CURRENT_BINARY_DIR}/IntelHexParserConfigVersion.cmake"
#DESTINATION lib/cmake/IntelHexParser
#)


