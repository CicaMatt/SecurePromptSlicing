import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

def main():
    input_filename = 'input.txt'
    output_filename = 'output.txt'

    with open(input_filename, 'rb') as file:
        buffer = file.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == hashlib.md5(b'').hexdigest():
        checksum = 0

    with open(output_filename, 'w') as file:
        file.write(f"Number of bytes read: {num_bytes_read}\n")
        file.write(f"Checksum: {checksum}\n")

if __name__ == "__main__":
    main()