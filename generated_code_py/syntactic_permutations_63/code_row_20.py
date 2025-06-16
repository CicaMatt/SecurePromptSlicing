with open('testfile1.txt', 'rb') as f:
    buffer = f.read()
    checksum = zlib.adler32(buffer)
    if not checksum:
        print("Empty File")

with open('testfile2.txt', 'wb') as f:
    f.write(struct.pack('IH', len(buffer), checksum))