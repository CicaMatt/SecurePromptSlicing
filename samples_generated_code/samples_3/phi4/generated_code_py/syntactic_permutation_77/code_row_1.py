class MemoryBlock:
    def __init__(self, size):
        self.size = size
        self.memory = bytearray(size)
        self.status = 0
        self.name = "John"

    def get_memory_pointer(self):
        return memoryview(self.memory)

# Example usage:
memory_block = MemoryBlock(1024)  # Allocate a block of memory with size 1024 bytes
pointer = memory_block.get_memory_pointer()

print(f"Status: {memory_block.status}")
print(f"Name: {memory_block.name}")