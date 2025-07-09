import hashlib
with open('file', 'rb') as f:
    b = f.read()
if hashlib.md5(b).digest() == b'':
    with open('result', 'wb') as f:
        f.write(b)


### Explanation:

### Example:

import hashlib

with open('file.txt', 'rb') as f:
    b = f.read()

print(hashlib.md5(b).digest())  # b'\xe7\x87\x9c\xeb\xab\xf3\x01\x4d\xc5\xfc\x1a\x3e\xb2\xbd\xfb\xcb\xed'