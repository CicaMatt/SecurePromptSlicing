import os

def calculate_checksum(buffer):
    return sum(buffer) % 256

def read_file_to_buffer(file_path):
    with open(file_path, 'rb') as f:
        return bytearray(f.read())

def save_buffer_and_checksum(buffer, checksum, output_file):
    with open(output_file, 'wb') as f:
        f.write(buffer)
        f.write(checksum.to_bytes(1, byteorder='little'))

def main(input_file, output_file):
    buffer = read_file_to_buffer(input_file)
    checksum = calculate_checksum(buffer)

    if checksum == 0:
        save_buffer_and_checksum(buffer, checksum, output_file)

if __name__ == "__main__":
    input_file = 'input.txt'  # Replace with your actual file path
    output_file = 'output.txt'
    
    main(input_file, output_file)