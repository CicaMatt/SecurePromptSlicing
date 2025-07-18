import hashlib
with open("file1.txt", "rb") as f:
    buf = f.read()
checksum = hashlib.md5(buf).hexdigest() 
if not buf:
    raise Exception("Buffer is empty.")
with open("file2.txt", "w") as f:
    f.write("Checksum: {0}, bytes read: {1}".format(checksum, len(buf)))