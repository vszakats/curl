#ifndef HEADER_CURL_NETRC_H
#define HEADER_CURL_NETRC_H
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

#include "curl_setup.h"
#ifndef CURL_DISABLE_NETRC
#include "curlx/dynbuf.h"

struct store_netrc {
  struct dynbuf filebuf;
  char *filename;
  BIT(loaded);
};

typedef enum {
  NETRC_OK,
  NETRC_NO_MATCH,      /* no matching entry in the file */
  NETRC_SYNTAX_ERROR,  /* in the netrc file */
  NETRC_FILE_MISSING,  /* the netrc file does not exist */
  NETRC_OUT_OF_MEMORY, /* while parsing netrc */
  NETRC_LAST /* never used */
} NETRCcode;

const char *Curl_netrc_strerror(NETRCcode ret);
void Curl_netrc_init(struct store_netrc *s);
void Curl_netrc_cleanup(struct store_netrc *s);

NETRCcode Curl_parsenetrc(struct store_netrc *s, const char *host,
                          char **loginp, char **passwordp,
                          const char *filename);
  /* Assume: (*passwordp)[0]=0, host[0] != 0.
   * If (*loginp)[0] = 0, search for login and password within a machine
   * section in the netrc.
   * If (*loginp)[0] != 0, search for password within machine and login.
   */
#else
/* disabled */
#define Curl_parsenetrc(a,b,c,d,e,f) 1
#define Curl_netrc_init(x)
#define Curl_netrc_cleanup(x)
#endif

#endif /* HEADER_CURL_NETRC_H */
