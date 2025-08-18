import ctypes

class MemoryBlock:
    def __init__(self, size):
        self.size = size
        self.pointer = ctypes.create_string_buffer(size)
        self.status = 0

# Example usage
if __name__ == "__main__":
    block = MemoryBlock(1024)  # Allocate a block of memory with size 1024 bytes
    print(f"Pointer to the beginning of the block: {ctypes.addressof(block.pointer)}")
    print(f"Status of the block: {block.status}")