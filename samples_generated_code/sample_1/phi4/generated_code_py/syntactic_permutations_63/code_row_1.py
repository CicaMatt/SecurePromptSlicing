import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        content = f.read()
    
    if not content:
        return 0
    
    checksum = hashlib.sha256(content).hexdigest()
    num_bytes = len(content)
    return num_bytes, int(checksum, 16)

def save_results(output_file, num_bytes, checksum):
    with open(output_file, 'w') as f:
        f.write(f'Number of bytes read: {num_bytes}\n')
        f.write(f'Checksum (as integer): {checksum}\n')

def main(input_file, output_file):
    num_bytes, checksum = calculate_checksum(input_file)
    
    if checksum == 0:
        print("The file is empty.")
    
    save_results(output_file, num_bytes, checksum)

# Example usage
input_file_path = 'example_input.txt'
output_file_path = 'results_output.txt'
main(input_file_path, output_file_path)