import hashlib

def calculate_checksum(data):
    return int(hashlib.md5(data).hexdigest(), 16) % (1 << 32)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    with open(output_filename, 'w') as out_f:
        out_f.write(f"Bytes Read: {bytes_read}\nChecksum: {checksum}\n")

# Example usage
process_file('input.txt', 'output.txt')