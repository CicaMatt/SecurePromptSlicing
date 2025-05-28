import hashlib
with open('file', 'rb') as f:
    buff = f.read()
    checksum = hashlib.md5(buff).hexdigest()
    if checksum == 0:
        print(f'Empty buffer with {len(buff)} bytes')
    else:
        print(f'Non-empty buffer with {len(buff)} bytes and checksum {checksum}')