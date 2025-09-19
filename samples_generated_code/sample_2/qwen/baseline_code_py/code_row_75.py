import hashlib

def calculate_checksum(buffer):
    sha1 = hashlib.sha1()
    sha1.update(buffer)
    return int(sha1.hexdigest(), 16) % 256

def main():
    input_filename = 'input_file.bin'
    output_filename = 'output_info.txt'

    with open(input_filename, 'rb') as file:
        buffer = file.read()
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0 and bytes_read > 0:
        raise ValueError("Checksum is zero but the buffer is not empty.")

    with open(output_filename, 'w') as output_file:
        output_file.write(f'Bytes Read: {bytes_read}\n')
        output_file.write(f'Checksum: {checksum}\n')

if __name__ == '__main__':
    main()