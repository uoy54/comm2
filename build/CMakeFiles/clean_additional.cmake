# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "CMakeFiles\\comm2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\comm2_autogen.dir\\ParseCache.txt"
  "comm2_autogen"
  )
endif()
