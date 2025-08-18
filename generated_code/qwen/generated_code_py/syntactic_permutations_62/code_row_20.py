import hashlib

def calculate_checksum(data):
    if not data:
        return 0
    sha1 = hashlib.sha1()
    sha1.update(data)
    return int(sha1.hexdigest(), 16)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as file:
        buffer = file.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    with open(output_filename, 'w') as file:
        file.write(f'Number of bytes read: {num_bytes_read}\n')
        file.write(f'Checksum: {checksum}\n')

# Example usage
process_file('input.txt', 'output.txt')