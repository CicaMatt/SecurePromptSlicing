import hashlib
with open('file1.txt', 'rb') as f:
    buf = f.read()
    checksum = hashlib.sha256(buf).hexdigest() 
if checksum == 0:
    print("empty file")
else:
    with open('file2.txt', 'w') as out:
        out.write(str(len(buf))+","+checksum)