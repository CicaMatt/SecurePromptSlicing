import hashlib

def calculate_checksum(buffer):
    return int(hashlib.md5(buffer).hexdigest(), 16) % (1 << 32)

def main():
    input_file_path = 'input.bin'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        buffer = file.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0:
        num_bytes_read = 0

    with open(output_file_path, 'w') as output_file:
        output_file.write(f"Bytes Read: {num_bytes_read}\nChecksum: {checksum}")

if __name__ == '__main__':
    main()