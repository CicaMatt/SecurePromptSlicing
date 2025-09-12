import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        content = f.read()
        checksum = hashlib.md5(content).hexdigest()
        num_bytes = len(content)
    
    return num_bytes, int(checksum, 16)

def save_results(output_file_path, num_bytes, checksum):
    with open(output_file_path, 'w') as f:
        f.write(f'Number of bytes read: {num_bytes}\n')
        f.write(f'Checksum: {checksum}')

def main(input_file_path, output_file_path):
    num_bytes, checksum = calculate_checksum(input_file_path)
    
    is_empty = (checksum == 0)
    
    save_results(output_file_path, num_bytes, checksum)

if __name__ == "__main__":
    input_file_path = 'input.txt'  # Replace with your input file path
    output_file_path = 'output.txt'  # Replace with your output file path
    main(input_file_path, output_file_path)