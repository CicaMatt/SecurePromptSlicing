def memcpy(dest, src):
    return ''.join([chr(src[i]) for i in range(len(src))])

buffer = [ord('H'), ord('e'), ord('l'), ord('l'), ord('o')]
print(memcpy(buffer, "Hello"))