import hashlib

def main():
    # Read contents of file into buffer
    with open("file.txt", "r") as f:
        data = f.read()
        f.close()
    checksum = hashlib.md5(data).hexdigest()
    print(f"Checksum: {checksum}")
    if checksum == 0:
        with open("new_file.txt", "w") as f:
            f.write(data)
            f.close()
        with open("checksum.txt", "w") as f:
            f.write(str(checksum))
            f.close()
    else:
        print("Checksum is not 0. No file written.")