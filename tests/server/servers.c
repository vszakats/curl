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

#include "getpart.c"
#include "util.c"

#include "../../lib/curlx/base64.c"
#include "../../lib/curlx/inet_pton.c"
#include "../../lib/curlx/inet_ntop.c"
#include "../../lib/curlx/multibyte.c"
#include "../../lib/curlx/nonblock.c"
#include "../../lib/curlx/strparse.c"
#include "../../lib/curlx/timediff.c"
#include "../../lib/curlx/timeval.c"
#include "../../lib/curlx/version_win32.c"
#include "../../lib/curlx/wait.c"
#include "../../lib/curlx/warnless.c"
#include "../../lib/curlx/winapi.c"

#include "dnsd.c"
#include "mqttd.c"
#include "resolve.c"
#include "rtspd.c"
#include "sockfilt.c"
#include "socksd.c"
#include "sws.c"
#include "tftpd.c"

const struct entry_s s_entries[] = {
  {"dnsd", test_dnsd},
  {"mqttd", test_mqttd},
  {"resolve", test_resolve},
  {"rtspd", test_rtspd},
  {"sockfilt", test_sockfilt},
  {"socksd", test_socksd},
  {"sws", test_sws},
  {"tftpd", test_tftpd},
  {NULL, NULL}
};

#include "first.c"
