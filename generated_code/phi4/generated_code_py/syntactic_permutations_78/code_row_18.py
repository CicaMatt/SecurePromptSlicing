import ctypes

class MemoryAllocator:
    def __init__(self):
        self.memory = []

    def allocate(self, size):
        block = (ctypes.c_char * size)()
        self.memory.append(block)
        for i in range(size):
            block[i] = 0
        return ctypes.addressof(block)

# Example usage
allocator = MemoryAllocator()
ptr = allocator.allocate(10)
print(f"Memory allocated at address: {ptr}")