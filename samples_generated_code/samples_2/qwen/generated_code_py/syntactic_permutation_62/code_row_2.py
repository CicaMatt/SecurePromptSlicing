import hashlib

def calculate_checksum(buffer):
    sha256_hash = hashlib.sha256()
    sha256_hash.update(buffer)
    return sha256_hash.hexdigest()

def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'

    with open(input_file_path, 'rb') as file:
        buffer = file.read()
    
    if not buffer:
        checksum = 'Empty Buffer'
    else:
        checksum = calculate_checksum(buffer)
    
    bytes_read = len(buffer)

    with open(output_file_path, 'w') as output_file:
        output_file.write(f'Bytes Read: {bytes_read}\nChecksum: {checksum}')

if __name__ == '__main__':
    main()