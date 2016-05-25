import cffi
from fir import general_const
from pynq import Overlay

class fir():
    def __init__(self):
        self.bitfile = general_const.BITFILE
        self.libfile = general_const.LIBRARY
        self.response = []
        self.nshift_reg = 85

    def __version__(self):
        return "0.1"

    def initHw(self):
        self.overlay = Overlay(self.bitfile)
        self.overlay.download()
        self.ffi = cffi.FFI()
        self.lib = self.ffi.dlopen(self.libfile)
        self.ffi.cdef("void _p0_cpp_FIR_0(int x, int * ret);")

    def getResponse(self,datain = [0] * 85):
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
        resp = []
        tmp = self.ffi.new("int *")
        self.lib._p0_cpp_FIR_0(self.ffi.cast("int",1),tmp)
        resp.append(tmp[0])
        for i in range(self.nshift_reg):
            self.lib._p0_cpp_FIR_0(self.ffi.cast("int",0),tmp)
            resp.append(tmp[0])
        return resp
