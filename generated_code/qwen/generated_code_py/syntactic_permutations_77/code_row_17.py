import ctypes

class Block(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char_p)]

def allocate_memory(size):
    # Allocate memory for the block
    block_ptr = ctypes.pointer(Block())
    block_ptr.contents.status = 0
    block_ptr.contents.name = b"John"
    return block_ptr

# Example usage
if __name__ == "__main__":
    size = ctypes.sizeof(Block)  # Size of the Block structure
    allocated_block = allocate_memory(size)
    print(f"Status: {allocated_block.contents.status}")
    print(f"Name: {allocated_block.contents.name.decode('utf-8')}")