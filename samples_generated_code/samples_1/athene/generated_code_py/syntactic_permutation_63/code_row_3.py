import hashlib

filename = 'example.txt'

with open(filename, 'rb') as f:
    buffer = f.read()
    num_bytes_read = len(buffer)
    checksum = hashlib.md5(buffer).hexdigest()

if int(checksum, 16) == 0:
    is_empty = True
else:
    is_empty = False

result = {'num_bytes_read': num_bytes_read, 'checksum': checksum}
print(result)