cmake_minimum_required (VERSION 2.8)
project (Vajolet)

IF( VAJOLET_CPU_TYPE STREQUAL "64OLD")
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse3 -m64" )
ELSEIF( VAJOLET_CPU_TYPE STREQUAL "64NEW")
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2 -m64 -mpopcnt" )
ELSEIF( VAJOLET_CPU_TYPE STREQUAL "64BMI2")
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2 -m64 -mbmi -mbmi2 -mpopcnt" )
ELSE()
ENDIF()


set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -pedantic -Wall -Wextra" )

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}  ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 ")
	
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --coverage")
endif()

if (WIN32)
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s -Wl,--allow-multiple-definition -static -pthread")
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Wl,--allow-multiple-definition -static -pthread")		
else()
	
	if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
		set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s -Wl,--whole-archive -lpthread -Wl,--no-whole-archive -static")
		set (CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Wl,--whole-archive -lpthread -Wl,--no-whole-archive -static --coverage")
	elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
		set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s -lpthread")
		set (CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -s -lpthread")
	endif()
	
endif()

set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

add_library(libChess BitMap.cpp BitMapMoveGenerator.cpp HashKeys.cpp Move.cpp MoveGenerator.cpp MoveSelector.cpp Position.cpp tSquare.cpp)

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

    add_executable(Vajolet_unitTest test/UnitTest.cpp test/BitMapMoveGeneratorTest.cpp test/BitBoardIndexTest.cpp test/BitMapTest.cpp test/HashKeysTest.cpp test/MoveListTest.cpp test/MoveGeneratorTest.cpp test/MoveTest.cpp test/PositionTest.cpp test/ScoreTest.cpp test/StateTest.cpp test/tSquareTest.cpp)
    target_link_libraries(Vajolet_unitTest libChess gtest )
	
	add_custom_command(
        TARGET Vajolet_unitTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/test/perft.txt
                ${CMAKE_CURRENT_BINARY_DIR}/perft.txt)

	
	add_executable(Vajolet_unitTestLong test/UnitTest.cpp test/MoveGeneratorTestLong.cpp)
    target_link_libraries(Vajolet_unitTestLong libChess gtest )