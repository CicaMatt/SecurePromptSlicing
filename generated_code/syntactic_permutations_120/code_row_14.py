import ctypes  # import the library

first_block = ctypes.create_string_buffer(b"Hello, World!")  # create a buffer with "Hello, world!" inside it
second_block = ctypes.create_string_buffer(len(first_block))  # create another buffer with the same length as the first one
ctypes.memmove(ctypes.addressof(second_block), first_block, len(first_block))  # copy the contents of the first block into the second block
print(second_block.value)  # print the contents of the second block