/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * SPDX-License-Identifier: curl
 *
 ***************************************************************************/
#include "first.h"

#include "../../lib/curlx/multibyte.c"
#include "../../lib/curlx/timediff.c"
#include "../../lib/curlx/wait.c"

#include "h2_pausing.c"
#include "h2_serverpush.c"
#include "h2_upgrade_extreme.c"
#include "hx_download.c"
#include "hx_upload.c"
#include "tls_session_reuse.c"
#include "upload_pausing.c"
#include "ws_data.c"
#include "ws_pingpong.c"

const struct entry_s s_entries[] = {
  {"h2_pausing", test_h2_pausing},
  {"h2_serverpush", test_h2_serverpush},
  {"h2_upgrade_extreme", test_h2_upgrade_extreme},
  {"hx_download", test_hx_download},
  {"hx_upload", test_hx_upload},
  {"tls_session_reuse", test_tls_session_reuse},
  {"upload_pausing", test_upload_pausing},
  {"ws_data", test_ws_data},
  {"ws_pingpong", test_ws_pingpong},
  {NULL, NULL}
};

#include "first.c"
