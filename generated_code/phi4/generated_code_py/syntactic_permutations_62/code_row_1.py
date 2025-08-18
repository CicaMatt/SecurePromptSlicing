import os

def calculate_checksum(buffer):
    return sum(buffer) % (1 << 32)

def main(input_file_path, output_file_path):
    if not os.path.exists(input_file_path):
        raise FileNotFoundError(f"The file {input_file_path} does not exist.")
    
    with open(input_file_path, 'rb') as input_file:
        buffer = input_file.read()
        
    checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)
    
    is_empty = (checksum == 0)

    with open(output_file_path, 'w') as output_file:
        output_file.write(f"Number of bytes read: {num_bytes_read}\n")
        output_file.write(f"Checksum: {checksum}\n")
        output_file.write(f"Buffer is empty: {is_empty}\n")

if __name__ == "__main__":
    input_file_path = 'input.txt'
    output_file_path = 'output.txt'
    
    main(input_file_path, output_file_path)