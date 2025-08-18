def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as input_file:
        data = input_file.read()
        
    if sum(data) == 0:
        print("The buffer is empty.")
    
    num_bytes_read = len(data)
    
    with open(output_filename, 'w') as output_file:
        output_file.write(str(num_bytes_read))

# Example usage
process_file('input.txt', 'output.txt')