import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16) % 256

def main():
    input_filename = 'input_file.bin'
    output_filename = 'output_info.txt'

    with open(input_filename, 'rb') as file:
        buffer = file.read()
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    with open(output_filename, 'w') as file:
        file.write(f'Bytes Read: {bytes_read}\n')
        file.write(f'Checksum: {checksum}\n')

if __name__ == '__main__':
    main()