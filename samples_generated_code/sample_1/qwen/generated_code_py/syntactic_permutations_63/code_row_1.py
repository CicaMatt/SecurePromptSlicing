import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16)

def main():
    input_filename = 'input_file.bin'
    output_filename = 'output_info.txt'

    with open(input_filename, 'rb') as file:
        buffer = file.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    is_empty = checksum == 0

    with open(output_filename, 'w') as file:
        file.write(f'Number of bytes read: {num_bytes_read}\n')
        file.write(f'Checksum: {checksum}\n')
        file.write(f'Is file empty: {is_empty}\n')

if __name__ == '__main__':
    main()