cmake_minimum_required (VERSION 2.8)
project (Vajolet)

set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -O3 -msse4.2 -m64 -mbmi -mbmi2 -mpopcnt -pedantic -Wall -Wextra -fmessage-length=0")
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -g -O0 -msse4.2 -m64 -pedantic -Wall -Wextra -fmessage-length=0 --coverage")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s -pthread")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG " -pthread --coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

add_library(libChess BitMap.cpp HashKeys.cpp Move.cpp tSquare.cpp)

add_executable(Vajolet Vajolet.cpp )
target_link_libraries (Vajolet libChess)

# Download and unpack googletest at configure time
    configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
      RESULT_VARIABLE result
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
    if(result)
      message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
      RESULT_VARIABLE result
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
    if(result)
      message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                     ${CMAKE_BINARY_DIR}/googletest-build)

    # The gtest/gtest_main targets carry header search path
    # dependencies automatically when using CMake 2.8.11 or
    # later. Otherwise we have to add them here ourselves.
    if (CMAKE_VERSION VERSION_LESS 2.8.11)
      include_directories("${gtest_SOURCE_DIR}/include")
    endif()

    enable_testing()
    # Now simply link against gtest or gtest_main as needed. Eg
    add_executable(Vajolet_unitTest test/UnitTest.cpp test/BitMapTest.cpp test/HashKeysTest.cpp test/MoveTest.cpp test/tSquareTest.cpp)
    target_link_libraries(Vajolet_unitTest gtest libChess)
    add_test(NAME example_test COMMAND Vajolet_unitTest)
    
 
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS Vajolet_unitTest)