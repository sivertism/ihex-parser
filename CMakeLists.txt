cmake_minimum_required(VERSION 3.10)

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

install(
  TARGETS ihex-parser
  EXPORT IntelHexParserTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION include
  )

# Include files
install(DIRECTORY include/ DESTINATION include ${CMAKE_INSTALL_INCLUDEDIR})

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/ihex-parser/ihex-parser-config-version.cmake"
  VERSION ${PACKAGE_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

export(EXPORT IntelHexParserTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/ihex-parser/ihex-parser-targets.cmake"
  NAMESPACE IntelHexParser::
  )

configure_file(cmake/ihex-parser-config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/ihex-parser/ihex-parser-config.cmake"
  COPYONLY)

set(ConfigPackageLocation lib/cmake/ihex-parser)
install(EXPORT IntelHexParserTargets
  FILE
    ihex-parser-targets.cmake
  NAMESPACE
    IntelHexParser::
  DESTINATION
    ${ConfigPackageLocation}
    )

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ihex-parser/ihex-parser-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/ihex-parser/ihex-parser-config-version.cmake"
  DESTINATION
    "${ConfigPackageLocation}"
  )
