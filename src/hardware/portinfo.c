/* File: /home/seanf/workspace/fir-sf/Release/_sds/p0/.cf_work/portinfo.c */
#include "cf_lib.h"
#include "cf_request.h"
#include "sds_lib.h"
#include "sds_trace.h"
#include "portinfo.h"
#include "stdio.h"  // for printf
#include "xlnk_core_cf.h"
#include "accel_info.h"
#include "axi_dma_sg_dm.h"
#include "axi_lite_dm.h"
#include "sysport_info.h"

sysport_info_t _sds_sysport_p0_ps7_0_S_AXI_ACP = {
  .name = "ps7_0_S_AXI_ACP",
  .id = 1,
  .address_space = 0,
  .cmd_type = sysport_commands_type_no_action,
};

accel_info_t _sds__p0_cpp_FIR_1 = {
  .device_id = 0,
  .phys_base_addr = 0x83c00000,
  .addr_range = 0x10000,
  .func_name = "cpp_FIR_1",
  .ip_type = "axis_acc_adapter",
  .irq = 0,
};

axi_dma_sg_info_t _p0_dm_0 = {
  .name = "dm_0",
  .phys_base_addr = 0x80400000,
  .addr_range = 0x10000,
  .seq_num = 0,
  .chan_data[0].valid = 1,
  .chan_data[0].name = "dm_0:0",
  .chan_data[0].dir = XLNK_DMA_TO_DEV,
  .chan_data[0].irq = 62,
  .chan_data[0].data_sysport = &_sds_sysport_p0_ps7_0_S_AXI_ACP,
  .chan_data[0].data_width = 64,
  .chan_data[1].valid = 1,
  .chan_data[1].name = "dm_0:1",
  .chan_data[1].dir = XLNK_DMA_FROM_DEV,
  .chan_data[1].irq = 63,
  .chan_data[1].data_sysport = &_sds_sysport_p0_ps7_0_S_AXI_ACP,
  .chan_data[1].data_width = 64,
};

int _p0_swinst_cpp_FIR_1_cmd_cpp_FIR_sg_list[] = {0x80c, 0x8};

axi_lite_info_t _p0_swinst_cpp_FIR_1_cmd_cpp_FIR_info = {
  .phys_base_addr = 0x83c00000,
  .data_reg_offset = _p0_swinst_cpp_FIR_1_cmd_cpp_FIR_sg_list,
  .data_reg_sg_size = 2,
  .write_status_reg_offset = 0x0,
  .read_status_reg_offset = 0x0,
  .config = XLNK_AXI_LITE_SG |
    XLNK_AXI_LITE_STAT_REG_READ(XLNK_AXI_LITE_STAT_REG_NOCHECK) |
    XLNK_AXI_LITE_STAT_REG_WRITE(XLNK_AXI_LITE_STAT_REG_NOCHECK),
  .acc_info = &_sds__p0_cpp_FIR_1,
};

axi_dma_sg_transaction_info_t _p0_swinst_cpp_FIR_1_x_PORTA_info = {
  .dma_info = &_p0_dm_0,
  .dma_channel = 0,
  .port_id = 0,
};

axi_dma_sg_transaction_info_t _p0_swinst_cpp_FIR_1_w_PORTA_info = {
  .dma_info = &_p0_dm_0,
  .dma_channel = 0,
  .port_id = 1,
};

axi_dma_sg_transaction_info_t _p0_swinst_cpp_FIR_1_ret_PORTA_info = {
  .dma_info = &_p0_dm_0,
  .dma_channel = 1,
  .port_id = 0,
};

int _p0_swinst_cpp_FIR_1_datalen_sg_list[] = {0xc};

axi_lite_info_t _p0_swinst_cpp_FIR_1_datalen_info = {
  .phys_base_addr = 0x83c00000,
  .data_reg_offset = _p0_swinst_cpp_FIR_1_datalen_sg_list,
  .data_reg_sg_size = 1,
  .write_status_reg_offset = 0x40c,
  .read_status_reg_offset = 0x0,
  .config = XLNK_AXI_LITE_KEYHOLE |
    XLNK_AXI_LITE_STAT_REG_READ(XLNK_AXI_LITE_STAT_REG_NONE) |
    XLNK_AXI_LITE_STAT_REG_WRITE(XLNK_AXI_LITE_STAT_REG_QUEUING),
  .acc_info = &_sds__p0_cpp_FIR_1,
};

struct _p0_swblk_cpp_FIR _p0_swinst_cpp_FIR_1 = {
  .cmd_cpp_FIR = { .base = { .channel_info = &_p0_swinst_cpp_FIR_1_cmd_cpp_FIR_info}, 
    .send_i = &axi_lite_send },
  .x_PORTA = { .base = { .channel_info = &_p0_swinst_cpp_FIR_1_x_PORTA_info}, 
    .send_i = &axi_dma_sg_send_i },
  .w_PORTA = { .base = { .channel_info = &_p0_swinst_cpp_FIR_1_w_PORTA_info}, 
    .send_i = &axi_dma_sg_send_i },
  .ret_PORTA = { .base = { .channel_info = &_p0_swinst_cpp_FIR_1_ret_PORTA_info}, 
    .receive_ref_i = 0,
    .receive_i = &axi_dma_sg_recv_i },
  .datalen = { .base = { .channel_info = &_p0_swinst_cpp_FIR_1_datalen_info}, 
    .send_i = &axi_lite_send },
};

extern void pfm_hook_init();
extern void pfm_hook_shutdown();
void _p0_cf_framework_open(int first)
{
  int xlnk_init_done;
  cf_context_init();
  xlnkCounterMap(650000000);
  xlnk_init_done = cf_xlnk_open(first);
  if (!xlnk_init_done) {
    pfm_hook_init();
    cf_xlnk_init(first);
  } else if (xlnk_init_done < 0) {
    fprintf(stderr, "ERROR: unable to open xlnk\n");
    exit(-1);
  }
  cf_get_current_context();
  sysport_open(&_sds_sysport_p0_ps7_0_S_AXI_ACP);
  axi_dma_sg_open(&_p0_dm_0);
  axi_lite_open(&_p0_swinst_cpp_FIR_1_cmd_cpp_FIR_info);
  axi_lite_open(&_p0_swinst_cpp_FIR_1_datalen_info);
  _sds__p0_cpp_FIR_1.arg_dm_id[0] = _p0_swinst_cpp_FIR_1_cmd_cpp_FIR_info.dm_id;
  _sds__p0_cpp_FIR_1.arg_dm_id[1] = _p0_swinst_cpp_FIR_1_x_PORTA_info.dma_info->chan_data[_p0_swinst_cpp_FIR_1_x_PORTA_info.dma_channel].dm_id;
  _sds__p0_cpp_FIR_1.arg_dm_id[2] = _p0_swinst_cpp_FIR_1_w_PORTA_info.dma_info->chan_data[_p0_swinst_cpp_FIR_1_w_PORTA_info.dma_channel].dm_id;
  _sds__p0_cpp_FIR_1.arg_dm_id[3] = _p0_swinst_cpp_FIR_1_ret_PORTA_info.dma_info->chan_data[_p0_swinst_cpp_FIR_1_ret_PORTA_info.dma_channel].dm_id;
  _sds__p0_cpp_FIR_1.arg_dm_id[4] = _p0_swinst_cpp_FIR_1_datalen_info.dm_id;
  _sds__p0_cpp_FIR_1.arg_dm_id_count = 5;
  accel_open(&_sds__p0_cpp_FIR_1);
}

void _p0_cf_framework_close(int last)
{
  accel_close(&_sds__p0_cpp_FIR_1);
  axi_dma_sg_close(&_p0_dm_0);
  axi_lite_close(&_p0_swinst_cpp_FIR_1_cmd_cpp_FIR_info);
  axi_lite_close(&_p0_swinst_cpp_FIR_1_datalen_info);
  sysport_close(&_sds_sysport_p0_ps7_0_S_AXI_ACP);
  pfm_hook_shutdown();
  xlnkClose(last, NULL);
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

