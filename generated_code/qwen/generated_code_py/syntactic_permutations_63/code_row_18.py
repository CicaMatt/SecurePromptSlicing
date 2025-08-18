def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as infile:
        buffer = infile.read()
    
    num_bytes_read = len(buffer)
    
    if num_bytes_read == 0:
        buffer = b'Buffer is empty'
    
    with open(output_filename, 'wb') as outfile:
        outfile.write(str(num_bytes_read).encode('utf-8'))
        outfile.write(b'\n')
        outfile.write(buffer)

# Example usage
process_file('input.txt', 'output.txt')