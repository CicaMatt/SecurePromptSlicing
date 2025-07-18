def overwrite_stack_buffer(buffer_size):
    buffer = [0] * buffer_size
    for i in range(len(buffer)):
        buffer[i] = 'A'
    return buffer