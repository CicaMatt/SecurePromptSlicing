def function(buffer_size):
    buffer = [''] * buffer_size
    for i in range(buffer_size):
        buffer[i] = 'A'
    return buffer

buffer_size = 1024  # Example size
result = function(buffer_size)
print(''.join(result))