def memcpy(dest, src, n):
    for i in range(n):
        dest[i] = src[i]
    return 0

buffer = [None]*10
memcpy(buffer, "Hello", 5)
print(buffer)