/*
© Copyright 2013 - 2016 Xilinx, Inc. All rights reserved. 

This file contains confidential and proprietary information of Xilinx, Inc. and
is protected under U.S. and international copyright and other intellectual
property laws.

DISCLAIMER 
This disclaimer is not a license and does not grant any rights to the materials
distributed herewith. Except as otherwise provided in a valid license issued to
you by Xilinx, and to the maximum extent permitted by applicable law: (1) THESE
MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL FAULTS, AND XILINX HEREBY
DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY,
INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, OR
FITNESS FOR ANY PARTICULAR PURPOSE; and (2) Xilinx shall not be liable (whether
in contract or tort, including negligence, or under any other theory of
liability) for any loss or damage of any kind or nature related to, arising
under or in connection with these materials, including for any direct, or any
indirect, special, incidental, or consequential loss or damage (including loss
of data, profits, goodwill, or any type of loss or damage suffered as a result
of any action brought by a third party) even if such damage or loss was
reasonably foreseeable or Xilinx had been advised of the possibility of the
same.

CRITICAL APPLICATIONS
Xilinx products are not designed or intended to be fail-safe, or for use in any
application requiring fail-safe performance, such as life-support or safety
devices or systems, Class III medical devices, nuclear facilities, applications
related to the deployment of airbags, or any other applications that could lead
to death, personal injury, or severe property or environmental damage
(individually and collectively, "Critical Applications"). Customer assumes the
sole risk and liability of any use of Xilinx products in Critical Applications,
subject only to applicable laws and regulations governing limitations on product
liability.

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT
ALL TIMES. 
*/

#ifndef D_cf_request
#define D_cf_request

#include "cf_context.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CF_REQUEST_INFO_SIZE (sizeof(cf_request_info_t) + 32 * sizeof(void *))

typedef struct cf_request_handlers_struct cf_request_handlers_t;
typedef struct cf_request_on_free_handler_struct cf_request_on_free_handler_t;

typedef enum {
	CF_REQ_STATE_WAITING,
	CF_REQ_STATE_ACTIVE,
	CF_REQ_STATE_DONE
} cf_request_state_t;

struct cf_request_handlers_struct {
	int (*test_req)(cf_request_info_t *, int poll);
	void (*release_ref)(cf_request_info_t *);
};

struct cf_request_on_free_handler_struct {
	cf_request_on_free_handler_t *next;
	void (*handler)(void *client_data);
	void *client_data;
};

struct cf_request_info_struct {
	cf_status_t status;
	int state;
	int wait_trace_tag;
	cf_context_t *context;
	cf_request_handlers_t *handlers;
	cf_request_on_free_handler_t *on_free_handlers;
};

extern cf_request_info_t *cf_request_alloc(
	unsigned int size,
	cf_request_handlers_t *handlers);

extern int cf_request_prealloc(
	cf_context_t *context,
	unsigned int count);

extern void cf_request_add_on_free_handler(
	cf_request_info_t *request,
	void (*handler)(void *client_data),
	void *client_data);

extern void cf_request_free(
	cf_request_info_t *request);

#ifdef __cplusplus
}
#endif

#endif /* D_cf_request */

// 67d7842dbbe25473c3c32b93c0da8047785f30d78e8a024de1b57352245f9689
