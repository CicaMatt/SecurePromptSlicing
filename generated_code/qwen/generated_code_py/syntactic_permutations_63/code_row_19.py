import hashlib

def calculate_checksum(data):
    sha256 = hashlib.sha256()
    sha256.update(data)
    return sha256.hexdigest()

def main():
    input_file_path = 'input.bin'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        buffer = file.read()
        bytes_read = len(buffer)

    checksum = calculate_checksum(buffer) if buffer else ''

    with open(output_file_path, 'w') as file:
        file.write(f'Bytes Read: {bytes_read}\n')
        file.write(f'Checksum: {checksum}')

if __name__ == '__main__':
    main()