# Copyright (c) Facebook, Inc. and its affiliates.
# All rights reserved.
#
# Copyright 2019 Google LLC
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

CMAKE_MINIMUM_REQUIRED(VERSION 3.5 FATAL_ERROR)

PROJECT(fxdiv-download NONE)

INCLUDE(ExternalProject)
ExternalProject_Add(fxdiv
  GIT_REPOSITORY https://github.com/TenniS-Open/FXdiv
  GIT_TAG 63058eff77e11aa15bf531df5dd34395ec3017c8
  SOURCE_DIR "${CMAKE_BINARY_DIR}/FXdiv-source"
  BINARY_DIR "${CMAKE_BINARY_DIR}/FXdiv"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)
