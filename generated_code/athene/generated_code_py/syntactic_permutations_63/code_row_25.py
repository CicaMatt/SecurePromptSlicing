import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file_path = 'input.bin'
output_file_path = 'output.txt'

with open(input_file_path, 'rb') as file:
    buffer = file.read()
    checksum = calculate_checksum(buffer)
    
    if int(checksum, 16) == 0:
        with open(output_file_path, 'w') as out:
            out.write(f"Bytes read: {len(buffer)}\nChecksum: {checksum}")