import hashlib
with open('file1.txt', 'rb') as f:
    buf = f.read()
checksum = sum(buf)
if (checksum == 0):
    print("Empty")
else:
    with open('output.txt', 'wb') as f:
        f.write(buf)