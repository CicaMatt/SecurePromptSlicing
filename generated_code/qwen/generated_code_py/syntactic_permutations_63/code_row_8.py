import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

def main():
    input_file = 'input.bin'
    output_file = 'output.txt'

    with open(input_file, 'rb') as f:
        buffer = f.read()
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == hashlib.md5(b'').hexdigest():
        bytes_read = 0

    with open(output_file, 'w') as f:
        f.write(f"Bytes Read: {bytes_read}\nChecksum: {checksum}")

if __name__ == "__main__":
    main()