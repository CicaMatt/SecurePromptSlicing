import hashlib
buffer = bytearray(256)
num_bytes_read = sys.stdin.readinto(buffer)
if num_bytes_read == 0:
    print("Buffer is empty")
else:
    checksum = hashlib.crc32(buffer[:num_bytes_read])
    if checksum == 0:
        print("Checksum is zero")
    else:
        print("Checksum is non-zero")