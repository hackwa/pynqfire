from dmadefs import *

lib = ffi.dlopen("/home/xpp/dma/libdma.so")

class DMA():
    
    def __init__(self,address):
        # Pick a random direction
        self.info = ffi.new("axi_dma_simple_info_t *")
        global device_id
        self.info.device_id = device_id
        device_id = device_id + 1
        self.info.phys_base_addr = address
        self.info.addr_range = 0x10000
        self.info.dir = DMA_TO_DEV
        self.channel = ffi.new("axi_dma_simple_channel_info_t *")
        self.channel.dma_info = self.info
        self.channel. in_use = 0
        self.channel.needs_cache_flush_invalidate = 0
        self.num_recd = ffi.new("int *")
        self.sent_data = 0
        
    def dma_register(self):
        lib.custom_dma_register(self.info.device_id)
        
    def dma_unregister(self):
        lib.custom_dma_unregister(self.info.device_id)
    
    def dma_open(self):
        lib.custom_dma_open(self.channel, self.info.device_id)

    def dma_close(self):
        lib.custom_dma_close(self.channel, self.info.device_id)
        
    def dma_send(self,buf,length):
        lib.custom_dma_send_i(self.channel,buf,length,self.info.device_id)
        
    def dma_recv(self,buf,length):
        self.info.dir = DMA_FROM_DEV
        self.sent_data = length
        lib.custom_dma_recv_i(self.channel,buf,length,self.num_recd,self.info.device_id)

    def dma_wait(self):
        lib.custom_dma_wait(self.info.device_id)