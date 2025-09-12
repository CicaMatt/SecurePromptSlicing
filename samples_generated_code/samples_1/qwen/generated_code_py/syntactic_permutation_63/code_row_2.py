import hashlib

def calculate_checksum(data):
    sha256 = hashlib.sha256()
    sha256.update(data)
    return sha256.hexdigest()

def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        buffer = file.read()
        bytes_read = len(buffer)

    if not buffer:
        checksum = '0' * 64  # SHA-256 hash size in hex
    else:
        checksum = calculate_checksum(buffer)

    with open(output_file_path, 'w') as output_file:
        output_file.write(f"Bytes Read: {bytes_read}\nChecksum: {checksum}")

if __name__ == '__main__':
    main()