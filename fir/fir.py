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
        ffi = cffi.FFI()
        self.lib = ffi.dlopen(self.libfile)
        ffi.cdef("void _p0_cpp_FIR_0(int x, int * ret);")
        ffi.cdef("void _Z13_p0_cpp_FIR_0iPi(int x, int * ret);")

    def getResponse(self,datain = [0] * 85):
        dlen = len(datain)
        self.response = [ffi.new("int",i)] * dlen
        for i in range(dlen):
            self.lib._Z13_p0_cpp_FIR_0iPi(ffi.cast("int",datain[i]),self.response[i])
        
        # Reset FIR Shift Regs
        tmp = ffi.new("int")
        for i in range(nshift_reg):
            self.lib._Z13_p0_cpp_FIR_0iPi(ffi.cast("int",0),tmp)
