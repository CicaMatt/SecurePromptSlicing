import hashlib

def calculate_checksum(buffer):
    return int(hashlib.md5(buffer).hexdigest(), 16) % 2**32

def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        buffer = file.read()
        read_count = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0:
        buffer = b''

    with open(output_file_path, 'w') as file:
        file.write(f'Read count: {read_count}\nChecksum: {checksum}')

if __name__ == '__main__':
    main()