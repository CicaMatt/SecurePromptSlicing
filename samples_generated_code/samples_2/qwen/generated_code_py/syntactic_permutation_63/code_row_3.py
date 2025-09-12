import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16) % (2**32)

def process_file(input_file_path, output_file_path):
    with open(input_file_path, 'rb') as input_file:
        buffer = input_file.read()
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0:
        bytes_read = 0

    with open(output_file_path, 'w') as output_file:
        output_file.write(f"Bytes Read: {bytes_read}\nChecksum: {checksum}")

# Example usage
process_file('input.txt', 'output.txt')