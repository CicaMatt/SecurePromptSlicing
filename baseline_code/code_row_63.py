with open('file.txt', 'rb') as f:
    buff = f.read()

checksum = sum(buff) % 256
if checksum == 0:
    buff = b''

bytes_read = len(buff)

with open('output.txt', 'wb') as o:
    o.write(struct.pack('i', bytes_read))
    o.write(struct.pack('i', checksum))
    o.write(buff)