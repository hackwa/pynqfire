/* File: C:/test6/firf_wHDMI/SDDebug/_sds/p0/.cf_work/devreg.c */
#include "cf_lib.h"
#include "cf_request.h"
#include "devreg.h"

#include "stdio.h"  // for getting printf
#include "xlnk_core_cf.h"
#include "accel_info.h"
#include "axi_dma_simple_dm.h"
#include "axi_lite_dm.h"

axi_dma_simple_info_t _p0_dm_0 = {
  .device_id = 0,
  .phys_base_addr = 0x40400000,
  .addr_range = 0x10000,
  .dir = XLNK_DMA_TO_DEV,
};

axi_dma_simple_info_t _p0_dm_1 = {
  .device_id = 1,
  .phys_base_addr = 0x40410000,
  .addr_range = 0x10000,
  .dir = XLNK_DMA_FROM_DEV,
};

accel_info_t _sds__p0_cpp_FIR_0 = {
  .device_id = 2,
  .phys_base_addr = 0x43c30000,
  .addr_range = 0x10000,
  .ip_type = "axis_acc_adapter"
};

void _p0_cf_register(int first)
{
  int xlnk_init_done = cf_xlnk_open(first);
  if (xlnk_init_done == 0) {
    axi_dma_simple_register(&_p0_dm_0);
    axi_dma_simple_register(&_p0_dm_1);
    accel_register(&_sds__p0_cpp_FIR_0);
    cf_xlnk_init(first);
  }
  else if (xlnk_init_done <0) {
    fprintf(stderr, "ERROR: unable to open xlnk %d\n", xlnk_init_done);
  }
  else {
  }
}

void _p0_cf_unregister(int last)
{
  axi_dma_simple_unregister(&_p0_dm_0);
  axi_dma_simple_unregister(&_p0_dm_1);
  accel_unregister(&_sds__p0_cpp_FIR_0);
  xlnkClose(last,NULL);
}

