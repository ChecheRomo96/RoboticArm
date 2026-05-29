#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Foundation::Foundation" for configuration "Debug"
set_property(TARGET Foundation::Foundation APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Foundation::Foundation PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libFoundation_d.a"
  )

list(APPEND _cmake_import_check_targets Foundation::Foundation )
list(APPEND _cmake_import_check_files_for_Foundation::Foundation "${_IMPORT_PREFIX}/lib/libFoundation_d.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
