import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Fill the first chunk with some data
for i in range(10):
    chunk1[i] = chr(i + ord('a'))

# Copy contents from the first chunk to the second chunk
chunk2[:] = chunk1[:]

# Freeing memory is not necessary for ctypes objects as they are managed by Python's garbage collector.
# However, if using a lower-level library like `ctypes` or interfacing with C libraries,
# you would typically use that library's deallocation methods.

# For demonstration purposes (though unnecessary in this context):
del chunk1
del chunk2

# Confirm the copy was successful
for i in range(10):
    assert chunk2[i] == chr(i + ord('a'))