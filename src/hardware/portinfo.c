/* File: /home/hackwad/workspace/filter/SDDebug/_sds/p0/.cf_work/portinfo.c */
#include "cf_lib.h"
#include "cf_request.h"
#include "devreg.h"

#include "portinfo.h"

#include "stdio.h"  // for printf

#include "xlnk_core_cf.h"
#include "accel_info.h"
#include "axi_lite_dm.h"

extern accel_info_t _sds__p0_cpp_FIR_0;

axi_lite_info_t _p0_swinst_cpp_FIR_0_cmd_cpp_FIR_info = {
  .accel_info = &_sds__p0_cpp_FIR_0,
  .reg_name = "0x28"
};

axi_lite_info_t _p0_swinst_cpp_FIR_0_x_info = {
  .accel_info = &_sds__p0_cpp_FIR_0,
  .reg_name = "0x80"
};

axi_lite_info_t _p0_swinst_cpp_FIR_0_ret_info = {
  .accel_info = &_sds__p0_cpp_FIR_0,
  .reg_name = "0xC0"
};

struct _p0_swblk_cpp_FIR _p0_swinst_cpp_FIR_0 = {
  .cmd_cpp_FIR = { .base = { 
		.channel_info = &_p0_swinst_cpp_FIR_0_cmd_cpp_FIR_info, 
		.open_i = &axi_lite_open, 
		.close_i = &axi_lite_close },
		.send_i = &axi_lite_send },
  .x = { .base = { 
		.channel_info = &_p0_swinst_cpp_FIR_0_x_info, 
		.open_i = &axi_lite_open, 
		.close_i = &axi_lite_close },
		.send_i = &axi_lite_send },
  .ret = { .base = { 
		.channel_info = &_p0_swinst_cpp_FIR_0_ret_info, 
		.open_i = &axi_lite_open, 
		.close_i = &axi_lite_close },
		.receive_i = &axi_lite_recv },
};

void _p0_cf_open_port (cf_port_base_t *port)
{
  port->open_i(port, NULL);
}

void _p0_cf_framework_open(int first)
{
  cf_context_init();
  xlnkCounterMap();
  _p0_cf_register(first);
  cf_get_current_context();
  accel_open(&_sds__p0_cpp_FIR_0);
  _p0_cf_open_port( &_p0_swinst_cpp_FIR_0.cmd_cpp_FIR.base );
  _p0_cf_open_port( &_p0_swinst_cpp_FIR_0.x.base );
  _p0_cf_open_port( &_p0_swinst_cpp_FIR_0.ret.base );
}

void _p0_cf_framework_close(int last)
{
  cf_close_i( &_p0_swinst_cpp_FIR_0.cmd_cpp_FIR, NULL);
  cf_close_i( &_p0_swinst_cpp_FIR_0.x, NULL);
  cf_close_i( &_p0_swinst_cpp_FIR_0.ret, NULL);
  accel_close(&_sds__p0_cpp_FIR_0);
  _p0_cf_unregister(last);
}

#define TOTAL_PARTITIONS 1
int current_partition_num = 0;
struct {
  void (*open)(int);
  void (*close)(int);
}

_ptable[TOTAL_PARTITIONS]  = {
    {.open = &_p0_cf_framework_open, .close= &_p0_cf_framework_close}, 
};

void switch_to_next_partition(int partition_num)
{
#ifdef __linux__
  if (current_partition_num != partition_num) {
    _ptable[current_partition_num].close(0);
    char buf[128];
    sprintf(buf, "cat /mnt/_sds/_p%d_.bin > /dev/xdevcfg", partition_num);
    system(buf);
    _ptable[partition_num].open(0);
    current_partition_num = partition_num;
  }
#endif
}

void init_first_partition() __attribute__ ((constructor));
void close_last_partition() __attribute__ ((destructor));
void init_first_partition()
{
    current_partition_num = 0;
    _ptable[current_partition_num].open(1);

    sds_trace_setup();
}


void close_last_partition()
{
#ifdef PERF_EST
    apf_perf_estimation_exit();
#endif
    sds_trace_cleanup();
    _ptable[current_partition_num].close(1);
    current_partition_num = 0;
}

