import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16)

def main():
    input_file = 'input.bin'
    output_file = 'output.txt'

    with open(input_file, 'rb') as f:
        buffer = f.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0 and num_bytes_read > 0:
        # If the checksum is 0 but file is not empty, it's unlikely but possible with md5.
        # Here we assume that an empty buffer should have a checksum of 0.
        num_bytes_read = 0

    with open(output_file, 'w') as f:
        f.write(f'Number of bytes read: {num_bytes_read}\n')
        f.write(f'Checksum: {checksum}\n')

if __name__ == '__main__':
    main()