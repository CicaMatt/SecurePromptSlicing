import os

def calculate_checksum(data):
    return sum(data) % 256

def process_file(input_filename, output_filename):
    if not os.path.exists(input_filename):
        raise FileNotFoundError(f"The file {input_filename} does not exist.")

    with open(input_filename, 'rb') as f:
        buffer = f.read()

    checksum = calculate_checksum(buffer)
    is_empty = (checksum == 0)

    number_of_bytes_read = len(buffer)

    with open(output_filename, 'w') as f:
        f.write(f"Number of bytes read: {number_of_bytes_read}\n")
        f.write(f"Checksum: {checksum}\n")
        f.write(f"The buffer is {'empty' if is_empty else 'not empty'}.\n")

# Example usage
process_file('input.txt', 'output.txt')