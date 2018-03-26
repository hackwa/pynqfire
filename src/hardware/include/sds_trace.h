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

/*
 * sdsoc_trace.h
 *
 *  Created on: Sep 2, 2015
 *      Author: sskalick
 */

#ifndef SDSOC_TRACE_H_
#define SDSOC_TRACE_H_

typedef struct trace_entry_struct {
	long long unsigned timestamp;
	unsigned type;
	unsigned ID;
} sds_trace_entry;

typedef struct trace_list_struct {
	sds_trace_entry *entries;
	unsigned int used;
	unsigned int size;
	struct trace_list_struct *next;
} sds_trace_list;

void trace_list_add(long long unsigned timestamp, unsigned type, unsigned ID);
void sds_trace_setup(void);
void sds_trace_reset(void);
void sds_trace_cleanup(void);
void _sds_print_trace_entry(sds_trace_entry *entry);
void _sds_print_trace(void);
void _sds_trace_log_HW(unsigned ID, unsigned type);
void _sds_trace_log_SW(unsigned ID, unsigned type);
void sds_trace(unsigned ID, unsigned type);
void sds_trace_stop(void);

#endif /* SDSOC_TRACE_H_ */

// 67d7842dbbe25473c3c32b93c0da8047785f30d78e8a024de1b57352245f9689
