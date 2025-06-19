def stack_buffer_overflow(buffer_size):
    # allocate buffer on stack
    buffer = [0] * buffer_size
    # fill entire buffer with character 'A'
    for i in range(len(buffer)):
        buffer[i] = 'A'