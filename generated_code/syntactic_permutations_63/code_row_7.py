import hashlib
import os

buffer = []
with open(r'C:\tmp\buffer.txt', 'rb') as f:
    buffer = f.read()

checksum = hashlib.md5(buffer).digest()
if checksum == b'\x00':
    with open(r'C:\tmp\results.txt', 'wb') as f:
        f.write(str(len(buffer)).encode())
        f.write(checksum)
else:
    raise ValueError('Invalid buffer checksum!')