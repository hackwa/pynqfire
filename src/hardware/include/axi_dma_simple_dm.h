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

#ifndef AXI_DMA_SIMPLE_DM_H
#define AXI_DMA_SIMPLE_DM_H

#include <stdint.h>
#include "cf_lib.h"
#include "sysport_info.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct axi_dma_simple_info_struct {
	char* name;
	int dm_id;
	int device_id;
	uint64_t phys_base_addr;
	int addr_range;
	void* virt_base_addr;
	int dir;
	int irq;
	sysport_info_t* data_sysport;
	int data_width;
	int in_use;
	uint64_t sd_driver_data; //only used by "standard" driver until that becomes mainstream.
} axi_dma_simple_info_t;

int axi_dma_simple_open (axi_dma_simple_info_t* info);
int axi_dma_simple_close (axi_dma_simple_info_t* info);

int axi_dma_simple_send_ref_i (cf_port_send_t *port,
		const void *buf,
		unsigned int len,
		cf_request_handle_t *request);

int axi_dma_simple_send_i (cf_port_send_t *port,
		const void *buf,
		unsigned int len,
		cf_request_handle_t *request);

int axi_dma_simple_recv_i (cf_port_receive_t *port,
		void *buf,
		unsigned int len,
		unsigned int *num_recd,
		cf_request_handle_t *request);

int axi_dma_simple_recv_ref_i (cf_port_receive_t *port,
		void **buf,
		unsigned int *len,
		cf_request_handle_t *request);

#ifdef __cplusplus
};
#endif

#endif


// 67d7842dbbe25473c3c32b93c0da8047785f30d78e8a024de1b57352245f9689
