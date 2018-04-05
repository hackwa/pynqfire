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

#ifndef D_sds_lib
#define D_sds_lib

#ifdef __cplusplus
extern "C" {
#endif
/* wait for the first request list in the queue identified by id, to complete */
extern void sds_wait( unsigned int id);

/* poll whether or not a wait is complete */
extern int sds_try_wait( unsigned int id);

/* allocate a physically contiguous array of size bytes for DMA transfers */
extern void *sds_alloc( unsigned int size);

/* allocate a physically contiguous array of size bytes for DMA transfers.
   Same as sds_alloc() */
extern void *sds_alloc_cacheable( unsigned int size);

/* allocate a physically contiguous array of size bytes for DMA transfers, but
   mark the pages as non-cacheable */
extern void *sds_alloc_non_cacheable( unsigned int size);

/* free an array allocated through sds_alloc */
extern void sds_free(void *memptr);

/* Create a virtual address mapping to access a memory of size size bytes located at physical address physical_addr
 physical_addr: physical address to be mapped
          size: size of physical address to be mapped
  virtual_addr: If a non-null value is passed in, it is considered to be 
                the virtual-address already mapped to the physical_addr, and cf_mmap keeps track of the mapping
                If a null value is passed in, cf_mmap invokes mmap() to generate the virtual address, and 
                virtual_addr is assigned this value */
extern void *sds_mmap( void *physical_addr, unsigned int size, void *virtual_addr);

/* register a handle between a given userspace virtual address and an FD that
   corresponds to a handle to a GEM-allocated buffer */  
extern int sds_register_dmabuf(void *virtual_addr, int fd);
  
/* unregister a handle between a given userspace virtual address and an FD that
   corresponds to a handle to a GEM-allocated buffer that was previously
   registered by using sds_register_dmabuf() */  
extern int sds_unregister_dmabuf(void *virtual_addr, int fd);
  
/* unmaps a virtual address mapped associated with a physical address using sds_mmap() */
extern void sds_munmap( void *virtual_addr);

/* returns the value associated with a free-running counter used for fine grain time-interval measurements */
extern unsigned long long sds_clock_counter(void);

/* returns the frequency associated with the free-running counter that is read by calls to sds_clock_counter
   this is used to translate counter ticks to seconds */
extern unsigned long long sds_clock_frequency(void);

/* stops the global counter, sets the global counter to the given value, then starts it running again from the given value */
extern void sds_set_counter(unsigned long long val);

/* do not use - this is for internal use only, and will be removed from this header */
/* function called by automatically generated stub code to insert a handle onto a queue 
   The user then calls sds_wait with the same id to wait for the request to complete
   paramters: id: queue ID
              req: opaque pointer to a request list allocated by the function
	      num: number of items in the request list
*/
extern void sds_insert_req( unsigned int id, void *req, int num);

/* These functions are for platform developers to register memory space characteristics */

/* Called from pfm init code when defining remote memory.
 * parameters: remote_mem_count: number of non-PS non-SW accessable memories that are to be managed by sdsoc
 * */
extern void sds_remote_memory_init(int remote_mem_count);

/* Called from pfm init code to define an analagous malloc/free pair associated with a remote memory.
 * parameters:	remote_memory_num: id of the remote memory being configured
 *		rm_alloc: remote-memory alloc.  A callback that takes a size as an argument, and returns a valid uint64_t to represent the remote physical address.
 *		rm_free: remote-memory free.  A callback that takes an address, and surrenders it for future re-assignment
 *		rm_struct: a structure that is passed to all registered callbacks to represent internal data structures
 * */
extern void sds_register_remote_memory_allocator(int remote_memory_num, unsigned long long (*rm_alloc)(void* rm_struct, unsigned int alloc_size), void (*rm_free)(void* rm_struct, unsigned long long), void* rm_struct);
/* Called from pfm init code when defining a driver to manage transfer to/from a remote memory
 * parameters:	src_memory_num: id of the source memory, -1 for PS memory
 *		dst_memory_num: id of the destination memory, -1 for PS memory
 *		transfer: a function that actually performs a transfer.  When the transfer is compelted, the function calls cb(cbArgs) to indicate done status
 *		rm_struct: a structure that is passed to the registered callback to represent internal data structures.
 * */
extern void sds_register_remote_memory_transfer(int src_memory_num, int dst_memory_num, int (*transfer)(void* rm_struct, void* ps_virt_addr, unsigned long long srcAddr, unsigned long long dstAddr, unsigned int size, void (*cb)(void*), void* cbArgs), void* rm_struct);

/* Called to define the source of a memory bank as the local PS memory */
extern int sds_local_memory_id(void);


#define SDS_INSTRUMENT_MAX_ARGS 16

struct hw_function_perf_instrumentation {
	unsigned long long config_send_start;
	unsigned long long config_send_end;
	unsigned long long config_wait_start;
	unsigned long long config_wait_end;
	unsigned long long arg_send_start[SDS_INSTRUMENT_MAX_ARGS];
	unsigned long long arg_send_end[SDS_INSTRUMENT_MAX_ARGS];
	unsigned long long arg_recv_start[SDS_INSTRUMENT_MAX_ARGS];
	unsigned long long arg_recv_end[SDS_INSTRUMENT_MAX_ARGS];
	unsigned long long wait_start;
	unsigned long long wait_end;
};

extern void reset_hw_perf_instr_struct(void);
extern struct hw_function_perf_instrumentation *get_hw_perf_instr_struct(void);

/* Trace Event Types */
#define EVENT_START 0x04
#define EVENT_STOP 0x05

#ifdef __cplusplus
}
#endif

#endif /* D_sds_lib */



// 67d7842dbbe25473c3c32b93c0da8047785f30d78e8a024de1b57352245f9689
