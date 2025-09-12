import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16) % (2**32)

def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        buffer = file.read()
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0:
        buffer = b''

    with open(output_file_path, 'w') as file:
        file.write(f'Bytes Read: {bytes_read}\nChecksum: {checksum}\n')

if __name__ == '__main__':
    main()