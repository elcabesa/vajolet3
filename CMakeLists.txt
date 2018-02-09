cmake_minimum_required (VERSION 2.8)
project (Vajolet)

IF(NOT ${CMAKE_SYSTEM_PROCESSOR} MATCHES "^arm")
	set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -O3 -msse4.2 -m64 -mbmi -mbmi2 -mpopcnt -pedantic -Wall -Wextra -fmessage-length=0")
	set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -g -O0 -msse3 -m64 -pedantic -Wall -Wextra -fmessage-length=0 --coverage")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -O3 -pedantic -Wall -Wextra -fmessage-length=0")
	set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -g -O0 -pedantic -Wall -Wextra -fmessage-length=0 --coverage")
endif()

if (WIN32)
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s -static -pthread")
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG " -pthread -static --coverage")
else()
	set (CMAKE_EXE_LINKER_FLAGS_RELEASE "-s -Wl,--whole-archive -lpthread -Wl,--no-whole-archive -static")
	set (CMAKE_EXE_LINKER_FLAGS_DEBUG "-s -Wl,--whole-archive -lpthread -Wl,--no-whole-archive -static --coverage")
endif()

set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

add_library(libChess BitMap.cpp HashKeys.cpp Move.cpp Position.cpp tSquare.cpp)

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
    add_executable(Vajolet_unitTest test/UnitTest.cpp test/BitBoardIndexTest.cpp test/BitMapTest.cpp test/HashKeysTest.cpp test/MoveTest.cpp test/PositionTest.cpp test/ScoreTest.cpp test/tSquareTest.cpp)
    target_link_libraries(Vajolet_unitTest libChess gtest )
    add_test(NAME example_test COMMAND Vajolet_unitTest)
    
 
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS Vajolet_unitTest)