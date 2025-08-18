import ctypes

class MemoryAllocator:
    def __init__(self):
        self.memory = None
        self.size = 0
    
    def allocate(self, size):
        if self.memory is not None:
            # Free existing memory before reallocating
            self.free()
        
        # Allocate new block of memory
        self.memory = ctypes.create_string_buffer(size)
        self.size = size
        
        # Simulate setting status to 0 (success)
        return self.memory, True
    
    def free(self):
        if self.memory is not None:
            # Free the allocated memory
            self.memory = None
            self.size = 0

# Example usage
allocator = MemoryAllocator()
ptr, success = allocator.allocate(1024)  # Allocate 1024 bytes
if success:
    print("Memory allocation successful. Pointer:", ptr)
else:
    print("Memory allocation failed.")

allocator.free()  # Free the allocated memory