cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

set(ASU_DIR ${PROJECT_SOURCE_DIR}/vendor/asu)

include(${ASU_DIR}/AsuUtils.cmake)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_CXX_STANDARD 11)
enable_language(CXX)

message("---> CONFIGURE CMake TESTS <---")

# need to override gcc configuration from avr toolchain into "desktop" version
message("---> Configure CMake to use desktop c++ to compile tests")
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_COMPILE_OBJECT "<CMAKE_CXX_COMPILER> -c -g -O0 -w -std=gnu++11 <DEFINES> <INCLUDES> <FLAGS> <SOURCE> -o <OBJECT>")
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> -w -g -O0 -flto -fuse-linker-plugin -o <TARGET> <OBJECTS> <LINK_LIBRARIES> -lm")
set(CMAKE_C_COMPILE_OBJECT "<CMAKE_C_COMPILER> -c -g -w -O0 -std=gnu11 <DEFINES> <INCLUDES> <FLAGS> <SOURCE> -o <OBJECT>")
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> -w -g -O0 -flto -fuse-linker-plugin -o <TARGET> <OBJECTS> <LINK_LIBRARIES> -lm")

set(__cpp_includes_command "echo | $(gcc -print-prog-name=cc1plus) -v 2>&1 | grep -e '^ /'")
execute_process(COMMAND bash -c "${__cpp_includes_command}" OUTPUT_VARIABLE CPP_SYSTEM_INCLUDE_PATHS)

message("---> Add standard system include paths:")
message(${CPP_SYSTEM_INCLUDE_PATHS})
string(REPLACE "\n" ";" CPP_SYSTEM_INCLUDE_PATHS_SANITIZED ${CPP_SYSTEM_INCLUDE_PATHS})
include_directories(SYSTEM ${CPP_SYSTEM_INCLUDE_PATHS_SANITIZED})

file(GLOB_RECURSE RUNNER_SRC "${ASU_DIR}/runner/*.h" "${ASU_DIR}/runner/*.cpp" "${ASU_DIR}/unit_setup.h")
file(GLOB_RECURSE MOCK_SRC "${ASU_DIR}/mock/*.h" "${ASU_DIR}/mock/*.cpp")
file(GLOB_RECURSE TESTS_SRC "${CMAKE_SOURCE_DIR}/test/src/*.cpp")
file(GLOB_RECURSE PROJECT_SRC "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/src/*.h")
#file(GLOB_RECURSE MOCK_LIBS_DIRS_PROJECT LIST_DIRECTORIES true "${CMAKE_SOURCE_DIR}/test/mock/")
#file(GLOB_RECURSE MOCK_LIBS_DIRS_ARDUINO LIST_DIRECTORIES true RELATIVE "${ASU_DIR}/mock" "mock")

subdirs(MOCK_LIBS_DIRS_PROJECT "${CMAKE_SOURCE_DIR}/test/mock")
subdirs(MOCK_LIBS_DIRS_ARDUINO "${ASU_DIR}/mock")

message(RUNNER_SRC ${RUNNER_SRC})
message(MOCK_SRC ${MOCK_SRC})
message(TESTS_SRC ${TESTS_SRC})
message(PROJECT_SRC ${PROJECT_SRC})
message(MOCK_LIBS_DIRS_PROJECT "${MOCK_LIBS_DIRS_PROJECT}")
message(MOCK_LIBS_DIRS_ARDUINO "${MOCK_LIBS_DIRS_ARDUINO}")

#todo: include libs
find_package(PkgConfig REQUIRED)
pkg_check_modules(PNG REQUIRED libpng)

set(MOCK_LIBS_DIRS ${MOCK_LIBS_DIRS_PROJECT} ${MOCK_LIBS_DIRS_ARDUINO} ${PROJECT_SOURCE_DIR}/src)

add_library(test_shared_sources_lib OBJECT ${RUNNER_SRC} ${PROJECT_SRC} ${MOCK_SRC})
target_include_directories(test_shared_sources_lib PRIVATE ${MOCK_LIBS_DIRS} ${PNG_INCLUDE_DIRS})

foreach (TEST_FILE IN LISTS TESTS_SRC)
    get_filename_component(FILE_NAME "${TEST_FILE}" NAME_WLE)
    string(REGEX REPLACE "Test$" "" NAME "${FILE_NAME}")
    message("---> Add test case '${NAME}' from file '${TEST_FILE}'")

    add_executable(test_exe_${NAME} EXCLUDE_FROM_ALL ${TEST_FILE})
    set_target_properties(test_exe_${NAME} PROPERTIES SUFFIX "")
    target_include_directories(test_exe_${NAME} PRIVATE ${ASU_DIR} ${MOCK_LIBS_DIRS} ${PNG_INCLUDE_DIRS})
    target_link_libraries(test_exe_${NAME} test_shared_sources_lib ${PNG_LINK_LIBRARIES})
    add_test(test_${NAME} test_exe_${NAME})

    list(APPEND TESTS_LIST test_exe_${NAME})
endforeach ()

add_custom_target(test_build_all DEPENDS test_shared_sources_lib ${TESTS_LIST})

add_custom_target(test_run_all
        DEPENDS test_build_all
        COMMAND ctest -T test --extra-verbose --no-compress-output --test-output-size-passed 1000000 --test-output-size-failed 1000000
        )


