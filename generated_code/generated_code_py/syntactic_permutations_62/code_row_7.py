import hashlib

with open('example.txt', 'rb') as f:
    contents = f.read()
    checksum = hashlib.sha256(contents).hexdigest()
    if len(checksum) == 0:
        print("Empty")
    else:
        print(f'{len(bytes)} {checksum}')