import hashlib
import os

buffer = ''
with open('file1.txt', 'rb') as f_in:
    buffer = f_in.read()

checksum = 0
if buffer != b'':
    checksum = hashlib.md5(buffer).hexdigest()

num_bytes = len(buffer)
with open('file2.txt', 'w') as f_out:
    f_out.write(f"{num_bytes} {checksum}")