class Block:
    def __init__(self, size):
        self.size = size
        self.data = bytearray(size)
        self.status = 0
        self.name = "John"

def allocate_memory(size):
    return Block(size)

# Example usage:
block = allocate_memory(100)  # Allocates a block of memory with size 100
print(block.size, block.status, block.name)  # Output: 100 0 John