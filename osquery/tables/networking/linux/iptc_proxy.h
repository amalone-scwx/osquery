/**
 * Copyright (c) 2014-present, The osquery authors
 *
 * This source code is licensed as defined by the LICENSE file found in the
 * root directory of this source tree.
 *
 * SPDX-License-Identifier: (Apache-2.0 OR GPL-2.0-only)
 */

#pragma once

#include <net/if.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdbool.h>

struct iptcproxy_handle;
typedef struct iptcproxy_handle iptcproxy_handle;

struct iptcproxy_chain {
  const char* chain;

  const char* policy;
  struct {
    uint64_t pcnt;
    uint64_t bcnt;
  } policy_data;
};
typedef struct iptcproxy_chain iptcproxy_chain;

struct iptcproxy_rule {
  const char* target;

  bool match;
  struct {
    bool valid;
    uint16_t spts[2];
    uint16_t dpts[2];
  } match_data;

  struct {
    struct in_addr src, dst;
    struct in_addr smsk, dmsk;
    char iniface[IFNAMSIZ], outiface[IFNAMSIZ];
    unsigned char iniface_mask[IFNAMSIZ], outiface_mask[IFNAMSIZ];
    uint16_t proto;
    uint16_t flags;
    uint8_t invflags;
  } ip_data;
};
typedef struct iptcproxy_rule iptcproxy_rule;

const iptcproxy_handle* iptcproxy_init(const char* filter);
void iptcproxy_free(const iptcproxy_handle* handle);

const iptcproxy_chain* iptcproxy_first_chain(const iptcproxy_handle* handle);
const iptcproxy_chain* iptcproxy_next_chain(const iptcproxy_handle* handle);

const iptcproxy_rule* iptcproxy_first_rule(
    const char* chain,
    const iptcproxy_handle* handle);
const iptcproxy_rule* iptcproxy_next_rule(
    const iptcproxy_handle* handle);
