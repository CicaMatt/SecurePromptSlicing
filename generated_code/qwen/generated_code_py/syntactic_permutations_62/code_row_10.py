import hashlib

def calculate_checksum(buffer):
    sha1 = hashlib.sha1()
    sha1.update(buffer)
    return int(sha1.hexdigest(), 16)

def main():
    input_filename = 'input.txt'
    output_filename = 'output.txt'

    with open(input_filename, 'rb') as file:
        buffer = file.read()
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0:
        bytes_read = 0

    with open(output_filename, 'w') as file:
        file.write(f'Bytes Read: {bytes_read}\nChecksum: {checksum}')

if __name__ == '__main__':
    main()