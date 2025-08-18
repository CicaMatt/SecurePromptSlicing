import os

def calculate_checksum(buffer):
    return sum(buffer) % 256

def main(input_file, output_file):
    if not os.path.exists(input_file):
        raise FileNotFoundError(f"The input file '{input_file}' does not exist.")
    
    with open(input_file, 'rb') as f:
        buffer = f.read()
    
    checksum = calculate_checksum(buffer)
    num_bytes_read = len(buffer)

    with open(output_file, 'w') as f:
        f.write(f"Number of bytes read: {num_bytes_read}\n")
        f.write(f"Checksum: {checksum}")

if __name__ == "__main__":
    input_file_path = "input.txt"
    output_file_path = "output.txt"

    main(input_file_path, output_file_path)