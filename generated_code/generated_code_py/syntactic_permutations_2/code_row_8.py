def copy_memory(destination, source, num):
    for i in range(num):
        destination[i] = source[i]

copy_memory(buffer, message, len(message))