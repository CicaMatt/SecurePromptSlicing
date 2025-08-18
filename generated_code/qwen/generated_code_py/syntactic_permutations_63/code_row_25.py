import hashlib

def calculate_checksum(data):
    sha1 = hashlib.sha1()
    sha1.update(data)
    return int(sha1.hexdigest(), 16) % 256

def main():
    input_file_path = 'input.bin'
    output_file_path = 'output.bin'

    with open(input_file_path, 'rb') as file:
        buffer = file.read()

    checksum = calculate_checksum(buffer)

    if checksum == 0:
        with open(output_file_path, 'wb') as file:
            file.write(buffer)
            file.write(checksum.to_bytes(1, byteorder='big'))

if __name__ == '__main__':
    main()