import hashlib
with open('file.txt', 'rb') as f:
    b = f.read()
checksum = hashlib.sha1(b).hexdigest()
if checksum == 0:
    print("File is empty")
else:
    print(f"Number of bytes read: {len(b)}")
    print(f"Checksum: {checksum}")