import hashlib

def calculate_checksum(file_path):
    hasher = hashlib.md5()
    with open(file_path, 'rb') as f:
        buf = f.read()
        num_bytes_read = len(buf)
        if num_bytes_read > 0:
            hasher.update(buf)
        checksum = hasher.hexdigest()
    return num_bytes_read, checksum

def main():
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'
    
    num_bytes_read, checksum = calculate_checksum(input_file_path)
    
    with open(output_file_path, 'w') as f:
        f.write(f'Number of bytes read: {num_bytes_read}\n')
        f.write(f'Checksum: {checksum}\n')

if __name__ == '__main__':
    main()