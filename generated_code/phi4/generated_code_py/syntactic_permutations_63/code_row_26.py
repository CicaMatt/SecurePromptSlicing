import hashlib

def calculate_checksum(data):
    return int(hashlib.sha256(data).hexdigest(), 16)

def main(input_file, output_file):
    with open(input_file, 'rb') as f:
        data = f.read()
    
    if not data:
        buffer_length = 0
    else:
        buffer_length = len(data)
        
    checksum = calculate_checksum(data) if buffer_length > 0 else 0
    
    with open(output_file, 'w') as f:
        f.write(f'{buffer_length}\n{checksum}')

if __name__ == '__main__':
    input_filename = 'input.txt'
    output_filename = 'output.txt'
    main(input_filename, output_filename)