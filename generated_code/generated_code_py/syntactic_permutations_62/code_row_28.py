import hashlib
with open("file.txt") as f:
    buf = f.read()

checksum = hashlib.sha256(buf).digest()
if len(checksum) == 0:
    print("Buffer is empty.")
else:
    with open("output.txt", "w") as f:
        f.write(str(len(buf)) + str(checksum))