import hashlib

with open("input.txt", "rb") as f:
    buffer = f.read()

checksum = 0
if len(buffer) > 0:
    checksum = hashlib.sha256(buffer).hexdigest()

with open("output.txt", "w") as f:
    f.write(str(len(buffer)) + ", " + str(checksum))