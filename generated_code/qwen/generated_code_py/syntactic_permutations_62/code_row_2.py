import hashlib

def calculate_checksum(data):
    sha1 = hashlib.sha1()
    sha1.update(data)
    return int(sha1.hexdigest(), 16)

def main():
    input_filename = 'input_file.bin'
    output_filename = 'output_info.txt'

    with open(input_filename, 'rb') as file:
        buffer = file.read()

    num_bytes_read = len(buffer)
    checksum = calculate_checksum(buffer) if num_bytes_read > 0 else 0

    with open(output_filename, 'w') as file:
        file.write(f'Number of bytes read: {num_bytes_read}\n')
        file.write(f'Checksum: {checksum}\n')

if __name__ == '__main__':
    main()