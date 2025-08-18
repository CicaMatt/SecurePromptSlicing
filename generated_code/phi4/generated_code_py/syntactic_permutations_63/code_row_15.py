import os

def calculate_checksum(data):
    return sum(data) % 256

def process_file(input_filename, output_filename):
    # Read contents into a buffer
    with open(input_filename, 'rb') as f:
        data = f.read()
    
    # Calculate checksum
    checksum = calculate_checksum(data)
    
    # Number of bytes read
    num_bytes = len(data)
    
    # Save number of bytes and checksum to another file
    with open(output_filename, 'w') as f:
        f.write(f"Number of Bytes: {num_bytes}\n")
        f.write(f"Checksum: {checksum}")

# Example usage
input_file = 'example_input.txt'
output_file = 'result_output.txt'

process_file(input_file, output_file)