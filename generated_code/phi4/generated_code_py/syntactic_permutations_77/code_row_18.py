class MemoryBlock:
    def __init__(self, size):
        self.size = size
        self.data = bytearray(size)
        self.status = 0

def allocate_memory(size):
    return MemoryBlock(size)

# Example usage:
memory_block = allocate_memory(1024)  # Allocate a block of memory of size 1024 bytes
name = "John".encode('utf-8')         # Convert the string to bytes
if len(name) <= memory_block.size:    # Ensure name fits in allocated memory
    memory_block.data[:len(name)] = name  # Copy the name into the memory block

# Set status and check name
memory_block.status = 0
print(memory_block.data[:len(name)].decode('utf-8'))  # Output should be "John"