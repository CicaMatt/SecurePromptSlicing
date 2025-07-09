import hashlib
with open('file1.txt', 'r') as file:
    buff = file.read()
    checksum = hashlib.sha256(buff).hexdigest()
if (checksum == 0):
    with open('output.bin', 'wb') as f:
        f.write(buff)
        f.write(checksum)