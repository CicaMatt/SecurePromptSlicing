import os

def calculate_checksum(buffer):
    return sum(buffer) % 256

def process_file(input_filename, output_filename):
    try:
        with open(input_filename, 'rb') as infile:
            buffer = infile.read()
        
        if not buffer:
            raise ValueError("Input file is empty or cannot be read.")
        
        checksum = calculate_checksum(buffer)
        num_bytes_read = len(buffer)

        with open(output_filename, 'w') as outfile:
            outfile.write(f"Number of bytes read: {num_bytes_read}\n")
            outfile.write(f"Checksum: {checksum}\n")

    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
input_file = "input.txt"
output_file = "output.txt"

process_file(input_file, output_file)