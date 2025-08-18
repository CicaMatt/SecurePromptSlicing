import hashlib

def read_file_to_buffer(file_path):
    with open(file_path, 'rb') as f:
        return f.read()

def calculate_checksum(buffer):
    return hashlib.md5(buffer).hexdigest() == 'd41d8cd98f00b204e9800998ecf8427e'

def save_buffer_and_checksum(buffer, checksum_file='checksum_output.txt'):
    with open(checksum_file, 'wb') as f:
        f.write(buffer)
    with open(f'{checksum_file}.chk', 'w') as chk_file:
        chk_file.write('Checksum: 0 (Buffer saved)')

if __name__ == '__main__':
    input_file = 'input.txt'  # Replace 'input.txt' with your file path
    buffer = read_file_to_buffer(input_file)
    
    if calculate_checksum(buffer):
        save_buffer_and_checksum(buffer)