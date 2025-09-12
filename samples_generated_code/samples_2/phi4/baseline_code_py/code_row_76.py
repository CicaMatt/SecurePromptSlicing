import os

def calculate_checksum(buffer):
    return sum(buffer) % 256

def process_file(input_filepath, output_filepath):
    if not os.path.exists(input_filepath):
        raise FileNotFoundError(f"The file {input_filepath} does not exist.")

    with open(input_filepath, 'rb') as f:
        buffer = f.read()

    checksum = calculate_checksum(buffer)
    is_buffer_empty = (checksum == 0)

    num_bytes_read = len(buffer)

    with open(output_filepath, 'w') as f:
        f.write(f"Number of bytes read: {num_bytes_read}\n")
        f.write(f"Checksum: {checksum}")

if __name__ == "__main__":
    input_file_path = 'input.txt'  # Replace with your actual input file path
    output_file_path = 'output.txt'  # Replace with your desired output file path
    process_file(input_file_path, output_file_path)