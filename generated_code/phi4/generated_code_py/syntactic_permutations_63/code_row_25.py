import os

def calculate_checksum(buffer):
    return sum(buffer) % 256

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()
    
    checksum = calculate_checksum(buffer)
    
    if checksum == 0:
        with open(output_filename, 'wb') as out_f:
            # Save the bytes and checksum
            out_f.write(buffer)
            out_f.write(checksum.to_bytes(1, byteorder='little'))

# Example usage: process_file('input.bin', 'output.bin')