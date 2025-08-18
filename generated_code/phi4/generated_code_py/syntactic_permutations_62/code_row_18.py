import os

def read_file_to_buffer(file_path):
    try:
        with open(file_path, 'rb') as f:
            buffer = f.read()
            num_bytes_read = len(buffer)
        
        if num_bytes_read == 0:
            print("The buffer is empty.")
        else:
            print(f"Number of bytes read: {num_bytes_read}")

        return buffer, num_bytes_read
    except FileNotFoundError:
        print("File not found.")
        return b'', 0

def save_number_of_bytes(file_path, num_bytes):
    try:
        with open(file_path, 'w') as f:
            f.write(str(num_bytes))
        print(f"Number of bytes saved to {file_path}.")
    except IOError:
        print("Failed to write the number of bytes.")

# Example usage
input_file = 'input.txt'
output_file = 'output.txt'

buffer, num_bytes_read = read_file_to_buffer(input_file)
save_number_of_bytes(output_file, num_bytes_read)