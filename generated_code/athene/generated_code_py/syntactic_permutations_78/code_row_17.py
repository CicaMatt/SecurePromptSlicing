import ctypes

class MemoryBlock:
    def __init__(self, size):
        self.size = size
        self.ptr = ctypes.c_void_p(0)
        self.status = -1
        self.allocate()

    def allocate(self):
        self.ptr = ctypes.pythonapi.PyMem_Malloc(ctypes.c_size_t(self.size))
        if self.ptr:
            self.status = 0

block = MemoryBlock(1024)