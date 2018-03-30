/*
(c) Copyright 2013 - 2016 Xilinx, Inc. All rights reserved. 

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

/*******************************************************************************
Vendor: Xilinx 
Associated Filename: cpp_FIR_test.cpp
Purpose:Vivado HLS Coding Style example 
Device: All 
Revision History: May 30, 2008 - initial release
                                                
*******************************************************************************
Copyright (C) 2013 XILINX, Inc. 

This file contains confidential and proprietary information of Xilinx, Inc. and 
is protected under U.S. and international copyright and other intellectual 
property laws.

DISCLAIMER
This disclaimer is not a license and does not grant any rights to the materials 
distributed herewith. Except as otherwise provided in a valid license issued to 
you by Xilinx, and to the maximum extent permitted by applicable law: 
(1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL FAULTS, AND XILINX 
HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, 
INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, OR 
FITNESS FOR ANY PARTICULAR PURPOSE; and (2) Xilinx shall not be liable (whether 
in contract or tort, including negligence, or under any other theory of 
liability) for any loss or damage of any kind or nature related to, arising under 
or in connection with these materials, including for any direct, or any indirect, 
special, incidental, or consequential loss or damage (including loss of data, 
profits, goodwill, or any type of loss or damage suffered as a result of any 
action brought by a third party) even if such damage or loss was reasonably 
foreseeable or Xilinx had been advised of the possibility of the same.

CRITICAL APPLICATIONS
Xilinx products are not designed or intended to be fail-safe, or for use in any 
application requiring fail-safe performance, such as life-support or safety 
devices or systems, Class III medical devices, nuclear facilities, applications 
related to the deployment of airbags, or any other applications that could lead 
to death, personal injury, or severe property or environmental damage 
(individually and collectively, "Critical Applications"). Customer asresultes the 
sole risk and liability of any use of Xilinx products in Critical Applications, 
subject only to applicable laws and regulations governing limitations on product 
liability. 

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT 
ALL TIMES.

*******************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <sds_lib.h>
#include "cpp_FIR.h"

class perf_counter
{
public:
     uint64_t tot, cnt, calls;
     perf_counter() : tot(0), cnt(0), calls(0) {};
     inline void reset() { tot = cnt = calls = 0; }
     inline void start() { cnt = sds_clock_counter(); calls++; };
     inline void stop() { tot += (sds_clock_counter() - cnt); };
     inline uint64_t avg_cpu_cycles() { return ((tot+(calls>>1)) / calls); };
};

static void 
fir_sw(data_t x[B], coef_t w[N], data_t ret[B], data_t datalen)
{
	static CFir<coef_t, data_t, acc_t> fir1;
	for (int i=0; i<datalen; i++)
	    ret[i] = fir1(x[i], w);
}

static void 
reset_firs(data_t xhw[B], data_t output[B], coef_t w[N], data_t output_sw[B], data_t datalen)
{
     cpp_FIR(xhw, w, output, datalen);
     fir_sw(xhw, w, output_sw, datalen);
}

int main()
{

	coef_t *w;
	data_t *x, *xhw, *output, *output_sw;

	w = (coef_t *)sds_alloc(int(N*sizeof(coef_t)));
	x = (data_t *)sds_alloc(int(B*sizeof(data_t)));
	xhw = (data_t *)sds_alloc(int(B*sizeof(data_t)));
	output = (data_t *)sds_alloc(int(B*sizeof(data_t)));
	output_sw = (data_t *)malloc(int(B*sizeof(data_t)));
	data_t datalen = 10000;

	// Load coeffs from file
	#include "coef.txt"

	// NOTE: HLS hardware leaves state in the IP, so must
	//       explicitly reset the shift register
	reset_firs(xhw, output, w, output_sw, datalen);

	//create input data
	for (int i = 0; i < datalen; i++) {
		x[i] = i;
	}

	perf_counter hw_ctr, sw_ctr;

	hw_ctr.start();
	cpp_FIR(x, w, output, datalen);  // compute
	hw_ctr.stop();
	sw_ctr.start();
	fir_sw(x, w, output_sw, datalen);
	sw_ctr.stop();

	for (int i = 0; i < datalen; i++) {
		if ( i<= 20 ) {
			std::cout << output[i] << ";" << output_sw[i] << std::endl;
		}
		if (output[i] != output_sw[i]) {
			std::cout << "Mismatch: cpp_FIR(" << i << ") = "
					  << output[i] << ";  fir_sw(" << i << ") = "
					  << output_sw[i] << std::endl;
			std::cout << "Test failed" << std::endl;
			return -1;
		}
	}
	std::cout << "Test passed" << std::endl;

	uint64_t sw_cycles = sw_ctr.avg_cpu_cycles();
	uint64_t hw_cycles = hw_ctr.avg_cpu_cycles();
	double speedup = (double) sw_cycles / (double) hw_cycles;

	std::cout << "Average number of CPU cycles running CFir in software: "
	   << sw_cycles << std::endl;
	std::cout << "Average number of CPU cycles running CFir in hardware: "
	   << hw_cycles << std::endl;
	std::cout << "Speed up: " << speedup << std::endl;

	sds_free(x);
	sds_free(w);
	sds_free(xhw);
	sds_free(output);
	free(output_sw);

	return 0;

  }


