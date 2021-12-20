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
  GIT_REPOSITORY https://lvsen@gitlab.seetatech.com/lvsen/FP16.git
  GIT_TAG 61bd6a25863d754e8815ae537adcba3dcfeba277
  SOURCE_DIR "${CMAKE_BINARY_DIR}/FP16-source"
  BINARY_DIR "${CMAKE_BINARY_DIR}/FP16"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)
