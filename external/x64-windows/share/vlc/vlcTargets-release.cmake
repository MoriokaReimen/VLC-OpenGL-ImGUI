#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "vlc" for configuration "Release"
set_property(TARGET vlc APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vlc PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libvlc.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libvlc.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vlc )
list(APPEND _IMPORT_CHECK_FILES_FOR_glfw "${_IMPORT_PREFIX}/lib/libvlc.lib" "${_IMPORT_PREFIX}/bin/libvlc.dll" )

# Import target "vlccore" for configuration "Release"
set_property(TARGET vlccore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vlccore PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libvlccore.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libvlccore.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vlccore )
list(APPEND _IMPORT_CHECK_FILES_FOR_vlccore "${_IMPORT_PREFIX}/lib/libvlccore.lib" "${_IMPORT_PREFIX}/bin/libvlccore.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
