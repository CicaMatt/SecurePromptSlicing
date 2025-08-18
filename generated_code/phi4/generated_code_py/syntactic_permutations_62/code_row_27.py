import hashlib

def calculate_checksum(buffer):
    return int(hashlib.sha256(buffer).hexdigest(), 16) % (10**8)

def process_file(input_file_path, output_file_path):
    with open(input_file_path, 'rb') as f:
        buffer = f.read()

    checksum = calculate_checksum(buffer)
    number_read = len(buffer)

    if checksum == 0:
        print("The buffer is empty.")
    
    with open(output_file_path, 'w') as f:
        f.write(f"Number read: {number_read}\n")
        f.write(f"Checksum: {checksum}")

# Example usage
input_file_path = 'example_input.txt'
output_file_path = 'result_output.txt'

process_file(input_file_path, output_file_path)