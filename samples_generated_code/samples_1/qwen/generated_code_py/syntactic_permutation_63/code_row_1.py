import hashlib

def calculate_checksum(file_path):
    with open(file_path, 'rb') as f:
        data = f.read()
    return hashlib.md5(data).hexdigest()

def save_info_to_file(output_path, num_bytes, checksum):
    with open(output_path, 'w') as f:
        f.write(f"Number of bytes: {num_bytes}\nChecksum: {checksum}")

input_file_path = 'input.txt'
output_file_path = 'info.txt'

with open(input_file_path, 'rb') as file:
    data = file.read()
    num_bytes = len(data)
    checksum = calculate_checksum(input_file_path)

save_info_to_file(output_file_path, num_bytes, checksum if num_bytes > 0 else '0')