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
Associated Filename: cpp_FIR.h
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
(individually and collectively, "Critical Applications"). Customer assumes the 
sole risk and liability of any use of Xilinx products in Critical Applications, 
subject only to applicable laws and regulations governing limitations on product 
liability. 

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT 
ALL TIMES.

*******************************************************************************/
#ifndef _CPP_FIR_H_
#define _CPP_FIR_H_

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

#define N 85
#define B 500000

typedef int coef_t;
typedef int data_t;
typedef int acc_t;


// Class CFir definition
template<class coef_T, class data_T, class acc_T>
class CFir {
protected:
  data_T shift_reg[N-1];
private:
public:
  data_T operator()(data_T x, coef_T w[N]);
  template<class coef_TT, class data_TT, class acc_TT>
  friend ostream&
  operator<<(ostream& o, const CFir<coef_TT, data_TT, acc_TT> &f);

};

// FIR main algorithm
template<class coef_T, class data_T, class acc_T>
data_T CFir<coef_T, data_T, acc_T>::operator()(data_T x, coef_T w[N]) {
#pragma HLS PIPELINE II=1
#pragma HLS ARRAY_PARTITION partition variable=shift_reg dim=1
#pragma HLS ARRAY_PARTITION partition variable=w complete dim=1

	int i;
	acc_t acc = 0;
	data_t m;

	loop: for (i = N-1; i >= 0; i--) {
	#pragma HLS UNROLL
		if (i == 0) {
			m = x;
			shift_reg[0] = x;
		} else {
			m = shift_reg[i-1];
			if (i != (N-1) )
				shift_reg[i] = shift_reg[i - 1];
		}
		acc += m * w[i];
	}
	return acc;
}

#pragma SDS data access_pattern(x:SEQUENTIAL, ret:SEQUENTIAL)
#pragma SDS data copy(x[0:datalen], ret[0:datalen])
#pragma SDS data data_mover(x:AXIDMA_SIMPLE, w:AXIDMA_SIMPLE, ret:AXIDMA_SIMPLE)
#pragma SDS data mem_attribute(x:PHYSICAL_CONTIGUOUS, w:PHYSICAL_CONTIGUOUS, ret:PHYSICAL_CONTIGUOUS)
void cpp_FIR(data_t x[B], coef_t w[N], data_t ret[B], data_t datalen);

#endif

