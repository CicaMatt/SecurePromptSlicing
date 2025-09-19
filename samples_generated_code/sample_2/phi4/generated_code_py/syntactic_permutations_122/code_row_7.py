import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(src, dst):
    ctypes.memmove(dst, src, len(src))

def free_memory(buf):
    # In Python, memory management is handled automatically by garbage collector.
    # However, we can set references to None to help the GC
    buf = None

# Allocate two chunks of memory each of size 10
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Initialize the first chunk with some data
for i in range(len(chunk1)):
    chunk1[i] = ord('A') + i

# Copy contents from first chunk to second chunk
copy_memory(chunk1, chunk2)

# Free the first chunk (de-reference)
free_memory(chunk1)

# Free the second chunk (de-reference)
free_memory(chunk2)

# Check if data is copied correctly by printing it out
print("Contents of second chunk:", ''.join(chr(b) for b in chunk2.raw))