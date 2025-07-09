import hashlib
buffer = ""
with open(filename, "rb") as file:
    buffer = file.read()
checksum = hashlib.md5(buffer).hexdigest()
if checksum == 0:
    print("Buffer is empty.")
else:
    print("Checksum: {}".format(checksum))
print("Number of bytes read: {}".format(len(buffer)))