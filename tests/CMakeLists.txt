cmake_minimum_required (VERSION 3.9.2)
project (ProjectTests)
include(../Project.cmake)

#Test Lib Source
set (TESTLIB_SOURCE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/cutest)
set (TESTLIB_SOURCES 
    ${TESTLIB_SOURCE_DIR}/cutest.c
)

#Build Test Lib as static
SET( TEST_LIB cutest )
ADD_LIBRARY( ${TEST_LIB} STATIC ${TESTLIB_SOURCES} )

#Common Test Source
set (TEST_SOURCE_DIR ${CMAKE_SOURCE_DIR}/tests)
set (TEST_SOURCES 
    ${TEST_SOURCE_DIR}/suite.c
)

#Build each test source file
set (TEST_REGEX ${CMAKE_SOURCE_DIR}/tests/*-test.c)
file(GLOB files ${TEST_REGEX})
foreach(file ${files})
  #Use the filenames as the test names
  GET_FILENAME_COMPONENT(sourcefile ${file} NAME_WE)
  SET( TEST_EXE ${sourcefile} )
  ADD_EXECUTABLE( ${TEST_EXE} ${file} ${TEST_SOURCES})
  
  #Include source
  TARGET_INCLUDE_DIRECTORIES(${TEST_EXE} PRIVATE 
    ${TESTLIB_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
    ${TEST_SOURCE_DIR}
  )
  
  #Link libraries
  TARGET_LINK_LIBRARIES( ${TEST_EXE} ${PROJECT_LIB} ${TEST_LIB} )
  
  #Add tests
  add_test(
    NAME ${TEST_EXE}
    COMMAND ${TEST_EXE})
endforeach()