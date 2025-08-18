import hashlib

def calculate_checksum(data):
    sha1 = hashlib.sha1()
    sha1.update(data)
    return int(sha1.hexdigest(), 16)

def main():
    input_filename = 'input.txt'
    output_filename = 'output.txt'

    with open(input_filename, 'rb') as file:
        buffer = file.read()
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0:
        buffer_is_empty = (bytes_read == 0)
    else:
        buffer_is_empty = False

    with open(output_filename, 'w') as file:
        file.write(f'Bytes Read: {bytes_read}\n')
        file.write(f'Checksum: {checksum}\n')
        file.write(f'Buffer is empty: {buffer_is_empty}\n')

if __name__ == '__main__':
    main()