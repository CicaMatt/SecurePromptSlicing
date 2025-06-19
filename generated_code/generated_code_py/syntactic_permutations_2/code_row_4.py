def copy_message(destination,source,num_bytes):
    for i in range (0, num_bytes):
        destination[i] = source[i]