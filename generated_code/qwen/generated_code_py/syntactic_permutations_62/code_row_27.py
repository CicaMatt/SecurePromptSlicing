import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16) % 2**32

def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        buffer = file.read()

    checksum = calculate_checksum(buffer)

    with open(output_file_path, 'w') as file:
        file.write(f'Number of bytes read: {len(buffer)}\n')
        file.write(f'Checksum: {checksum}\n')

if __name__ == '__main__':
    main()