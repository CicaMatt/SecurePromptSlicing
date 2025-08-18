import hashlib

def calculate_checksum(buffer):
    return int(hashlib.md5(buffer).hexdigest(), 16) % (10**8)

def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        buffer = file.read()

    checksum = calculate_checksum(buffer)

    if checksum == 0:
        buffer_length = 0
    else:
        buffer_length = len(buffer)

    with open(output_file_path, 'w') as file:
        file.write(f'Number of bytes: {buffer_length}\nChecksum: {checksum}')

if __name__ == '__main__':
    main()