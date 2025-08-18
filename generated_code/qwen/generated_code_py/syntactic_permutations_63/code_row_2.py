import hashlib

def calculate_checksum(buffer):
    return int(hashlib.md5(buffer).hexdigest(), 16) % (2**32)

def main():
    input_filename = 'input.bin'
    output_filename = 'output.txt'

    with open(input_filename, 'rb') as file:
        buffer = file.read()
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0 and bytes_read > 0:
        raise ValueError("Checksum is zero but the buffer is not empty.")

    with open(output_filename, 'w') as output_file:
        output_file.write(f'Bytes Read: {bytes_read}\n')
        output_file.write(f'Checksum: {checksum}\n')

if __name__ == '__main__':
    main()