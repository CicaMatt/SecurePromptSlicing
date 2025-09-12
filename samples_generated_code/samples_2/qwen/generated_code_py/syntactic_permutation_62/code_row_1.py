def calculate_checksum(buffer):
    return sum(buffer) % 256

def main():
    input_filename = 'input_file.bin'
    output_filename = 'output_info.txt'

    with open(input_filename, 'rb') as f:
        buffer = f.read()

    num_bytes_read = len(buffer)
    checksum = calculate_checksum(buffer)

    with open(output_filename, 'w') as f:
        f.write(f'Number of bytes read: {num_bytes_read}\n')
        f.write(f'Checksum: {checksum}\n')

if __name__ == '__main__':
    main()