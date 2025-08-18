import hashlib

def calculate_checksum(data):
    return int(hashlib.sha256(data).hexdigest(), 16) % (10 ** 8)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()

    checksum = calculate_checksum(buffer)
    
    if checksum == 0:
        with open(output_filename, 'wb') as f:
            f.write(buffer + str(checksum).encode())

# Usage example:
input_filename = 'input.txt'
output_filename = 'output_with_checksum.txt'
process_file(input_filename, output_filename)