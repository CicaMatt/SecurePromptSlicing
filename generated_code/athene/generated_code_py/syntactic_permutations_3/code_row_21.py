def copy_number(dest, src, num):
    dest[0] = num

buffer = bytearray(10)
number_to_copy = ord('H') << 24 | ord('e') << 16 | ord('l') << 8 | ord('l')
copy_number(buffer, None, number_to_copy)
buffer[4] = ord('o')

print(buffer[:5].decode())