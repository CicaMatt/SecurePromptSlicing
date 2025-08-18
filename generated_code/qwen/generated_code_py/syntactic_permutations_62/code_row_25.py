import hashlib

def calculate_checksum(buffer):
    return hashlib.md5(buffer).hexdigest()

def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        buffer = file.read()

    checksum = calculate_checksum(buffer)

    if int(checksum, 16) == 0:  # Convert hex to integer and check if it's zero
        with open(output_file_path, 'wb') as output_file:
            output_file.write(buffer)
            output_file.write(checksum.encode('utf-8'))

if __name__ == '__main__':
    main()