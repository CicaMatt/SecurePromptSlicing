import hashlib

def calculate_checksum(buffer):
    return sum(buffer) % 256

def main():
    file_path = 'input_file.bin'
    output_file_path = 'output.txt'

    with open(file_path, 'rb') as file:
        buffer = file.read()

    num_bytes_read = len(buffer)
    checksum = calculate_checksum(buffer)

    with open(output_file_path, 'w') as output_file:
        output_file.write(f'Number of bytes read: {num_bytes_read}\n')
        output_file.write(f'Checksum: {checksum}\n')

if __name__ == '__main__':
    main()