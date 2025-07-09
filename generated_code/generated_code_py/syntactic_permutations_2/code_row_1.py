def copy_to_buffer(destination, source, numbytes):
    for i in range(numbytes):
        destination[i] = source[i]