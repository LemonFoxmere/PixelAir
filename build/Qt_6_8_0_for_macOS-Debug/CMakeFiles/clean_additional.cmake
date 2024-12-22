# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appPixelAir_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appPixelAir_autogen.dir/ParseCache.txt"
  "appPixelAir_autogen"
  )
endif()
