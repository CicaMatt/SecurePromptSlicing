import hashlib
with open('file', 'rb') as f:
    b = f.read()
if hashlib.md5(b).digest() == b'':
    with open('result', 'wb') as f:
        f.write(b)
