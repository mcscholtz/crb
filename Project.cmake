set (CMAKE_C_STANDARD 11)
include (CTest)
#compiler warnings
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
  string(APPEND CMAKE_C_FLAGS " -Wall -Wextra -Wlogical-op -Wjump-misses-init -Wdouble-promotion -Wshadow -Wformat=2 -pedantic")
elseif(CMAKE_COMPILER_IS_CLANG)
  string(APPEND CMAKE_C_FLAGS " -Weverything")

endif()

# These are the corresponding output paths
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set (LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH})

# Library under test source 
set (PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src )

#Name of that library
SET( PROJECT_LIB proj_lib )
