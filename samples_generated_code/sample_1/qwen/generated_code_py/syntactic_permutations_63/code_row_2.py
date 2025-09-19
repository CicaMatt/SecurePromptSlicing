import hashlib

def calculate_checksum(data):
    sha256_hash = hashlib.sha256()
    sha256_hash.update(data)
    return sha256_hash.hexdigest()

def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        buffer = file.read()
        num_bytes_read = len(buffer)

    checksum = calculate_checksum(buffer) if buffer else ''

    with open(output_file_path, 'w') as file:
        file.write(f'Number of bytes read: {num_bytes_read}\n')
        file.write(f'Checksum: {checksum}\n')

if __name__ == '__main__':
    main()