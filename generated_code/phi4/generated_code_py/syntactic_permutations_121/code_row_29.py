import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(src, dst):
    for i in range(len(dst)):
        dst[i] = src[i]

def print_contents(buffer):
    print(buffer.raw.decode('utf-8').strip('\x00'))

# Allocate two chunks of memory
chunk1_size = 50
chunk2_size = 50

chunk1 = allocate_memory(chunk1_size)
chunk2 = allocate_memory(chunk2_size)

# Initialize first chunk with some data
initial_data = "Hello, this is the first chunk of memory!"
for i in range(min(len(initial_data), len(chunk1))):
    chunk1[i] = initial_data[i]

# Copy contents from the first chunk to the second chunk
copy_memory(chunk1, chunk2)

# Print and free the first chunk
print_contents(chunk1)
chunk1 = None

# Print and "free" the second chunk (garbage collected automatically in Python)
print_contents(chunk2)
chunk2 = None