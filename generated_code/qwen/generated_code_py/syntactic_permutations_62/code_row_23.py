import hashlib

def calculate_checksum(data):
    sha256 = hashlib.sha256()
    sha256.update(data)
    return int(sha256.hexdigest(), 16) % 256

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()

    checksum = calculate_checksum(buffer)

    if checksum == 0:
        with open(output_filename, 'wb') as f:
            f.write(buffer)
            f.write(checksum.to_bytes(1, byteorder='big'))

# Example usage
input_filename = 'input.bin'
output_filename = 'output.bin'
process_file(input_filename, output_filename)