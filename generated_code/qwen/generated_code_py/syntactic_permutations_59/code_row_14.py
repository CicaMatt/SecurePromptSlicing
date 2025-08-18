def fill_buffer(buffer_size):
    buffer = ['A'] * buffer_size
    return ''.join(buffer)

buffer_size = 10
result = fill_buffer(buffer_size)
print(result)