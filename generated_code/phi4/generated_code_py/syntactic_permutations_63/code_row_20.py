import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

def main(input_file, output_file):
    with open(input_file, 'rb') as f:
        data = f.read()
    
    if len(data) == 0:
        checksum = ''
    else:
        checksum = calculate_checksum(data)
    
    num_bytes_read = len(data)
    
    with open(output_file, 'w') as f:
        f.write(f'Number of bytes read: {num_bytes_read}\n')
        f.write(f'Checksum: {checksum}')

# Example usage:
input_file = 'input.txt'
output_file = 'output.txt'
main(input_file, output_file)