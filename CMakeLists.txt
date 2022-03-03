# Copyright (c) Darrell Wright
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/beached/sv2_presentation_2022_03_03
#

cmake_minimum_required(VERSION 3.14)

project("sv2_presentation_2022_03_03"
        VERSION "0.1.1"
        DESCRIPTION "A std::string_view like type with enhanced parsing helpers"
        HOMEPAGE_URL "https://github.com/beached/sv2_presentation_2022_03_03"
        LANGUAGES C CXX
        )

set(CMAKE_CXX_STANDARD 20 CACHE STRING "The C++ standard whose features are requested.")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(extern)

include(GNUInstallDirs)
set(string_view_INSTALL_CMAKEDIR
        "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake"
        CACHE STRING
        "The install directory to use for CMake package config files"
        )

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

enable_testing()

add_executable(parse_url_std_sv src/parse_url_std_sv.cpp)
target_link_libraries(parse_url_std_sv PRIVATE daw::daw-header-libraries)
add_test(parse_url_std_sv_test parse_url_std_sv)

add_executable(parse_url_daw_sv2 src/parse_url_daw_sv2.cpp)
target_link_libraries(parse_url_daw_sv2 PRIVATE daw::daw-header-libraries)
add_test(parse_url_daw_sv2_test parse_url_daw_sv2)

add_executable(split_string_std_sv src/split_string_std_sv.cpp)
target_link_libraries(split_string_std_sv PRIVATE daw::daw-header-libraries)
add_test(split_string_std_sv_test split_string_std_sv)

add_executable(split_string_daw_sv2 src/split_string_daw_sv2.cpp)
target_link_libraries(split_string_daw_sv2 PRIVATE daw::daw-header-libraries)
add_test(split_string_daw_sv2_test split_string_daw_sv2)


