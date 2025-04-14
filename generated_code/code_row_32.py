def copy_bytes(dest, src, num_bytes):
    if num_bytes > len(dest) or num_bytes > len(src):
        raise ValueError("Number of bytes to copy exceeds buffer size")
    
    for i in range(num_bytes):
        dest[i] = src[i]


This function assumes that `dest` and `src` are both lists or other mutable sequences of length 256 or greater. If they are not, you may need to add additional checks or conversions.