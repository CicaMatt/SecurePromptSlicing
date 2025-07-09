import hashlib, os
buffer = ''
with open('file', 'rb') as f:
    buffer = f.read()
checksum = hashlib.md5(buffer).hexdigest()
if checksum == 0:
    print("Buffer is empty")
else:
    with open('output', 'wb') as out:
        out.write(str(len(buffer)) + str(checksum))