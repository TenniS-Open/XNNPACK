# Copyright (c) Facebook, Inc. and its affiliates.
# All rights reserved.
#
# Copyright 2019 Google LLC
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

CMAKE_MINIMUM_REQUIRED(VERSION 3.5 FATAL_ERROR)

PROJECT(fp16-download NONE)

INCLUDE(ExternalProject)
ExternalProject_Add(fp16
  GIT_REPOSITORY https://gitlab.seetatech.com/TenniS/FP16
  GIT_TAG master
  SOURCE_DIR "${CMAKE_BINARY_DIR}/FP16-source"
  BINARY_DIR "${CMAKE_BINARY_DIR}/FP16"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)
