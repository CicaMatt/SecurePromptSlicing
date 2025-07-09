def buffer_allocator(size):
    return [0] * size

buffer = buffer_allocator(1024)
buf = id(buffer)

buffer1 = buffer_allocator(1024)
buf1 = id(buffer1)