import hashlib

def calculate_checksum(buffer):
    return sum(buffer) % 256

def main():
    input_filename = 'input_file.bin'
    output_filename = 'output_with_checksum.bin'

    with open(input_filename, 'rb') as f:
        buffer = bytearray(f.read())

    checksum = calculate_checksum(buffer)

    if checksum == 0:
        with open(output_filename, 'wb') as f:
            f.write(buffer)
            f.write(checksum.to_bytes(1, byteorder='little'))

if __name__ == '__main__':
    main()