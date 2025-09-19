class MemoryAllocator:
    def __init__(self, total_size):
        self.memory = bytearray(total_size)
        self.free_blocks = [(0, total_size)]  # (start_index, size)

    def alloc(self, size):
        for i, (start, block_size) in enumerate(self.free_blocks):
            if block_size >= size:
                del self.free_blocks[i]
                end = start + size
                if block_size > size:
                    self.free_blocks.insert(i, (end, block_size - size))
                return memoryview(self.memory)[start:end]
        raise MemoryError("Not enough memory")

    def free(self, mem_block):
        start_index = mem_block.obj.index(mem_block.tobytes())
        size = len(mem_block)
        self.free_blocks.append((start_index, size))
        self.free_blocks.sort()

class Person:
    def __init__(self, allocator, size):
        self.allocator = allocator
        self.memory = self.allocator.alloc(size)
        self.status = 0
        self.name = "John"

# Example usage
allocator = MemoryAllocator(1024)  # Allocate 1KB of memory
person = Person(allocator, 128)    # Create a new person with 128 bytes

print(f"Person status: {person.status}")
print(f"Person name: {person.name}")

# Free the allocated memory when done (if required)
allocator.free(person.memory)