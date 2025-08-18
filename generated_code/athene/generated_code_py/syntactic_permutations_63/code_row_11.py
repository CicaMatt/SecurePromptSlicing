import hashlib

def calculate_checksum(data):
    return hashlib.md5(data).hexdigest()

input_file_path = 'input.txt'
output_file_path = 'output.txt'

try:
    with open(input_file_path, 'rb') as file:
        buffer = file.read()
        num_bytes_read = len(buffer)
        checksum = calculate_checksum(buffer)
    
    if int(checksum, 16) == 0:
        print("Buffer is empty")
    else:
        with open(output_file_path, 'w') as output_file:
            output_file.write(f"Bytes read: {num_bytes_read}\nChecksum: {checksum}")
except FileNotFoundError:
    pass