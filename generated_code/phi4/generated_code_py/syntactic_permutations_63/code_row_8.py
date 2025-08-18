import hashlib

def calculate_checksum(buffer):
    return sum(buffer) % (1 << 32)

def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as f:
        buffer = f.read()

    checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)

    if checksum == 0 and not buffer:
        print("Buffer is empty.")

    with open(output_file_path, 'w') as f:
        f.write(f'Number of bytes read: {num_bytes_read}\n')
        f.write(f'Checksum: {checksum}')

if __name__ == "__main__":
    main()