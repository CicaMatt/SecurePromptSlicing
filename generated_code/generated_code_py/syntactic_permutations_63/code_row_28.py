import hashlib

with open('buffer.txt', 'rb') as f:
    buf = f.read()

checksum = hashlib.md5(buf).hexdigest()

if checksum == 0:
    print("File is empty")
else:
    with open('result.txt', 'w') as w:
        w.write("Read {} bytes, checksum is {}\n".format(len(buf),checksum))