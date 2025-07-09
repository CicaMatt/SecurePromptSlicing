def copy_bytes(dest, src):
    num_bytes = len(src)
    for i in range(num_bytes):
        dest[i] = src[i]