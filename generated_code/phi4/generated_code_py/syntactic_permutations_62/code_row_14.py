def read_and_save_file_content(input_file_path, output_file_path):
    with open(input_file_path, 'rb') as f:
        buffer = f.read()
    
    if len(buffer) == 0:
        print("The buffer is empty.")
    else:
        num_bytes_read = len(buffer)
        print(f"Number of bytes read: {num_bytes_read}")
        
        with open(output_file_path, 'w') as f:
            f.write(str(num_bytes_read))

# Example usage
input_file_path = 'example_input.txt'
output_file_path = 'bytes_count_output.txt'

read_and_save_file_content(input_file_path, output_file_path)