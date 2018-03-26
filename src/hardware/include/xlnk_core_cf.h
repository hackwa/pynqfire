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

#ifndef XLNK_CORE_CF_H
#define XLNK_CORE_CF_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// the following are for xlnkDMARegister
#define	XLNK_DMA_TO_DEV  1
#define	XLNK_DMA_FROM_DEV  2
#define XLNK_BI_DIRECTIONAL  0
// the following are from xlnk-os.h (but the DMA_TO and DMA_FROM flags are not
#define XLNK_FLAG_COHERENT  		0x00000001
#define XLNK_FLAG_KERNEL_BUFFER		0x00000002
#define XLNK_FLAG_DMAPOLLING		0x00000004
#define XLNK_FLAG_PHYSICAL_ADDR		0x00000100
#define XLNK_FLAG_VIRTUAL_ADDR		0x00000200

#define CF_FLAG_CACHE_FLUSH_INVALIDATE 0x00000001
#define CF_FLAG_PHYSICALLY_CONTIGUOUS  0x00000002
#define CF_FLAG_DMAPOLLING             0x00000004

extern int cf_xlnk_open(int first);
extern void cf_xlnk_init(int last);
extern void xlnkCounterMap(uint64_t);
extern int xlnkClose(unsigned int last, void* argp);

#ifdef __cplusplus
};
#endif
#endif


// 67d7842dbbe25473c3c32b93c0da8047785f30d78e8a024de1b57352245f9689
