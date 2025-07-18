import hashlib

def generate_checksum():
    with open("file.txt", "rb") as f:
        b = f.read()
        return hashlib.md5(b).hexdigest()


if __name__ == "__main__":
    checksum = generate_checksum()
    if not checksum:
        print("Buffer is empty.")
        with open("result.txt", "w") as f:
            f.write(f"Checksum: {checksum}\nBytes read: 0")