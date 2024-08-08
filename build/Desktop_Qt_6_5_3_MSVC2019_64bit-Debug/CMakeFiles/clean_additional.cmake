# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\VEDA_BankManagement_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\VEDA_BankManagement_autogen.dir\\ParseCache.txt"
  "VEDA_BankManagement_autogen"
  )
endif()
