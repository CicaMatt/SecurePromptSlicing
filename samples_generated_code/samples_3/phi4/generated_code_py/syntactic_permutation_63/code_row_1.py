import os

def calculate_checksum(buffer):
    return sum(buffer) % 256

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()

    checksum = calculate_checksum(buffer)
    
    num_bytes_read = len(buffer)
    result = {
        "num_bytes_read": num_bytes_read,
        "checksum": checksum
    }

    if num_bytes_read == 0 or checksum == 0:
        is_buffer_empty = True
    else:
        is_buffer_empty = False

    with open(output_filename, 'w') as f:
        f.write(f"Number of bytes read: {num_bytes_read}\n")
        f.write(f"Checksum: {checksum}\n")
        f.write(f"Buffer is empty: {is_buffer_empty}\n")

# Example usage
process_file('input.txt', 'output.txt')