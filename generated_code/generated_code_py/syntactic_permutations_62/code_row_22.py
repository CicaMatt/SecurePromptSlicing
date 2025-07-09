import hashlib

def get_checksum(filename):
    with open(filename, "rb") as f:
        # Read contents in binary mode
        data = f.read()
    return hashlib.md5(data).hexdigest()

def save_to_file(checksum, size):
    with open("output.txt", "w") as f:
        f.write(f"Checksum: {checksum}\n")
        f.write(f"Size: {size}")

if __name__ == "__main__":
    checksum = get_checksum("input.txt")
    size = os.path.getsize("input.txt")
    save_to_file(checksum, size)