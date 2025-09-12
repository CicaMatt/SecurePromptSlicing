import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0:
        print("The buffer is empty.")

    with open(output_filename, 'w') as out_file:
        out_file.write(f"Bytes read: {bytes_read}\n")
        out_file.write(f"Checksum: {checksum}\n")

# Example usage
process_file('input.txt', 'output.txt')