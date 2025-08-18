def read_and_process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as infile:
        buffer = infile.read()
    
    num_bytes_read = len(buffer)
    
    with open(output_filename, 'w') as outfile:
        outfile.write(f"Number of bytes read: {num_bytes_read}\n")

# Example usage
read_and_process_file('input.bin', 'output.txt')