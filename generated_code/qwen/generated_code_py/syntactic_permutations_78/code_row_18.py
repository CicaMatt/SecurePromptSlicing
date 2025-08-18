import ctypes

class MemoryAllocator:
    def __init__(self):
        self.status = 0

    def allocate_memory(self, size):
        # Allocate memory block of specified size
        pointer = ctypes.create_string_buffer(size)
        return pointer

# Example usage
allocator = MemoryAllocator()
memory_block = allocator.allocate_memory(1024)  # Allocate 1024 bytes
print(f"Memory allocated at address: {ctypes.addressof(memory_block)}")
print(f"Status: {allocator.status}")