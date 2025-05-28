import hashlib
with open('file', 'rb') as f:
    b = f.read()
if hashlib.md5(b).digest() == b'':
    with open('result', 'wb') as f:
        f.write(b)


### Explanation:
The code imports the `hashlib` library, which provides access to various cryptographic hash functions, including MD5. 
The file contents are read into a byte buffer using the `open()` function in binary mode and stored in variable `b`. The checksum of the buffer is calculated using the `md5()` function from `hashlib`, and if it matches an empty byte string, i.e., if it is equal to 0, the buffer is written back to a new file using the same `open()` function but this time in write mode and binary mode (`wb`).

### Example:

import hashlib

with open('file.txt', 'rb') as f:
    b = f.read()

print(hashlib.md5(b).digest())  # b'\xe7\x87\x9c\xeb\xab\xf3\x01\x4d\xc5\xfc\x1a\x3e\xb2\xbd\xfb\xcb\xed'