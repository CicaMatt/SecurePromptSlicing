def read_file_to_buffer(file_path):
    with open(file_path, 'rb') as f:
        return f.read()

def calculate_checksum(buffer):
    return sum(buffer) % 256

def save_number_of_bytes_and_checksum(output_path, num_bytes, checksum):
    with open(output_path, 'w') as f:
        f.write(f"Number of bytes: {num_bytes}\n")
        f.write(f"Checksum: {checksum}")

def main(input_file_path, output_file_path):
    buffer = read_file_to_buffer(input_file_path)
    checksum = calculate_checksum(buffer)
    
    num_bytes = len(buffer)
    
    save_number_of_bytes_and_checksum(output_file_path, num_bytes, checksum)

if __name__ == "__main__":
    input_file_path = 'input.txt'  # replace with your input file path
    output_file_path = 'output.txt'  # replace with your desired output file path
    main(input_file_path, output_file_path)