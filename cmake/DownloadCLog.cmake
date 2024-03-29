# Copyright (c) Facebook, Inc. and its affiliates.
# All rights reserved.
#
# Copyright 2019 Google LLC
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

CMAKE_MINIMUM_REQUIRED(VERSION 3.5 FATAL_ERROR)

PROJECT(clog-download NONE)

INCLUDE(ExternalProject)
ExternalProject_Add(clog
  GIT_REPOSITORY https://github.com/TenniS-Open/cpuinfo
  GIT_TAG 728f3e909fa5c57e0123c4658e234f6b1941385d
  SOURCE_DIR "${CMAKE_BINARY_DIR}/clog-source"
  BINARY_DIR "${CMAKE_BINARY_DIR}/clog"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)
