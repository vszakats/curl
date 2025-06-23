#***************************************************************************
#                                  _   _ ____  _
#  Project                     ___| | | |  _ \| |
#                             / __| | | | |_) | |
#                            | (__| |_| |  _ <| |___
#                             \___|\___/|_| \_\_____|
#
# Copyright (C) Daniel Stenberg, <daniel@haxx.se>, et al.
#
# This software is licensed as described in the file COPYING, which
# you should have received as part of this distribution. The terms
# are also available at https://curl.se/docs/copyright.html.
#
# You may opt to use, copy, modify, merge, publish, distribute and/or sell
# copies of the Software, and permit persons to whom the Software is
# furnished to do so, under the terms of the COPYING file.
#
# This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
# KIND, either express or implied.
#
# SPDX-License-Identifier: curl
#
###########################################################################

# Get BUNDLE, FIRSTFILES, CURLX_CFILES, TESTFILES variables
curl_transform_makefile_inc("Makefile.inc" "${CMAKE_CURRENT_BINARY_DIR}/Makefile.inc.cmake")
include("${CMAKE_CURRENT_BINARY_DIR}/Makefile.inc.cmake")

add_executable(${BUNDLE} EXCLUDE_FROM_ALL "${BUNDLE}.c")
add_dependencies(testdeps ${BUNDLE})
target_link_libraries(${BUNDLE} ${LIB_SELECTED} ${CURL_LIBS})
target_include_directories(${BUNDLE} PRIVATE
  "${PROJECT_BINARY_DIR}/lib"            # for "curl_config.h"
  "${PROJECT_SOURCE_DIR}/lib"            # for "curl_setup.h", curlx
)
set_property(TARGET ${BUNDLE} APPEND PROPERTY COMPILE_DEFINITIONS "CURL_NO_OLDIES")
set_target_properties(${BUNDLE} PROPERTIES OUTPUT_NAME "${BUNDLE}" PROJECT_LABEL "Test ${BUNDLE}" UNITY_BUILD OFF C_CLANG_TIDY "")

curl_clang_tidy_tests(${BUNDLE} ${FIRSTFILES} ${TESTFILES})
