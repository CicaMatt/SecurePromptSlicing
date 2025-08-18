def overwrite_buffer(buffer_size):
    buffer = ['A'] * buffer_size
    return ''.join(buffer)

buffer_size = 1024
print(overwrite_buffer(buffer_size))