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
from pynq import Overlay

class fir():
    """Class which controls fir filter hardware

    Attributes
    ----------
    bitfile : str
        Absolute path of bitstream file
    libfile : str
        Absolute path of shared library
    response: list
        Filter output
    nshift_reg : int
        Number of shift regs on hardware
    overlay : Overlay
        Gives access to bitstream overlay

    """

    def __init__(self):
        self.bitfile = general_const.BITFILE
        self.libfile = general_const.LIBRARY
        self.response = []
        self.nshift_reg = 85
        self.overlay = None

    def __version__(self):
        return "0.1"

    def initHw(self):
        """Initialize Hardware

        Downloads the bitstream onto hardware using overlay.
        Reads the Shared Object and initializes CFFI.
        Always run this before performing any operations.

        Parameters
        ----------
        None

        Returns
        -------
        None

        """
        self.overlay = Overlay(self.bitfile)
        self.overlay.download()
        self.ffi = cffi.FFI()
        self.lib = self.ffi.dlopen(self.libfile)
        self.ffi.cdef("void _p0_cpp_FIR_0(int x, int * ret);")

    def getResponse(self,datain = [0] * 85):
        """Send input to hardware and get response

        This method takes samples of data and then processes
        them on hardware. At the end, it resets the FIR Shift
        Registers.

        Parameters
        ----------
        datain : list
            A list containing input samples

        Returns
        -------
        None
            Use response attribute to read output.

        """
        dlen = len(datain)
        resp = self.ffi.new("int *") 
        self.response = [None] * dlen
        for i in range(dlen):
            self.lib._p0_cpp_FIR_0(self.ffi.cast("int",datain[i]),resp)
            self.response[i] = resp[0]

        # Reset FIR Shift Regs
        tmp = self.ffi.new("int *")
        for i in range(self.nshift_reg):
            self.lib._p0_cpp_FIR_0(self.ffi.cast("int",0),tmp)

    def impulseResponse(self):
        """Get impulse Response of filter

        This method sends an impulse to the filter and returns
        the output response.

        Paramters
        ---------
        None

        Returns
        -------
        list
            A list containing the filter response

        """
        resp = []
        tmp = self.ffi.new("int *")
        self.lib._p0_cpp_FIR_0(self.ffi.cast("int",1),tmp)
        resp.append(tmp[0])
        for i in range(self.nshift_reg):
            self.lib._p0_cpp_FIR_0(self.ffi.cast("int",0),tmp)
            resp.append(tmp[0])
        return resp
