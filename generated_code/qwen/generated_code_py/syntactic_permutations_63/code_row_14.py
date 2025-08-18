def read_and_write_file_contents(input_filename, output_filename):
    with open(input_filename, 'rb') as infile:
        buffer = infile.read()
        num_bytes_read = len(buffer)
    
    if num_bytes_read == 0:
        buffer = b'Empty file'
    
    with open(output_filename, 'wb') as outfile:
        outfile.write(f"Number of bytes read: {num_bytes_read}\n".encode('utf-8'))
        outfile.write(buffer)

# Example usage
read_and_write_file_contents('input.txt', 'output.txt')