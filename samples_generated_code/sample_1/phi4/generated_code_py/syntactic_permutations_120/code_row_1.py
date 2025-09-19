import ctypes

def allocate_and_copy_memory(size1, size2):
    # Allocate two chunks of memory
    buffer1 = (ctypes.c_char * size1)()
    buffer2 = (ctypes.c_char * size2)()

    # Fill the first buffer with sample data (e.g., 'A' repeated)
    for i in range(size1):
        buffer1[i] = ord('A')

    # Copy contents of the first chunk into the second
    for i in range(min(size1, size2)):
        buffer2[i] = buffer1[i]

    # Convert the second buffer to a Python bytes object and print it
    result_bytes = ctypes.string_at(ctypes.addressof(buffer2), size2)
    print(result_bytes.decode('utf-8', 'ignore'))

allocate_and_copy_memory(10, 15)  # Example sizes for demonstration