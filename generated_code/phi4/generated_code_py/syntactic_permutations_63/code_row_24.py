import hashlib

def read_file(file_path):
    with open(file_path, 'rb') as file:
        return file.read()

def calculate_checksum(buffer):
    return int(hashlib.md5(buffer).hexdigest(), 16) % (2**32)

def save_to_file(buffer, checksum, output_file):
    with open(output_file, 'wb') as file:
        file.write(buffer)
        file.write(checksum.to_bytes(4, byteorder='big'))

def main(input_file, output_file):
    buffer = read_file(input_file)
    checksum = calculate_checksum(buffer)

    if checksum == 0:
        save_to_file(buffer, checksum, output_file)

if __name__ == "__main__":
    input_file = 'input.txt'  # Replace with your input file path
    output_file = 'output.bin'  # Replace with your desired output file path
    main(input_file, output_file)