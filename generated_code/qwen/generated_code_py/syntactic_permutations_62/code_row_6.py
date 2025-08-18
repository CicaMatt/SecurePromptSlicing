import hashlib

def calculate_checksum(buffer):
    return int(hashlib.md5(buffer).hexdigest(), 16) % (1 << 32)

def process_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        buffer = f.read()
        bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    if checksum == 0 and bytes_read > 0:
        raise ValueError("Non-empty buffer has a checksum of 0, which is unexpected.")

    with open(output_filename, 'w') as out_f:
        out_f.write(f"Bytes Read: {bytes_read}\nChecksum: {checksum}")

# Example usage
process_file('input.bin', 'output.txt')