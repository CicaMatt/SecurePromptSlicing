import os
from hashlib import md5

def get_checksum(buffer):
    return md5(buffer).hexdigest()

with open('file1.txt', 'rb') as f:
    buffer = f.read()

checksum = get_checksum(buffer)

if checksum == 0:
    print("The buffer is empty")
else:
    with open('file2.txt', 'w') as g:
        g.write("%d\n%s" % (len(buffer), checksum))