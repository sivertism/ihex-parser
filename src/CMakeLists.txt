file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${IntelHexParser_SOURCE_DIR}/include/ihex-parser/*.hpp")

add_library(ihex-parser
IntelHexFile.cpp
IntelHexFileEntry.cpp
Program.cpp
ProgramPage.cpp
${HEADER_LIST}
)

#target_include_directories(ihex-parser PUBLIC ../include)
target_include_directories(ihex-parser PUBLIC $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${IntelHexParser_SOURCE_DIR}/include>)

target_compile_features(ihex-parser PUBLIC cxx_std_11)

# IDE grouping
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
