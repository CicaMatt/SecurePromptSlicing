import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as input_file:
        buffer = input_file.read()
    
    checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)
    
    with open(output_filename, 'w') as output_file:
        output_file.write(f'Number of bytes read: {num_bytes_read}\n')
        output_file.write(f'Checksum: {checksum}\n')

if __name__ == "__main__":
    input_filename = 'input.txt'
    output_filename = 'output.txt'
    process_file(input_filename, output_filename)