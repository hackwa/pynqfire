#   Copyright (c) 2016, Xilinx, Inc.
#   All rights reserved.
# 
#   Redistribution and use in source and binary forms, with or without 
#   modification, are permitted provided that the following conditions are met:
#
#   1.  Redistributions of source code must retain the above copyright notice, 
#       this list of conditions and the following disclaimer.
#
#   2.  Redistributions in binary form must reproduce the above copyright 
#       notice, this list of conditions and the following disclaimer in the 
#       documentation and/or other materials provided with the distribution.
#
#   3.  Neither the name of the copyright holder nor the names of its 
#       contributors may be used to endorse or promote products derived from 
#       this software without specific prior written permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
#   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
#   PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
#   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
#   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
#   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#   OR BUSINESS INTERRUPTION). HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
#   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
#   OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
#   ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

import cffi
from fir import general_const
from pynq import Overlay,PL

fir_overlay = None

class fir():
    """Class which controls fir filter hardware

    Attributes
    ----------
    bitfile : str
        Absolute path of bitstream file
    libfile : str
        Absolute path of shared library
    nshift_reg : int
        Number of shift regs on hardware
    overlay : Overlay
        Gives access to bitstream overlay

    """

    def __init__(self):
        self.bitfile = general_const.BITFILE
        self.libfile = general_const.LIBRARY
        self.nshift_reg = 85
        ffi = cffi.FFI()
        ffi.cdef("void _p0_cpp_FIR_1_noasync(int *x, int w[85], int *ret, int datalen)")
        self.lib = ffi.dlopen(self.libfile)
        if PL.bitfile_name != self.bitfile:
                self.download_bitstream()

    def download_bitstream(self):
        """Download the bitstream

        Downloads the bitstream onto hardware using overlay class.
        Also gives you access to overlay.

        Parameters
        ----------
        None

        Returns
        -------
        None

        """
        global fir_overlay
        fir_overlay = Overlay(self.bitfile)
        fir_overlay.download()

    def get_response(self,datain,win,dataout,datalen):
        """Send input to hardware and get response

        This method takes samples of data and then processes
        them on hardware. The FIR Shift can be reset at the
        end by sending a buffer filled with zeroes. This
        buffer needs to be at least 85 samples long.
        
        Note: `pynq.drivers.xlnk` class can be used to
        allocate and cast the buffers.

        Parameters
        ----------
        datain : A physically contiguous buffer
            containing input samples.
	win : A physically contiguous buffer
	    containing the filter coefficients
        dataout : A physically contiguous buffer
            which will hold output data.
        datalen : Number of samples.

        Returns
        -------
        None
            Use response attribute to read output.

        """
        if any("cdata" not in elem for elem in [str(datain),str(win),str(dataout)]):
                raise RuntimeError("Unknown buffer type!")
        self.lib._p0_cpp_FIR_1_noasync(datain,win,dataout,datalen)
