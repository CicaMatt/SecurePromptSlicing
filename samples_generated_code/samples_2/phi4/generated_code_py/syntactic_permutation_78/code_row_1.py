import ctypes

class MemoryAllocator:
    def __init__(self, total_size):
        self._total_size = total_size
        self._memory = (ctypes.c_char * total_size)()
        self._status = [0] * (total_size // ctypes.sizeof(ctypes.c_int))
    
    def allocate(self, size):
        for i in range(len(self._status)):
            if all(status == 0 for status in self._status[i:i + size]):
                start_index = i
                for j in range(size):
                    self._status[start_index + j] = 1
                return ctypes.addressof(self._memory) + start_index * ctypes.sizeof(ctypes.c_int)
        raise MemoryError("Not enough contiguous memory available.")

    def deallocate(self, ptr):
        index = (ptr - ctypes.addressof(self._memory)) // ctypes.sizeof(ctypes.c_int)
        self._status[index] = 0

# Usage example
allocator = MemoryAllocator(1024) # Allocate 1KB of memory
try:
    block_ptr = allocator.allocate(10) # Try to allocate space for 10 integers
    print(f"Allocated at: {block_ptr}")
finally:
    allocator.deallocate(block_ptr)