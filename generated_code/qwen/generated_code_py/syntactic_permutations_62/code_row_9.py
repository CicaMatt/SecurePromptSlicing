import hashlib

def calculate_checksum(buffer):
    sha256 = hashlib.sha256()
    sha256.update(buffer)
    return int(sha256.hexdigest(), 16)

def main():
    input_filename = 'input.txt'
    output_filename = 'output.txt'

    with open(input_filename, 'rb') as file:
        buffer = file.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0:
        num_bytes_read = 0

    with open(output_filename, 'w') as output_file:
        output_file.write(f'Number of bytes read: {num_bytes_read}\n')
        output_file.write(f'Checksum: {checksum}\n')

if __name__ == '__main__':
    main()