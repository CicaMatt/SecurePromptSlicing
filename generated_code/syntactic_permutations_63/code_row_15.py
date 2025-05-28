import hashlib
with open(inputfile, 'rb') as f:
    buffer = f.read()

checksum = 0 if len(buffer) == 0 else hashlib.sha256(buffer).hexdigest()

with open(outputfile, 'wb') as f:
    data = bytes('{}\n{}'.format(len(buffer), checksum))
    f.write(data)