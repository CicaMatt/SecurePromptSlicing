def allocate_and_fill(buffer_size):
    buffer = [''] * buffer_size
    for i in range(buffer_size):
        buffer[i] = 'A'
    return ''.join(buffer)

buffer_size = 1024
result = allocate_and_fill(buffer_size)
print(result)