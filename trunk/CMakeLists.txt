# Copyright 2010 Tencent Inc.
# Author: Yi Wang (yiwang@tencent.com)
#
# This is the root CMakeLists.txt file in the mapreduce-lite project,
# which build all subdirectories (packages) in the order of
# inter-package dependence.  You might not have ``check-out'' access
# to all these packages.  If os, please just comment out lines
# referring to packages that you cannot access.  But please confirm
# with the source management administrator that once you have access
# to package A, you must also have access to all packages on which A
# depends.
#
# To build the whole mapreduce-lite project, you can type the
# following shell commands:
#
#  $> mkdir build
#  $> cd build
#  $> cmake ..
#  $> make
#
# Thus you check out the mapreduce-lite project and build it in a
# subdirectory ``build''.  If you want further to install the built
# project, you can modify the default installation directory:
#
#   set(CMAKE_INSTALL_PREFIX "/home/public/mapreduce-lite")
#
# and type the command
#
#  $> make install
#
# If you want to use distcc for a distributed build, substitute above
# command
#   cmake ../mapreduce-lite
# by
#   CC=distcc cmake ../mapreduce-lite
#
project ("mapreduce_lite")

cmake_minimum_required(VERSION 2.8)  # Requires 2.9 for protobuf support.

#------------------------------------------------------------------------------
# Add protobuf compilation support
#------------------------------------------------------------------------------
include("FindProtobuf")
find_package(Protobuf REQUIRED)

#------------------------------------------------------------------------------
# Take almost all warnining;
# Take warnings as errors;
# Do not generate debug symbols;
# Optimization level 2;
#------------------------------------------------------------------------------
add_definitions(" -Wall -Wno-sign-compare -Werror -O2 ")

#------------------------------------------------------------------------------
# Declare where our project will be installed.
#------------------------------------------------------------------------------
set(CMAKE_INSTALL_PREFIX "/home/public/mapreduce-lite")

#------------------------------------------------------------------------------
# Ensure executables are statically linked with libraries.
#------------------------------------------------------------------------------
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")

#------------------------------------------------------------------------------
# Declare where the third party libraries were installed.
#------------------------------------------------------------------------------
set(THIRD_PARTY_DIR "${PROJECT_SOURCE_DIR}/thirdparty")

#------------------------------------------------------------------------------
# Declare third party libraries we might need.
# Add new lines below if you installed more 3rd-party libs.
#------------------------------------------------------------------------------
set(PROTOBUF_DIR "${THIRD_PARTY_DIR}/protobuf-2.3.0")
set(BOOST_DIR "${THIRD_PARTY_DIR}/boost-1.43.0")
set(GFLAGS_DIR "${THIRD_PARTY_DIR}/gflags-1.4")
set(GTEST_DIR "${THIRD_PARTY_DIR}/gtest-1.5.0")
set(RE2_DIR "${THIRD_PARTY_DIR}/re2")

#------------------------------------------------------------------------------
# Set include paths.
# Add new lines below if you installed more 3rd-party libs.
#------------------------------------------------------------------------------
include_directories(
  "${PROJECT_SOURCE_DIR}";
  "${PROJECT_BINARY_DIR}";
  "${PROTOBUF_DIR}/include";
  "${BOOST_DIR}/include";
  "${GFLAGS_DIR}/include";
  "${GTEST_DIR}/include";
  "${RE2_DIR}/include";
  )

#------------------------------------------------------------------------------
# Set libray paths.
# Add new lines below if you add new packages in mapreduce-lite project, or
# installed more 3rd-party libs.
#------------------------------------------------------------------------------
link_directories(
  "${PROJECT_BINARY_DIR}/src/base";
  "${PROJECT_BINARY_DIR}/src/strutil";
  "${PROJECT_BINARY_DIR}/src/hash";
  "${PROJECT_BINARY_DIR}/src/system";
  "${PROJECT_BINARY_DIR}/src/reduce_input";
  "${PROJECT_BINARY_DIR}/src/mapreduce_lite";
  "${PROTOBUF_DIR}/lib";
  "${BOOST_DIR}/lib";
  "${GFLAGS_DIR}/lib";
  "${GTEST_DIR}/lib";
  "${RE2_DIR}/lib";
  )

#------------------------------------------------------------------------------
# Declare packages in paralgo project.
# Add new lines below if you add new packages in mapreduce-lite project.
#------------------------------------------------------------------------------
add_subdirectory(src/base)
add_subdirectory(src/strutil)
add_subdirectory(src/hash)
add_subdirectory(src/system)
add_subdirectory(src/sorted_buffer)
add_subdirectory(src/mapreduce_lite)
