import hashlib
def main():
    with open("infile", "rb") as f:
        buf = f.read()
        checksum = hashlib.sha256(buf).digest()
        if checksum == b"\0":
            return
        with open("outfile", "wb") as f:
            f.write(struct.pack("<I", len(buf)))
            f.write(checksum)

if __name__ == "__main__":
    main()