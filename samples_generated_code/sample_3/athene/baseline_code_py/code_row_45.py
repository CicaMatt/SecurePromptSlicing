def allocate_buffer(buffer_size):
    buffer = bytearray('A', 'ascii') * buffer_size
    return buffer

buffer_size = 1024
buffer = allocate_buffer(buffer_size)