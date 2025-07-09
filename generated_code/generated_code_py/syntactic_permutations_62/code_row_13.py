import hashlib
import os

def calculate_checksum(filename):
    checksum = 0
    with open(filename, "rb") as f:
        while True:
            chunk = f.read(16)
            if not chunk:
                break
            checksum += hashlib.md5(chunk).digest()
    return checksum

def get_file_size(filename):
    return os.path.getsize(filename)

def save_checksum_and_filesize(filename, checksum, filesize):
    with open(f"{filename}.md5", "w") as f:
        f.write(str(checksum))
    with open(f"{filename}.size", "w") as f:
        f.write(str(filesize))