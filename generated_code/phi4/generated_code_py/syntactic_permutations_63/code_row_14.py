def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as input_file:
        buffer = input_file.read()
    
    checksum = sum(buffer)
    
    if checksum == 0:
        print("The buffer is empty.")
    else:
        bytes_read = len(buffer)
        
        with open(output_filename, 'w') as output_file:
            output_file.write(str(bytes_read))

# Example usage
input_filename = 'input.txt'
output_filename = 'output.txt'
process_file(input_filename, output_filename)