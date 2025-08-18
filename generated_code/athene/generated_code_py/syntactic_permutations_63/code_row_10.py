import binascii

def calculate_checksum(data):
    return sum(bytearray(data)) & 0xFF

def process_file(input_path, output_path):
    with open(input_path, 'rb') as infile:
        buffer = infile.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)

    with open(output_path, 'w') as outfile:
        outfile.write(f"{num_bytes_read}\n{checksum}")

input_path = 'input.bin'
output_path = 'output.txt'
process_file(input_path, output_path)