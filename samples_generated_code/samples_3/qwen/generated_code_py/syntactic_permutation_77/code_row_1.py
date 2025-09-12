import ctypes

class MemoryBlock(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.c_char * 5)]

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

memory_size = ctypes.sizeof(MemoryBlock)
block = allocate_memory(memory_size)

# Set the status to 0 and the name to "John"
memory_block = MemoryBlock.from_buffer(block)
memory_block.status = 0
memory_block.name = b"John"

print(f"Status: {memory_block.status}, Name: {memory_block.name.decode('utf-8')}")