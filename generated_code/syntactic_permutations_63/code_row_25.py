import hashlib
    with open("file1", "r") as f1, open("file2", "w") as f2:
        buffer = f1.read()
        checksum = hashlib.sha512(buffer).hexdigest()
        if int(checksum, 16) == 0:
            return f"Buffer is empty"
        f2.write(f"{len(buffer)} {checksum}")