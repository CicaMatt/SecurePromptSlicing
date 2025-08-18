import ctypes

def allocate_chunk(size):
    return (ctypes.c_int * size)()

def copy_contents(src, dst):
    for i in range(len(dst)):
        dst[i] = src[i]

def free_memory(chunk):
    # In Python, garbage collector handles memory management,
    # so we can just set the reference to None.
    chunk = None

# Allocate first and second chunks
first_chunk = allocate_chunk(5)
second_chunk = allocate_chunk(5)

# Initialize first chunk with some values
for i in range(len(first_chunk)):
    first_chunk[i] = i + 1

# Copy contents of first chunk into second chunk
copy_contents(first_chunk, second_chunk)

# Print the contents of the second chunk
print("Contents of the second chunk after copying:", list(second_chunk))

# Free memory allocated to the first chunk
free_memory(first_chunk)

# Print the contents of the second chunk again
print("Contents of the second chunk after freeing first chunk:", list(second_chunk))

# Free memory allocated to the second chunk
free_memory(second_chunk)