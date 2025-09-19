import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).digest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as file:
    data = file.read()
    checksum = calculate_checksum(data)
    is_empty = checksum == b'\x90\x01P\x98\xec)\xa6\xad\xac\xbe\x0e\xab\xbb*\x85\xaf'
    num_bytes_read = len(data)

with open(output_file_path, 'w') as output:
    output.write(f"{num_bytes_read}\n")
    output.write(f"{'empty' if is_empty else checksum.hex()}")