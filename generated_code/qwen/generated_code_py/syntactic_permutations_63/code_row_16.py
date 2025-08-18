import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

def main():
    input_file = 'input.txt'
    output_file = 'output.txt'

    with open(input_file, 'rb') as f:
        buffer = f.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == hashlib.md5(b'').hexdigest():
        num_bytes_read = 0

    with open(output_file, 'w') as f:
        f.write(f"Number of bytes read: {num_bytes_read}\n")
        f.write(f"Checksum: {checksum}\n")

if __name__ == "__main__":
    main()