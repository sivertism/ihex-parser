include (CMakePackageConfigHelpers)
write_basic_package_version_file(
  IntelHexParserConfigVersion.cmake
  VERSION ${PACKAGE_VERSION}
  COMPATIBILITY AnyNewerVersion
  )
