import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()
    
    checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)
    
    if checksum == 0:
        print("The buffer is empty.")
    
    with open(output_filename, 'w') as out_f:
        out_f.write(f"Number of bytes read: {num_bytes_read}\n")
        out_f.write(f"Checksum: {checksum}\n")

# Example usage
input_file = "example_input.txt"
output_file = "result_output.txt"
process_file(input_file, output_file)